module inst_decoder (
    input [31:0] inst,

    output       wen,
    output [4:0] waddr,
    output       rden1,
    output [4:0] raddr1,
    output       rden2,
    output [4:0] raddr2,
    output       alu_en,
    output [4:0] alu_card,
    output       mem_rd,
    output       mem_wr,
    output       jmp,
    output       invalid
);

  wire [5:0] op = inst[31:26];
  wire [4:0] rs = inst[25:21];
  wire [4:0] rt = inst[20:16];
  wire [4:0] rd = inst[15:11];
  wire [5:0] funct = inst[5:0];

  wire R_type = ~|op;
  wire R_shape_100XXX = R_type & funct[5] & ~funct[4] & ~funct[3];
  wire R_shape_1000X0 = R_shape_100XXX & ~funct[2] & ~funct[0];
  wire ADD = R_shape_1000X0 & ~funct[1];
  wire SUB = R_shape_1000X0 & funct[1];
  wire AND = R_shape_100XXX & funct[2] & ~funct[1] & ~funct[0];
  wire OR = R_shape_100XXX & funct[2] & ~funct[1] & funct[0];
  wire XOR = R_shape_100XXX & funct[2] & funct[1] & ~funct[0];

  wire op_shape_10X011 = op[5] & ~op[4] & ~op[2] & op[1] & op[0];
  wire SW = op_shape_10X011 & op[3];
  wire LW = op_shape_10X011 & ~op[3];

  wire J = ~op[5] & ~op[4] & ~op[3] & ~op[2] & op[1] & ~op[0];

  wire do_calc = ADD | SUB | AND | OR | XOR;

  assign alu_card = ADD ? 5'b00001 :
                    SUB ? 5'b00011 :
                    AND ? 5'b01100 :
                    OR  ? 5'b01011 :
                    XOR ? 5'b01110 : 5'b00000;

  assign alu_en = do_calc;
  assign invalid = ~(do_calc | SW | LW | J);

  assign rden1 = do_calc | LW | SW;
  assign raddr1 = rden1 ? rs : 5'b00000;

  assign rden2 = do_calc | SW;
  assign raddr2 = rden2 ? rt : 5'b00000;

  assign wen = do_calc | LW;
  assign waddr = do_calc ? rd : (LW ? rt : 5'b00000);

  assign mem_rd = LW;
  assign mem_wr = SW;
  assign jmp = J;

endmodule

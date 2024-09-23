module my_alu (
    input wire [31:0] A,  // 左操作数
    input wire [31:0] B,  // 右操作数
    input wire [4 : 0] shamt,  // 移位量
    input wire [4 : 0] alu_op,  // ALU操作码
    output wire [31:0] F  // ALU计算结果
);

  wire signed [31:0] A_signed = A;
  wire signed [31:0] B_signed = B;

  wire eq = A == B;
  wire lt = A_signed < B_signed;
  wire u_lt = A < B;
  wire le = A_signed <= B_signed;
  wire u_le = A <= B;

  wire [31:0] cmp_res = {
    22'b0,
    ~u_le,  // ~(无符号小于等于) => 无符号大于
    ~le,  // ~(无符号小于等于) => 有符号大于
    ~u_lt,  // ~(无符号小于) => 无符号大于等于
    ~lt,  // ~(有符号小于) => 有符号大于等于
    ~eq,  // ~(等于) => 不等于
    u_le,  // 无符号小于等于
    le,  // 有符号小于等于
    u_lt,  // 无符号小于
    lt,  // 有符号小于
    eq  // 等于
  };

  assign F =    alu_op == 5'b00001 ? A + B :
                alu_op == 5'b00010 ? A - B :
                alu_op == 5'b00011 ? A & B :
                alu_op == 5'b00100 ? A | B :
                alu_op == 5'b00101 ? A ^ B :
                alu_op == 5'b00110 ? cmp_res :
                alu_op == 5'b00111 ? (B << shamt) :
                32'hz;
endmodule

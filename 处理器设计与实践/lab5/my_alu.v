module my_alu (
    input wire [31:0] A,  // 左操作数
    input wire [31:0] B,  // 右操作数
    input wire [4 : 0] alu_op,  // ALU操作码
    output wire [31:0] F  // ALU计算结果
);
  assign F = alu_op == 5'b00000 ? A + B :
                alu_op == 5'b00010 ? A - B :
                alu_op == 5'b00100 ? A & B :
                alu_op == 5'b00101 ? A | B :
                alu_op == 5'b00110 ? A ^ B : 32'hzzzzzzzz;
endmodule

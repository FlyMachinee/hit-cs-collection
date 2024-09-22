module my_decoder (
    input wire [5:0] op,    // 操作码字段
    input wire [5:0] funct, // 功能码字段

    output wire       do_calc,       // 是否进行ALU计算操作
    output wire [4:0] alu_op,        // ALU操作码
    output wire       do_shift,      // 是否进行移位操作
    output wire       do_movz,       // 是否进行MOVZ操作
    output wire       do_mem_read,   // 是否进行存储器读操作
    output wire       do_mem_write,  // 是否进行存储器写操作
    output wire       do_cmp,        // 是否进行比较操作
    output wire       do_bit_test,   // 是否进行位测试操作
    output wire       do_jump        // 是否进行跳转操作
);

  // R型指令判断
  wire R_type = ~|op;  // 当操作码全为0时，为R型指令

  // 非R型指令判断
  wire LW = op == 6'b100011;  // 加载字指令
  wire SW = op == 6'b101011;  // 存储字指令
  wire J = op == 6'b000010;  // 跳转指令
  wire CMP = op == 6'b111110;  // 比较指令
  wire BBT = op == 6'b111111;  // 位测试指令

  wire ADD = R_type & funct == 6'b100000;  // 加法指令
  wire SUB = R_type & funct == 6'b100010;  // 减法指令
  wire AND = R_type & funct == 6'b100100;  // 与指令
  wire OR = R_type & funct == 6'b100101;  // 或指令
  wire XOR = R_type & funct == 6'b100110;  // 异或指令
  wire SLL = R_type & funct == 6'b000000;  // 逻辑左移指令
  wire MOVZ = R_type & funct == 6'b001010;  // 条件移动指令

  // 根据指令类型设置输出信号
  assign do_calc = ADD | SUB | AND | OR | XOR;  // ALU操作
  assign alu_op = do_calc ? funct[4:0] : 5'bzzzzz;  // ALU操作码
  assign do_shift = SLL;  // 移位操作
  assign do_movz = MOVZ;  // MOVZ操作
  assign do_mem_read = LW;  // 存储器读操作
  assign do_mem_write = SW;  // 存储器写操作
  assign do_cmp = CMP;  // 比较操作
  assign do_bit_test = BBT;  // 位测试操作
  assign do_jump = J;  // 跳转操作

endmodule

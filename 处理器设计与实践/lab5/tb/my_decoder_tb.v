module my_decoder_tb;
  reg [5:0] op;
  reg [5:0] funct;
  wire do_calc;
  wire [4:0] alu_op;
  wire do_shift;
  wire do_movz;
  wire do_mem_read;
  wire do_mem_write;
  wire do_cmp;
  wire do_bit_test;
  wire do_jump;

  // 实例化被测试模块
  my_decoder uut (
      .op(op),
      .funct(funct),
      .do_calc(do_calc),
      .alu_op(alu_op),
      .do_shift(do_shift),
      .do_movz(do_movz),
      .do_mem_read(do_mem_read),
      .do_mem_write(do_mem_write),
      .do_cmp(do_cmp),
      .do_bit_test(do_bit_test),
      .do_jump(do_jump)
  );

  initial begin
    // 初始化信号
    op = 6'b000000;
    funct = 6'b000000;

    // 测试 R 型指令
    #10;
    funct = 6'b100000;  // ADD
    #10;
    funct = 6'b100010;  // SUB
    #10;
    funct = 6'b100100;  // AND
    #10;
    funct = 6'b100101;  // OR
    #10;
    funct = 6'b100110;  // XOR
    #10;
    funct = 6'b000000;  // SLL
    #10;
    funct = 6'b001010;  // MOVZ

    // 测试非 R 型指令
    #10;
    op = 6'b100011;  // LW
    #10;
    op = 6'b101011;  // SW
    #10;
    op = 6'b000010;  // J
    #10;
    op = 6'b111110;  // CMP
    #10;
    op = 6'b111111;  // BBT

    // 结束仿真
    #10;
    $finish;
  end
endmodule

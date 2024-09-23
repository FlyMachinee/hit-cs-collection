module my_alu_tb;
  reg  [31:0] A;
  reg  [31:0] B;
  reg  [ 4:0] alu_op;
  wire [31:0] F;

  // 实例化被测试模块
  my_alu uut (
      .A(A),
      .B(B),
      .alu_op(alu_op),
      .F(F)
  );

  initial begin
    // 初始化信号
    A = 32'h00000000;
    B = 32'h00000000;
    alu_op = 5'b00000;

    // 测试 ADD 操作
    #10;
    A = 32'h00000010;
    B = 32'h00000020;
    alu_op = 5'b00000;
    $display("ADD: A = %h, B = %h, F = %h", A, B, F);

    // 测试 SUB 操作
    #10;
    A = 32'h00000030;
    B = 32'h00000010;
    alu_op = 5'b00010;
    $display("SUB: A = %h, B = %h, F = %h", A, B, F);

    // 测试 AND 操作
    #10;
    A = 32'h000000FF;
    B = 32'h0000FF00;
    alu_op = 5'b00100;
    $display("AND: A = %h, B = %h, F = %h", A, B, F);

    // 测试 OR 操作
    #10;
    A = 32'h000000FF;
    B = 32'h0000FF00;
    alu_op = 5'b00101;
    $display("OR: A = %h, B = %h, F = %h", A, B, F);

    // 测试 XOR 操作
    #10;
    A = 32'h000000FF;
    B = 32'h0000FF00;
    alu_op = 5'b00110;
    $display("XOR: A = %h, B = %h, F = %h", A, B, F);

    // 测试无效操作码
    #10;
    A = 32'h000000FF;
    B = 32'h0000FF00;
    alu_op = 5'b11111;
    #10;
    $display("Invalid: A = %h, B = %h, F = %h", A, B, F);

    // 结束仿真
    $finish;
  end
endmodule

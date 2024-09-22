`timescale 1ns / 1ps

module test_mux;
  reg  [1:0] d0;  // 2位输入信号 d0
  reg  [1:0] d1;  // 2位输入信号 d1
  reg        select;  // 选择信号
  wire [1:0] out;  // 2位输出信号

  mux_2_to_1 U_mux (
      .d0(d0),
      .d1(d1),
      .select(select),
      .out(out)
  );

  // 测试过程
  initial begin
    // 初始化信号
    d0 = 2'b00;
    d1 = 2'b01;
    select = 0;

    #10 select = 1;

    #10 d0 = 2'b10;
    d1 = 2'b11;
    select = 0;

    #10 select = 1;
    $stop;
  end
endmodule

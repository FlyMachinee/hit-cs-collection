`timescale 1ns / 1ps

module test_counter;
  // 测试元件中的信号
  reg        clk;  // 时钟信号
  reg        rst;  // 复位信号
  wire [3:0] T;  // 输出信号

  counter U_counter (
      .clk(clk),
      .rst(rst),
      .T  (T)
  );

  initial begin
    // 初始化信号
    clk = 0;
    rst = 1;
    #10;

    rst = 0;
    #50;

    // 再次复位
    rst = 1;
    #10;

    rst = 0;
    #50;

    $stop;
  end

  always begin
    #5 clk = ~clk;
  end

endmodule

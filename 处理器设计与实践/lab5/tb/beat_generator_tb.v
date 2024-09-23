module beat_generator_tb;
  reg clk;
  reg resetn;
  wire [2:0] T;

  // 实例化被测试模块
  beat_generator uut (
      .clk(clk),
      .resetn(resetn),
      .T(T)
  );

  // 时钟生成
  initial begin
    clk = 0;
    forever #5 clk = ~clk;  // 每5个时间单位翻转一次时钟信号
  end

  // 测试序列
  initial begin
    // 初始化信号
    resetn = 0;

    // 复位节拍器
    #10;
    resetn = 1;

    // 观察节拍器输出
    #150;

    // 结束仿真
    $finish;
  end
endmodule

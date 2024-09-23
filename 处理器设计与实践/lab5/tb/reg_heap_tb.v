module reg_heap_tb;
  reg clk;
  reg resetn;
  reg [4:0] raddr1;
  reg [4:0] raddr2;
  reg we;
  reg [4:0] waddr;
  reg [31:0] wdata;
  wire [31:0] rdata1;
  wire [31:0] rdata2;

  // 实例化被测试模块
  reg_heap uut (
      .clk(clk),
      .resetn(resetn),
      .raddr1(raddr1),
      .raddr2(raddr2),
      .we(we),
      .waddr(waddr),
      .wdata(wdata),
      .rdata1(rdata1),
      .rdata2(rdata2)
  );

  // 时钟生成
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end

  // 测试序列
  initial begin
    // 初始化信号
    resetn = 0;
    raddr1 = 5'b00000;
    raddr2 = 5'b00001;
    we = 0;
    waddr = 5'b00000;
    wdata = 32'h0;

    // 复位寄存器堆
    #10;
    resetn = 1;

    // 写入数据到寄存器
    #10;
    we = 1;
    waddr = 5'b00010;
    wdata = 32'hDEADBEEF;
    #10;
    we = 0;

    // 读取寄存器数据
    #10;
    raddr1 = 5'b00010;
    #10;
    $display("Read from raddr1: %h", rdata1);

    // 写入另一个数据到寄存器
    #10;
    we = 1;
    waddr = 5'b00011;
    wdata = 32'hCAFEBABE;
    #10;
    we = 0;

    // 读取寄存器数据
    #10;
    raddr2 = 5'b00011;
    #10;
    $display("Read from raddr2: %h", rdata2);

    // 结束仿真
    #50;
    $finish;
  end
endmodule

module reg_heap (
    input wire        clk,     // 时钟信号
    input wire        resetn,  // 低电平复位信号
    input wire [ 4:0] raddr1,  // 读寄存器1地址
    input wire [ 4:0] raddr2,  // 读寄存器2地址
    input wire        we,      // 写使能信号
    input wire [ 4:0] waddr,   // 写寄存器地址
    input wire [31:0] wdata,   // 写入数据

    output wire [31:0] rdata1,  // 读寄存器1数据
    output wire [31:0] rdata2   // 读寄存器2数据
);

  // 寄存器堆，包含32个32位寄存器
  reg [31:0] registers[31:0];
  integer i;

  // 时钟上升沿触发
  always @(posedge clk) begin
    if (!resetn) begin
      // 复位时，将所有寄存器清零
      for (i = 0; i < 32; i = i + 1) begin
        registers[i] <= 32'h0;
      end
    end else if (we) begin
      // 写使能信号有效时，将数据写入指定寄存器
      registers[waddr] <= wdata;
    end
  end

  // 读寄存器1的数据
  assign rdata1 = registers[raddr1];
  // 读寄存器2的数据
  assign rdata2 = registers[raddr2];

endmodule

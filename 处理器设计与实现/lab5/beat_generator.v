module beat_generator (
    input wire clk,  // 时钟信号
    input wire resetn,  // 低有效复位信号
    output reg [2:0] T  // 节拍输出
);
  // 时钟上升沿触发
  always @(posedge clk) begin
    if (!resetn) begin  // 复位时
      T <= 3'b001;  // 重置为3'b001
    end else begin
      T <= {T[0], T[2:1]};  // 循环右移
    end
  end
endmodule

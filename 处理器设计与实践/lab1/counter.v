module counter (
    input wire clk,
    input wire rst,
    output reg [3:0] T
);
  always @(posedge clk) begin
    if (rst) begin
      T <= 4'b1000;
    end else begin
      T <= {T[0], T[3:1]};
    end
  end
endmodule

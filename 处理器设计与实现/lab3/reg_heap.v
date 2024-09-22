module reg_heap (
    input wire clk,
    input wire [4:0] raddr1,
    input wire [4:0] raddr2,
    input wire we,
    input wire [4:0] waddr,
    input wire [31:0] wdata,

    output wire [31:0] rdata1,
    output wire [31:0] rdata2
);

  reg [31:0] registers[31:0];

  assign rdata1 = registers[raddr1];
  assign rdata2 = registers[raddr2];

  always @(posedge clk) begin
    if (we) begin
      registers[waddr] <= wdata;
    end
  end

endmodule

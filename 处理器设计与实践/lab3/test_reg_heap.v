`timescale 1ns / 1ps

module test_reg_heap;

  reg clk;
  reg [4:0] raddr1;
  reg [4:0] raddr2;
  reg we;
  reg [4:0] waddr;
  reg [31:0] wdata;

  wire [31:0] rdata1;
  wire [31:0] rdata2;

  reg_heap uut (
      .clk(clk),
      .raddr1(raddr1),
      .raddr2(raddr2),
      .we(we),
      .waddr(waddr),
      .wdata(wdata),
      .rdata1(rdata1),
      .rdata2(rdata2)
  );

  always #5 clk = ~clk;

  initial begin
    clk = 0;
    raddr1 = 0;
    raddr2 = 0;

    // r0 = 0, r1 = 0, w = 1
    we = 1;
    waddr = 5'd1;
    wdata = 32'hA5A5A5A5;
    #10;
    we = 0;

    // r0 = 1, r1 = 0
    raddr1 = 5'd1;
    #10;

    // r0 = 1, r1 = 0, w = 2
    we = 1;
    waddr = 5'd2;
    wdata = 32'h5A5A5A5A;
    #10;
    we = 0;

    // r0 = 1, r1 = 2
    raddr2 = 5'd2;
    #10;

    // r0 = 1, r1 = 2, w = 3
    we = 1;
    waddr = 5'd3;
    wdata = 32'h12345678;
    #10;
    we = 0;

    raddr1 = 5'd3;
    #10;

    $finish;
  end

endmodule

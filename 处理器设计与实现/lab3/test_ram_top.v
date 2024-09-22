`timescale 1ns / 1ps

module test_ram_top;

  reg clk;
  reg [15:0] ram_addr;
  reg [31:0] ram_wdata;
  reg ram_wen;

  wire [31:0] ram_rdata;

  ram_top U_ram_top (
      .clk(clk),
      .ram_addr(ram_addr),
      .ram_wdata(ram_wdata),
      .ram_wen(ram_wen),
      .ram_rdata(ram_rdata)
  );

  always #5 clk = ~clk;

  initial begin
    clk = 0;
    ram_addr = 0;
    ram_wdata = 0;
    ram_wen = 0;

    #10;

    // Test Case 1: Write data to address 0
    ram_addr  = 16'h0000;
    ram_wdata = 32'hDEADBEEF;
    ram_wen   = 1;
    #10;
    ram_wen  = 0;

    // Test Case 2: Read data from address 0
    ram_addr = 16'h0000;
    #10;

    // Test Case 3: Write data to address 1
    ram_addr  = 16'h0001;
    ram_wdata = 32'hCAFEBABE;
    ram_wen   = 1;
    #10;
    ram_wen  = 0;

    // Test Case 4: Read data from address 1
    ram_addr = 16'h0001;
    #10;

    $finish;
  end

endmodule

module testbench;
  reg clk;
  reg [15:0] ram_addr;
  wire [31:0] ram_wdata;
  reg ram_wen;
  wire [31:0] ram_rdata;

  reg [4:0] raddr1;
  reg we;
  reg [4:0] waddr;
  wire [31:0] wdata;
  wire [31:0] rdata1;

  reg init = 0;
  reg [31:0] init_data = 32'hDEADBEEF;

  assign wdata = init ? init_data : ram_rdata;
  assign ram_wdata = init ? init_data : rdata1;

  // Instantiate the RAM module
  ram_top ram_inst (
      .clk(clk),
      .ram_addr(ram_addr),
      .ram_wdata(ram_wdata),
      .ram_wen(ram_wen),
      .ram_rdata(ram_rdata)
  );

  // Instantiate the Register Heap module
  reg_heap reg_inst (
      .clk(clk),
      .raddr1(raddr1),
      .we(we),
      .waddr(waddr),
      .wdata(wdata),
      .rdata1(rdata1)
  );

  // Clock generation
  initial begin
    clk = 0;
    forever #5 clk = ~clk;
  end



  // Test sequence
  initial begin
    // Initialize signals
    ram_addr = 16'h0000;
    ram_wen = 1'b0;
    raddr1 = 5'b00000;
    we = 1'b0;
    waddr = 5'b00000;

    // Write data to RAM addr 0001
    #10;
    init = 1;
    init_data = 32'hDEADBEEF;
    ram_addr = 16'h0001;
    ram_wen = 1'b1;
    #10;
    ram_wen = 1'b0;

    // Read data from RAM addr 0001 to register $2
    ram_addr = 16'h0001;
    we = 1'b1;
    waddr = 5'b00010;
    #10;
    we = 1'b0;

    // Write data from register $2 to RAM addr 0002
    raddr1 = 5'b00010;
    ram_addr = 16'h0002;
    ram_wen = 1'b1;
    #10;
    ram_wen = 1'b0;

    // Read data from RAM addr 0002 to register $1
    ram_addr = 16'h0002;
    we = 1'b1;
    waddr = 5'b00001;
    raddr1 = 5'b00001;
    #10;
    we = 1'b0;
    $finish;
  end

endmodule

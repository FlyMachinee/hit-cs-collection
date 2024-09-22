module test_inst_decoder;

  // Parameters

  //Ports
  reg [31:0] inst;
  wire wen;
  wire [4:0] waddr;
  wire rden1;
  wire [4:0] raddr1;
  wire rden2;
  wire [4:0] raddr2;
  wire alu_en;
  wire [4:0] alu_card;
  wire mem_rd;
  wire mem_wr;
  wire jmp;
  wire invalid;

  inst_decoder inst_decoder_inst (
      .inst(inst),
      .wen(wen),
      .waddr(waddr),
      .rden1(rden1),
      .raddr1(raddr1),
      .rden2(rden2),
      .raddr2(raddr2),
      .alu_en(alu_en),
      .alu_card(alu_card),
      .mem_rd(mem_rd),
      .mem_wr(mem_wr),
      .jmp(jmp),
      .invalid(invalid)
  );

  initial begin
    inst = 32'h00430820;
    #10;
    
    inst = 32'h8cc40018;
    #10;
    
    inst = 32'h12345678;
    #10;

    $stop;
  end
endmodule

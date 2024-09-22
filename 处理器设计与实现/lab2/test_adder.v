`timescale 1ns / 1ps

module test_adder;

  // Inputs
  reg [31:0] A;
  reg [31:0] B;
  reg Cin;

  // Outputs
  wire [31:0] F;
  wire Cout;

  // Instantiate the adder
  adder U_adder (
      .A(A),
      .B(B),
      .Cin(Cin),
      .F(F),
      .Cout(Cout)
  );

  initial begin
    A   = 32'h00000001;
    B   = 32'h00000001;
    Cin = 0;
    #10;

    A   = 32'h00000001;
    B   = 32'h00000001;
    Cin = 1;
    #10;

    A   = 32'hFFFFFFFF;
    B   = 32'h00000001;
    Cin = 0;
    #10;

    A   = 32'hFFFFFFFF;
    B   = 32'h00000001;
    Cin = 1;
    #10;

    $finish;
  end

endmodule

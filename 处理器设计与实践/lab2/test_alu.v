`timescale 1ns / 1ps

module test_alu;

  reg [31:0] A;
  reg [31:0] B;
  reg Cin;
  reg [4:0] Card;

  wire [31:0] F;
  wire Cout;
  wire Zero;

  alu U_alu (
      .A(A),
      .B(B),
      .Cin(Cin),
      .Card(Card),
      .F(F),
      .Cout(Cout),
      .Zero(Zero)
  );

  initial begin
    // Test Case 1: A + B
    A = 32'hfffffffe;
    B = 32'h00000001;
    Card = 0;
    #10;

    // Test Case 2: A + B + Cin
    A = 32'hfffffffe;
    B = 32'h00000001;
    Cin = 1;
    Card = 1;
    #10;

    // Test Case 3: A - B
    A = 32'h0000000a;
    B = 32'h0000000a;
    Cin = 0;
    Card = 2;
    #10;

    // Test Case 4: A - B - Cin
    A = 32'h0000000a;
    B = 32'h0000000a;
    Cin = 1;
    Card = 3;
    #10;

    // Test Case 5: B - A
    A = 32'h00000001;
    B = 32'h00000002;
    Cin = 0;
    Card = 4;
    #10;

    // Test Case 6: B - A - Cin
    A = 32'h00000001;
    B = 32'h00000002;
    Cin = 1;
    Card = 5;
    #10;

    // Test Case 7: A
    A = 32'h00000001;
    B = 32'h00000000;
    Cin = 0;
    Card = 6;
    #10;

    // Test Case 8: B
    A = 32'h00000000;
    B = 32'h00000001;
    Cin = 0;
    Card = 7;
    #10;

    // Test Case 9: ~A
    A = 32'h00000001;
    B = 32'h00000000;
    Cin = 0;
    Card = 8;
    #10;

    // Test Case 10: ~B
    A = 32'h00000000;
    B = 32'h00000001;
    Cin = 0;
    Card = 9;
    #10;

    // Test Case 11: A | B
    A = 32'h00000001;
    B = 32'h00000002;
    Cin = 0;
    Card = 10;
    #10;

    // Test Case 12: A & B
    A = 32'h00000003;
    B = 32'h00000001;
    Cin = 0;
    Card = 11;
    #10;

    // Test Case 13: ~(A ^ B)
    A = 32'h00000001;
    B = 32'h00000001;
    Cin = 0;
    Card = 12;
    #10;

    // Test Case 14: A ^ B
    A = 32'h00000001;
    B = 32'h00000002;
    Cin = 0;
    Card = 13;
    #10;

    // Test Case 15: ~(A & B)
    A = 32'h00000001;
    B = 32'h00000001;
    Cin = 0;
    Card = 14;
    #10;

    // Test Case 16: Zero
    Card = 15;
    #10;

    // Finish simulation
    $finish;
  end

endmodule

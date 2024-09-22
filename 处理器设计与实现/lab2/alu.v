module alu (
    input wire [ 31:0] A,
    input wire [ 31:0] B,
    input wire         Cin,
    input wire [4 : 0] Card,

    output wire [31:0] F,
    output wire        Cout,
    output wire        Zero
);
  wire cout_temp;
  assign {cout_temp, F} =    (Card == 0) ? A + B :
                (Card == 1) ? A + B + Cin :
                (Card == 2) ? A - B :
                (Card == 3) ? A - B - Cin :
                (Card == 4) ? B - A :
                (Card == 5) ? B - A - Cin :
                (Card == 6) ? A :
                (Card == 7) ? B :
                (Card == 8) ? ~A :
                (Card == 9) ? ~B :
                (Card == 10) ? A | B :
                (Card == 11) ? A & B :
                (Card == 12) ? ~(A ^ B) :
                (Card == 13) ? A ^ B :
                (Card == 14) ? ~(A & B) :
                33'b0;

  assign Cout = (Card >= 0 && Card <= 5) ? cout_temp : 0;

  assign Zero = ~(|(F));

endmodule

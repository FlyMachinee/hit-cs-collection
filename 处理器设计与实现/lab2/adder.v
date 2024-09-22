module adder (
    input wire [31:0] A,
    input wire [31:0] B,
    input wire Cin,

    output wire [31:0] F,
    output wire Cout
);

  assign {Cout, F} = A + B + Cin;

endmodule

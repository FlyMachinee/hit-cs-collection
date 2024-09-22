module mux_2_to_1 (
    input wire [1:0] d0,
    input wire [1:0] d1,
    input wire select,
    output wire [1:0] out
);

  assign out = select ? d1 : d0;

endmodule

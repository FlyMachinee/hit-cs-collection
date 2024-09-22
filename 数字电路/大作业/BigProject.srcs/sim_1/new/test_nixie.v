`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 17:18:17
// Design Name: 
// Module Name: test_nixie
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test_nixie();

reg [3:0] bcd;
wire [6:0] out;

initial begin
    #10 bcd = 4'b0101;
    #10 bcd = 4'b0111;
    #10 bcd = 4'b1001;
    #10 bcd = 4'b0100;
end

Nixie_Tube_Decode_typeA u(bcd, out);

endmodule

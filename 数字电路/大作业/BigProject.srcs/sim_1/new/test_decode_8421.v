`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 16:46:14
// Design Name: 
// Module Name: test_decode_8421
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


module test_decode_8421();

reg [15:0] secs;
wire [15:0] out;

initial 
begin
    secs = 16'b0;
    #20
    secs = 16'h1730; // 5936√Î£¨98∑÷÷”56√Î
    #20
    secs = 16'h0203; // 515√Î£¨8∑÷÷”35√Î
end

Decode_16bits_to_8421 u(secs, out);

endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 19:08:20
// Design Name: 
// Module Name: Mux_8421_2_to_1
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

module Mux_8421_2_to_1(
    input wire [3:0] num0,
    input wire [3:0] num1,
    input wire addr,
    output reg [3:0] out
);

always@(*) begin
    if (addr)
        out = num1;
    else
        out = num0;
end

endmodule

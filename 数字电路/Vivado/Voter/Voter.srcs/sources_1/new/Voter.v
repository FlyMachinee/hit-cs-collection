`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 15:47:13
// Design Name: 
// Module Name: Voter
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


module Voter(
    input A,
    input B,
    input C,
    output F
);
    wire o = 0;
    mux8to1 u1(o,0,0,0,1,0,1,1,1,{C,B,A});
    assign F = o;
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 15:21:02
// Design Name: 
// Module Name: FA
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


module FA(
    input A_i,
    input B_i,
    input C_i_1,
    output S_i,
    output C_i
    );
    wire s, c1, c2;
    HA_0 ha1(A_i, B_i, s, c1);
    HA_0 ha2(s, C_i_1, S_i, c2);
    assign C_i = c1 | c2;
endmodule

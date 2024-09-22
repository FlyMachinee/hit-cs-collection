`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 15:40:02
// Design Name: 
// Module Name: mux8to1
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


module mux8to1(output reg out, input[7:0] in, input[2:0] select);
	always @(in or select)
	    case(select)    //根据sel的不同选通in0,in1,in2,in3,in4,in5,in6,in7
	        3'b000: out = in[0];
	        3'b001: out = in[1];
	        3'b010: out = in[2];
	        3'b011: out = in[3];
	        3'b100: out = in[4];
	        3'b101: out = in[5];
	        3'b110: out = in[6];
	        3'b111: out = in[7];
	        default: out=1'bx;
	endcase
endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 15:40:34
// Design Name: 
// Module Name: test_rs
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
module test_rs();       
reg clk,r,s;
wire q,qb; 

initial begin
    clk = 0;
	r = 0;
	s = 0;
	
	#50
	r = 0;
	s = 1;
	
	#50
	r = 1;
    s = 0;
    
	#50
	r = 1;
	s = 1;
	
	#50
	r = 0;
	s = 1;
end

always #10 clk = ~clk;

RS_Trigger  u1 (s, r, clk, q, qb);

endmodule
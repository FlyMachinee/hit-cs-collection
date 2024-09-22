`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/29 17:50:08
// Design Name: 
// Module Name: test_mux
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
module test_mux();
reg [3:0] num0;
reg [3:0] num1;
reg addr;
wire [3:0] out;

initial begin
    num0 = 4'b1001;
    num1 = 4'b1100;
    addr = 0;
    #20 addr = 1;
    #20 addr = 0;
    #20 num1 = 4'b0010;
    #20 addr = 1;
end 

Mux_8421_2_to_1 u(num0, num1, addr, out);

endmodule

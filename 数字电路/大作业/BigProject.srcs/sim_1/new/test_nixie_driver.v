`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/29 18:01:50
// Design Name: 
// Module Name: test_nixie_driver
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


module test_nixie_driver();

reg [7:0] num0, num1, num2, num3;
reg clk = 0;
wire [3:0] addr;
wire [7:0] select_num;

always #1 clk = ~clk;

initial begin
    num0 = 8'h00;
    num1 = 8'h44;
    num2 = 8'h88;
    num3 = 8'hCC;
end

Nixie_Show_Driver u(num0, num1, num2, num3, clk, addr, select_num);

endmodule

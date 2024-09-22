`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 18:33:48
// Design Name: 
// Module Name: test_led
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


module test_led();

reg clk, work, type;
wire [3:0] led1;

initial begin
    clk = 0;
    work = 0;
    type = 0;
    #100 work = 1;
    #300 type = 1;
end

always #10 clk = ~clk;

LED_flow u1(clk, work, type, led1);

endmodule

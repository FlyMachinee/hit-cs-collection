`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/29 18:09:22
// Design Name: 
// Module Name: test_led_score
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


module test_led_score();

reg work;
reg [1:0] value;
wire [2:0] led;

initial begin
    work = 1;
    value = 0;
end

always #50 value = value + 1;
LED_score u(work, value, led);

endmodule

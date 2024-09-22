`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 16:04:42
// Design Name: 
// Module Name: test_counter
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


module test_counter();

reg set_zero, set_val, clock, is_ascend, pause;
reg [15:0] val;
wire [15:0] out;

initial 
begin
    set_zero = 0;
    set_val = 0;
    clock = 0;
    is_ascend = 1;
    pause = 0;
    
    #100 set_zero = 1;
    #20 set_zero = 0;
    
    #200
    val = 16'h001F;
    set_val = 1;
    is_ascend = 0;
    
    #20 set_val = 0;
    
    #200 pause = 1;
    #50 pause = 0;
end

always #10 clock = ~clock;

Counter u(set_zero, set_val, val, clock, pause, is_ascend, out);

endmodule

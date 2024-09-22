`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 15:31:20
// Design Name: 
// Module Name: sim
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


module sim();
    reg a, b, c;
    wire S, C;
    FA adder(a, b, c, S, C);
    initial
        begin
            a = 0;
            b = 0;
            c = 0;
        end
    always #10 {a, b, c} = {a, b, c} + 1;
endmodule

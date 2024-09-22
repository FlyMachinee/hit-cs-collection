`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/01 15:50:19
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
    reg A, B, C;
    wire F;
    mux8to1 u(F,8'b11101000,{C, B, A});
    initial
        begin
            A = 0;
            B = 0;
            C = 0;
        end
    always #10 {C, B, A} = {C, B, A} + 1;
endmodule

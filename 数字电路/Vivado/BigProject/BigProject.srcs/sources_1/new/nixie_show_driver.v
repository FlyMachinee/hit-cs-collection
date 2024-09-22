`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 22:31:45
// Design Name: 
// Module Name: nixie_show_driver
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
module Nixie_Show_Driver( // 数码管显示驱动
    input wire [7:0] num0,
    input wire [7:0] num1,
    input wire [7:0] num2,
    input wire [7:0] num3,
    input wire clk,
    output reg [3:0] addr,
    output reg [7:0] select_num
);

reg [31:0] counter = 0;
reg [1:0] sel = 0;

always @(posedge clk) begin
    if (counter < 32'd100_000) // 100_000_000 / 100_000 = 1000Hz
        counter = counter + 1;
    else begin
        counter = 0;
        case (sel)
            2'b00:
                begin
                    addr = 4'b1000;
                    select_num = num0;
                end
            2'b01:
                begin
                    addr = 4'b0100;
                    select_num = num1;
                end
            2'b10:
                begin
                    addr = 4'b0010;
                    select_num = num2;
                end
            2'b11:
                begin
                    addr = 4'b0001;
                    select_num = num3;
                end
        endcase
        
        sel = sel + 1;
    end
end

endmodule

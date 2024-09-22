`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 16:32:58
// Design Name: 
// Module Name: Decode_16bits_to_8421
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


module Decode_16bits_to_8421(
    input wire [15:0] bits, // 总秒数
    output reg [15:0] digits
);
reg [15:0] min, sec;
reg [15:0] min_h, min_l, sec_h, sec_l;

always@(bits)
begin
    min = bits / 16'd60; // 分钟数
    sec = bits % 16'd60; // 秒数
    
    min_h = min / 16'd10; // 分钟数的十位
    digits[15:12] = min_h[3:0];
    min_l = min % 16'd10; // 分钟数的个位
    digits[11:8] = min_l[3:0];
    sec_h = sec / 16'd10; // 秒钟数的十位
    digits[7:4] = sec_h[3:0];
    sec_l = sec % 16'd10; // 秒钟数的个位
    digits[3:0] = sec_l[3:0];
end

endmodule

`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 17:05:02
// Design Name: 
// Module Name: Nixie_Tube_Decode
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


module Nixie_Tube_Decode_typeA( // 带零显示
    input wire [3:0] Code_8421,
    input wire work,
    output reg [7:0] LEDs // g f e d c b a
);

always@(*)
begin
    LEDs = 8'b0;
    if (!work)
        LEDs = 8'b0;
    else
        case(Code_8421)
            4'd0: LEDs = 8'h3f;
            4'd1: LEDs = 8'h06;
            4'd2: LEDs = 8'h5b;
            4'd3: LEDs = 8'h4f;
            4'd4: LEDs = 8'h66;
            4'd5: LEDs = 8'h6d;
            4'd6: LEDs = 8'h7d;
            4'd7: LEDs = 8'h07;
            4'd8: LEDs = 8'h7f;
            4'd9: LEDs = 8'h6f;
            default: LEDs = 8'b0;
        endcase
end

endmodule


module Nixie_Tube_Decode_typeB( // 不带零显示
    input wire [3:0] Code_8421,
    input wire work,
    output reg [7:0] LEDs // g f e d c b a
);

always@(*)
begin
    LEDs = 8'b0;
    if (!work)
        LEDs = 8'b0;
    else
        case(Code_8421)
            4'd0: LEDs = 8'h00;
            4'd1: LEDs = 8'h06;
            4'd2: LEDs = 8'h5b;
            4'd3: LEDs = 8'h4f;
            4'd4: LEDs = 8'h66;
            4'd5: LEDs = 8'h6d;
            4'd6: LEDs = 8'h7d;
            4'd7: LEDs = 8'h07;
            4'd8: LEDs = 8'h7f;
            4'd9: LEDs = 8'h6f;
            default LEDs = 8'b0;
        endcase
end

endmodule

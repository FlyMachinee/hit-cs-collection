`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 15:30:41
// Design Name: 
// Module Name: RS_Trigger
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


module RS_Trigger(
    input wire set,
    input wire reset,
    input wire clock,
    output reg out = 0,
    output wire out_reverse
);

assign out_reverse = ~out;

always@(posedge clock)
    begin
        case({set, reset})
            2'b00: out <= out; // ����
            2'b01: out <= 1'b0; // ��0
            2'b10: out <= 1'b1; // ��1
            2'b11: out <= out; // �Ƿ����룬����Ϊ����
        endcase
    end

endmodule

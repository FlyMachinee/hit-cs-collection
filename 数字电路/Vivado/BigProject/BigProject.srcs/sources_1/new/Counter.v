`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 15:52:45
// Design Name: 
// Module Name: Counter
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


module Counter(
    input wire set_zero,
    input wire set_val,
    input wire [15:0] val,
    input wire clock,
    input wire freeze,
    input wire is_ascend,
    output reg [15:0] out = 1
);

reg [31:0] counter = 0;

always @(posedge clock)
begin
    if (counter < 32'd100_000_000)
        counter = counter + 1;
    else begin
        counter = 0;
        if (!freeze) begin
            if (is_ascend) begin
                if (out != 16'hFFFF)
                    out = out + 16'b1; //正计数
            end
            else
                if (out != 16'b0)
                    out = out - 16'b1; //倒计数
        end
    end
    
    if (set_zero)
        out = 16'b0; //同步清零
    else if (set_val)
        out = val; //同步置数
end

endmodule

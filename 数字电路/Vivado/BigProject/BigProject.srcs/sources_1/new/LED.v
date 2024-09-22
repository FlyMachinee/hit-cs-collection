`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 18:25:20
// Design Name: 
// Module Name: LED_flow
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
module LED_flow(
    input wire clk,
    input wire work,
    input wire type, // 0 为闪烁模式， 1 为流动模式
    output reg [3:0] led
);

reg [31:0] counter = 0;

always@(posedge clk) begin
    if (counter < 32'd20_000_000) // 每秒变5次  20_000_000
        counter = counter + 1;
    else begin
        counter = 0;
        if (!work)
            led = 4'b0000;
        else if (type) begin
            if (led == 4'b0000)
                led = 4'b0001;
            else
                led = led << 1;
        end
        else begin
            if (led == 4'b0101 || led == 4'b0000)
                led = 4'b1010;
            else
                led = 4'b0101;
        end
    end
end
endmodule

module LED_score(
    input wire work,
    input wire [1:0] value,
    output reg [2:0] led
);

always @(*) begin
    if (!work)
        led = 0;
    else
        case (value)
            2'd0: led = 3'b000;
            2'd1: led = 3'b001;
            2'd2: led = 3'b011;
            2'd3: led = 3'b111;
        endcase
end
endmodule
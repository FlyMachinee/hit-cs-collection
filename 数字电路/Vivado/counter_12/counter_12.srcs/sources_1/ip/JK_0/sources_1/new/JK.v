`timescale 1ns / 1ps
module JK(clk,Reset,Set,J,K,Q);
input clk;
input Reset;
input Set;
input J;
input K;

output Q;

reg q;

always@(posedge clk)
    if(!Reset)            
        begin
            q <= 1'b0;
        end
    else if(!Set)    
        begin
            q <= 1'b1;
        end
    else
        begin
            case({J,K})
                2'b00 : q <= q;
                2'b01 : q <= 0;
                2'b10 : q <= 1;
                default : q <= ~q;
            endcase
         end
     assign Q=q;
endmodule
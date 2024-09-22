`timescale 1ns / 1ps
module counter_12(reset,set,clk,Y);
input reset;
input set;
input clk;
output [3:0]Y;

wire j1,j2,j3,j4,k1,k2,k3,k4;

assign j1 = 1;
assign k1 = 1;
assign j2 = Y[0];
assign k2 = Y[0];
assign j3 = (~Y[3])&Y[1]&Y[0];
assign k3 = Y[0]&Y[1];
assign j4 = Y[0]&Y[1]&Y[2];
assign k4 = Y[0]&Y[1];
JK_0 u1 (clk,reset,set,j1,k1,Y[0]);
JK_0 u2 (clk,reset,set,j2,k2,Y[1]);
JK_0 u3 (clk,reset,set,j3,k3,Y[2]);
JK_0 u4 (clk,reset,set,j4,k4,Y[3]);

endmodule
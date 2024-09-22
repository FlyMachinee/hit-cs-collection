`timescale 1ns / 1ps
module JK_sim();
reg Reset, Set, clk;
wire Q;
reg J, K;

JK u(clk, Reset, Set, J, K, Q);
initial
    begin
    Reset = 0;
    Set = 0;
    clk = 1;
    J = 0;
    K = 0;
    #80 Reset = 1;
    #40 Set = 1;
    end
always #20{J, K} = {J, K} + 1;
always #10 clk = ~clk;
endmodule
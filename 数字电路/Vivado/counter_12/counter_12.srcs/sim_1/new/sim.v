`timescale 1ns / 1ps
module sim_dev1();
reg reset,set,clk;
wire [3:0]Y;

initial
    begin
        reset = 0;
        set = 0;
        clk = 1;
        #40 set = 1;
        #40 reset = 1;
    end
always#20 clk = ~clk;
counter_12 u(reset,set,clk,Y);
endmodule
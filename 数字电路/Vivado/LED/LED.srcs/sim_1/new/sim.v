`timescale 1ns/1ns
module sim_dev1();
parameter T=1000;
reg clk;
reg reset;
wire [7:0] led8;

initial 
begin
clk=1'b0;
reset=1'b0;
#(T+1) reset=1'b1;
end

always #(T/2) clk=~clk;

led u1(
.clk(clk),
.reset(reset),
.led(led8)
);

endmodule

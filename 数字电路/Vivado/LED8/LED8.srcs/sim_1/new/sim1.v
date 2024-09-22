`timescale 1ns / 1ps
module led8_tb;

	// Inputs
	reg clk;
	reg rst_n;
	reg [7:0] user;

	// Outputs
	wire  led;

	// Instantiate the Unit Under Test (UUT)
	led8 uut (
		.clk(clk), 
		.rst_n(rst_n), 
		.user(user), 
		.led(led)
	);
always #10 clk = ~clk;
	initial begin
		// Initialize Inputs
		clk = 0;
		rst_n = 0;
		user = 0;

		// Wait 100 ns for global reset to finish
		#100;
      rst_n = 1; 
		
		user = 8'b1011_0101;
		// Add stimulus here

	end
 
endmodule

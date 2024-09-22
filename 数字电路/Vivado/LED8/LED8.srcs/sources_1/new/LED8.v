`timescale 1ns / 1ps

module led8(
	input						clk,
	input 					    rst_n,
	input			[7:0]		user,
	output 		    reg			led
    );
reg [31:0]	cnt;
parameter counter = 500;
		
always@(posedge clk or negedge rst_n)begin
	if(!rst_n)begin
		cnt <= 1'b0;
		end 
	else if(cnt==500_000-1)begin
		cnt <= 1'b0;
		end
	else begin
		cnt <= cnt + 1'b1;
		end
	end
always@(posedge clk or negedge rst_n)begin
		if(!rst_n)begin
			led <= 1'b0;
			end 
		else if(cnt==counter-1)begin
			led <= user[7];
			end
		else if(cnt==2*counter-1)begin
			led <= user[6];
			end
		else if(cnt==3*counter-1)begin
			led <= user[5];
			end
		else if(cnt==4*counter-1)begin
			led <= user[4];
			end
		else if(cnt==5*counter-1)begin
			led <= user[3];
			end
		else if(cnt==6*counter-1)begin
			led <= user[2];
			end
		else if(cnt==7*counter-1)begin
			led <= user[1];
			end
		else if(cnt==8*counter-1)begin
			led <= user[0];
		end
	end
endmodule

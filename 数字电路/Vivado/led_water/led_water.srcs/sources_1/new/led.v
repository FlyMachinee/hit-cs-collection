`timescale 1ns / 1ps
module led(
    clk, 
    reset, 
    led 
);
input clk;
input reset;
output [7:0] led;

reg [7:0] led;
reg [31:0] counter; 
reg [1:0] state; 


always @(posedge clk or negedge reset)
    begin
        if(!reset) 
            begin
                counter <= 32'd0;
            end
        else if ( counter == 32'd10000000) //change T
            begin
                counter <= 32'd0;
            end
        else 
            begin
                counter <= counter + 32'd1;
            end
        end
        

always @(posedge clk or negedge reset)
    begin
        if(!reset) 
            begin
                state <= 1'd0;
            end
        else if( counter == 32'd0 )
            begin
            state <= 1'd1;
            end
        else
            begin
            state <= 1'd0;
            end
        
    end
    

always @(posedge clk or negedge reset)
    begin
        if(!reset) 
            begin
                led <= 8'b1111_1111;
            end
        else 
            begin
                if(state == 1'd1)
                begin
                    if(led == 8'b1111_1111)
                    begin
                        led <= 8'b0000_0001;
                    end
                    else if(led == 8'b1000_0000)
                    begin
                        led <= 8'b0000_0001;
                    end
                    else
                    begin
                        led <= led << 1'b1;
                    end
                end
            end
    end

endmodule
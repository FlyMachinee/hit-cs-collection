`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 2023/11/28 19:17:38
// Design Name: 
// Module Name: Big_Project
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
/////////////////////////////////////////////////////////////////////////////////
module Big_Project(
    input wire clk,
    input wire [5:0] initial_minutes,
    input wire set_zero_A, // 清空对应时钟
    input wire set_zero_B,
    
    input wire btn_A,
    input wire btn_B,
    input wire btn_start_and_pause,
    
    output wire [7:0] nixie_seg0,
    output wire [3:0] nixie_addr0,
    output wire [7:0] nixie_seg1,
    output wire [3:0] nixie_addr1,
    
    output wire [3:0] state_led_A,
    output wire [3:0] state_led_B,
    output wire [2:0] score_led_A,
    output wire [2:0] score_led_B
);

reg [2:0] state = 0; // 0为正在设置时间，1为正在倒计时，2为暂停中，3为本小局游戏结束，4为本局游戏结束
reg [1:0] win_round_A = 0, win_round_B = 0; // 各自的胜利局数
wire [3:0] score_A, score_B;
reg pause = 0; // 是否正在暂停
reg set_time = 0; // 是否设置时间
wire [15:0] set_seconds; // 设置的秒数
reg [7:0] nixie_work_state = 8'b11111111; // 8个数码管的工作状态
reg [31:0] btn_sp_counter = 32'd100_000_000; // btn_start_and_pause两次响应时间间隔为1秒
reg led_flow_type = 0; // 状态led的流动模式
reg led_flow_work_A = 0, led_flow_work_B = 0; // 各个状态led的工作使能
reg nixie_model = 0; // 数码管输出模式，0为时间输出，1为分数输出

wire rs_out, rs_out_reverse; // RS触发器的输出
wire clk_rs; // 送至RS触发器的时钟
assign clk_rs = clk & ~pause; // 暂停时触发器应该对按钮不响应
RS_Trigger u_rs(btn_A, btn_B, clk_rs, rs_out, rs_out_reverse);

// 计算设置的秒数
assign set_seconds = {{10{1'b0}}, initial_minutes[5:0]} * 16'd60;
wire [15:0] time_A, time_B; // 计数器的总秒数输出
Counter u_counter_A(~pause & set_zero_A, set_time, set_seconds, clk, pause | rs_out, 0, time_A);
Counter u_counter_B(~pause & set_zero_B, set_time, set_seconds, clk, pause | rs_out_reverse, 0, time_B);

wire [15:0] digits_A, digits_B; // 双方总秒数的译码结果，各自4个8421BCD码
Decode_16bits_to_8421 u_counter_decode_A(time_A, digits_A);
Decode_16bits_to_8421 u_counter_decode_B(time_B, digits_B);

assign score_A = 4'd3 * {{2{1'b0}},win_round_A};
assign score_B = 4'd3 * {{2{1'b0}},win_round_B};
wire [3:0] first_digit_of_A, first_digit_of_B;
Mux_8421_2_to_1 u_mux_1(digits_A[3:0], score_A, nixie_model, first_digit_of_A);
Mux_8421_2_to_1 u_mux_2(digits_B[3:0], score_B, nixie_model, first_digit_of_B);

wire [7:0] nixie_0, nixie_1, nixie_2, nixie_3, nixie_4, nixie_5, nixie_6, nixie_7;
// 将译码结果送至输出
Nixie_Tube_Decode_typeA u_nixie_0(first_digit_of_B, nixie_work_state[0], nixie_0);
Nixie_Tube_Decode_typeA u_nixie_1(digits_B[7:4], nixie_work_state[1], nixie_1);
Nixie_Tube_Decode_typeA u_nixie_2(digits_B[11:8], nixie_work_state[2], nixie_2);
Nixie_Tube_Decode_typeB u_nixie_3(digits_B[15:12], nixie_work_state[3], nixie_3);
Nixie_Tube_Decode_typeA u_nixie_4(first_digit_of_A, nixie_work_state[4], nixie_4);
Nixie_Tube_Decode_typeA u_nixie_5(digits_A[7:4], nixie_work_state[5], nixie_5);
Nixie_Tube_Decode_typeA u_nixie_6(digits_A[11:8], nixie_work_state[6], nixie_6);
Nixie_Tube_Decode_typeB u_nixie_7(digits_A[15:12], nixie_work_state[7], nixie_7);
// 由输出驱动器输出至板卡
Nixie_Show_Driver u_nixie_driver_0(nixie_0, nixie_1, {~nixie_model,nixie_2[6:0]}, nixie_3, clk, nixie_addr0, nixie_seg0);
Nixie_Show_Driver u_nixie_driver_1(nixie_4, nixie_5, {~nixie_model,nixie_6[6:0]}, nixie_7, clk, nixie_addr1, nixie_seg1);

// 状态LED显示
LED_flow u_state_A(clk, led_flow_work_A, led_flow_type, state_led_A);
LED_flow u_state_B(clk, led_flow_work_B, led_flow_type, state_led_B);

// 分数LED显示
LED_score u_score_A(1, win_round_A, score_led_A); 
LED_score u_score_B(1, win_round_B, score_led_B);

// 根据当前状态进行相应操作
always @(posedge clk) begin
    if (btn_sp_counter > 32'b0)
        btn_sp_counter = btn_sp_counter - 1;
    case (state)
        3'd0: // 正在设置时间
            begin
                pause = 1;
                set_time = 1;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // 上升沿，在设置时间时按下了btn_start_and_pause按钮
                    state = 1; // 计时开始
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd1: // 正在倒计时
            begin
                pause = 0;
                set_time = 0;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // 上升沿，在计时时按下了btn_start_and_pause按钮
                    state = 2; // 计时暂停
                    btn_sp_counter = 32'd100_000_000;
                end
                if (time_A == 0 || time_B == 0) // 一方时间清零
                    state = 3;
            end
        3'd2: // 正在暂停
            begin
                pause = 1;
                set_time = 0;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // 上升沿，在暂停时按下了btn_start_and_pause按钮
                    state = 1; // 计时继续
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd3: // 一方时间清零
            begin
                pause = 1;
                set_time = 0;
                led_flow_type = 1;
                if (time_A == 0) begin
                    led_flow_work_B = 1;
                    led_flow_work_A = 0;
                end
                else begin
                    led_flow_work_B = 0;
                    led_flow_work_A = 1;
                end
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                    
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin
                    if (time_A == 0)
                        win_round_B = win_round_B + 1;
                    else
                        win_round_A = win_round_A + 1;
                    
                    if (win_round_A >= 2 || win_round_B >= 2) // 三局两胜
                        state = 4; // 本局游戏结束
                    else
                        state = 0; // 本局游戏尚未结束
                        
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd4: // 本局游戏结束
            begin
                pause = 1;
                set_time = 0;
                led_flow_type = 0;
                if (win_round_B > win_round_A) begin
                    led_flow_work_B = 1;
                    led_flow_work_A = 0;
                end
                else begin
                    led_flow_work_B = 0;
                    led_flow_work_A = 1;
                end
                nixie_model = 1;
                nixie_work_state = 8'b00010001;
            
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin
                    win_round_A = 0;
                    win_round_B = 0;
                    state = 0;
                    btn_sp_counter = 32'd100_000_000;
                end
            end
    endcase 
end

endmodule

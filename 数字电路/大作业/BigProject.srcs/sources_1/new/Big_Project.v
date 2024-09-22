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
    input wire set_zero_A, // ��ն�Ӧʱ��
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

reg [2:0] state = 0; // 0Ϊ��������ʱ�䣬1Ϊ���ڵ���ʱ��2Ϊ��ͣ�У�3Ϊ��С����Ϸ������4Ϊ������Ϸ����
reg [1:0] win_round_A = 0, win_round_B = 0; // ���Ե�ʤ������
wire [3:0] score_A, score_B;
reg pause = 0; // �Ƿ�������ͣ
reg set_time = 0; // �Ƿ�����ʱ��
wire [15:0] set_seconds; // ���õ�����
reg [7:0] nixie_work_state = 8'b11111111; // 8������ܵĹ���״̬
reg [31:0] btn_sp_counter = 32'd100_000_000; // btn_start_and_pause������Ӧʱ����Ϊ1��
reg led_flow_type = 0; // ״̬led������ģʽ
reg led_flow_work_A = 0, led_flow_work_B = 0; // ����״̬led�Ĺ���ʹ��
reg nixie_model = 0; // ��������ģʽ��0Ϊʱ�������1Ϊ�������

wire rs_out, rs_out_reverse; // RS�����������
wire clk_rs; // ����RS��������ʱ��
assign clk_rs = clk & ~pause; // ��ͣʱ������Ӧ�ö԰�ť����Ӧ
RS_Trigger u_rs(btn_A, btn_B, clk_rs, rs_out, rs_out_reverse);

// �������õ�����
assign set_seconds = {{10{1'b0}}, initial_minutes[5:0]} * 16'd60;
wire [15:0] time_A, time_B; // �����������������
Counter u_counter_A(~pause & set_zero_A, set_time, set_seconds, clk, pause | rs_out, 0, time_A);
Counter u_counter_B(~pause & set_zero_B, set_time, set_seconds, clk, pause | rs_out_reverse, 0, time_B);

wire [15:0] digits_A, digits_B; // ˫����������������������4��8421BCD��
Decode_16bits_to_8421 u_counter_decode_A(time_A, digits_A);
Decode_16bits_to_8421 u_counter_decode_B(time_B, digits_B);

assign score_A = 4'd3 * {{2{1'b0}},win_round_A};
assign score_B = 4'd3 * {{2{1'b0}},win_round_B};
wire [3:0] first_digit_of_A, first_digit_of_B;
Mux_8421_2_to_1 u_mux_1(digits_A[3:0], score_A, nixie_model, first_digit_of_A);
Mux_8421_2_to_1 u_mux_2(digits_B[3:0], score_B, nixie_model, first_digit_of_B);

wire [7:0] nixie_0, nixie_1, nixie_2, nixie_3, nixie_4, nixie_5, nixie_6, nixie_7;
// ���������������
Nixie_Tube_Decode_typeA u_nixie_0(first_digit_of_B, nixie_work_state[0], nixie_0);
Nixie_Tube_Decode_typeA u_nixie_1(digits_B[7:4], nixie_work_state[1], nixie_1);
Nixie_Tube_Decode_typeA u_nixie_2(digits_B[11:8], nixie_work_state[2], nixie_2);
Nixie_Tube_Decode_typeB u_nixie_3(digits_B[15:12], nixie_work_state[3], nixie_3);
Nixie_Tube_Decode_typeA u_nixie_4(first_digit_of_A, nixie_work_state[4], nixie_4);
Nixie_Tube_Decode_typeA u_nixie_5(digits_A[7:4], nixie_work_state[5], nixie_5);
Nixie_Tube_Decode_typeA u_nixie_6(digits_A[11:8], nixie_work_state[6], nixie_6);
Nixie_Tube_Decode_typeB u_nixie_7(digits_A[15:12], nixie_work_state[7], nixie_7);
// �����������������忨
Nixie_Show_Driver u_nixie_driver_0(nixie_0, nixie_1, {~nixie_model,nixie_2[6:0]}, nixie_3, clk, nixie_addr0, nixie_seg0);
Nixie_Show_Driver u_nixie_driver_1(nixie_4, nixie_5, {~nixie_model,nixie_6[6:0]}, nixie_7, clk, nixie_addr1, nixie_seg1);

// ״̬LED��ʾ
LED_flow u_state_A(clk, led_flow_work_A, led_flow_type, state_led_A);
LED_flow u_state_B(clk, led_flow_work_B, led_flow_type, state_led_B);

// ����LED��ʾ
LED_score u_score_A(1, win_round_A, score_led_A); 
LED_score u_score_B(1, win_round_B, score_led_B);

// ���ݵ�ǰ״̬������Ӧ����
always @(posedge clk) begin
    if (btn_sp_counter > 32'b0)
        btn_sp_counter = btn_sp_counter - 1;
    case (state)
        3'd0: // ��������ʱ��
            begin
                pause = 1;
                set_time = 1;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // �����أ�������ʱ��ʱ������btn_start_and_pause��ť
                    state = 1; // ��ʱ��ʼ
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd1: // ���ڵ���ʱ
            begin
                pause = 0;
                set_time = 0;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // �����أ��ڼ�ʱʱ������btn_start_and_pause��ť
                    state = 2; // ��ʱ��ͣ
                    btn_sp_counter = 32'd100_000_000;
                end
                if (time_A == 0 || time_B == 0) // һ��ʱ������
                    state = 3;
            end
        3'd2: // ������ͣ
            begin
                pause = 1;
                set_time = 0;
                led_flow_type = 1;
                led_flow_work_B = 0;
                led_flow_work_A = 0;
                nixie_model = 0;
                nixie_work_state = 8'b11111111;
                if (btn_start_and_pause && (btn_sp_counter == 0)) begin // �����أ�����ͣʱ������btn_start_and_pause��ť
                    state = 1; // ��ʱ����
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd3: // һ��ʱ������
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
                    
                    if (win_round_A >= 2 || win_round_B >= 2) // ������ʤ
                        state = 4; // ������Ϸ����
                    else
                        state = 0; // ������Ϸ��δ����
                        
                    btn_sp_counter = 32'd100_000_000;
                end
            end
        3'd4: // ������Ϸ����
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

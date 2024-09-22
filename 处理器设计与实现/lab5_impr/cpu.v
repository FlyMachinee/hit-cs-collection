`define NULL 32'hz

module cpu (
    input clk,    // 时钟信号
    input resetn, // 低有效复位信号

    output        inst_sram_en,    // 指令存储器读使能
    output [31:0] inst_sram_addr,  // 指令存储器读地址
    input  [31:0] inst_sram_rdata, // 指令存储器读出的数据

    output        data_sram_en,     // 数据存储器端口读/写使能
    output [ 3:0] data_sram_wen,    // 数据存储器写使能
    output [31:0] data_sram_addr,   // 数据存储器读/写地址
    output [31:0] data_sram_wdata,  // 写入数据存储器的数据
    input  [31:0] data_sram_rdata,  // 数据存储器读出的数据

    // 供自动测试环境进行CPU正确性检查
    output [31:0] debug_wb_pc,  // 当前正在执行指令的PC
    output debug_wb_rf_wen,  // 当前通用寄存器组的写使能信号

    output [ 4:0] debug_wb_rf_wnum,  // 当前通用寄存器组写回的寄存器编号
    output [31:0] debug_wb_rf_wdata  // 当前指令需要写回的数据
);

  // 节拍发生器相关
  wire T1;
  wire T2;
  wire T3;
  beat_generator U_beat_generator (
      .clk(clk),
      .resetn(resetn),
      .T({T1, T2, T3})
  );

  assign inst_sram_en = T3;

  // 程序计数器相关
  reg  [31:0] pc = 32'h00000000;
  wire [31:0] npc = pc + 4;
  assign inst_sram_addr = pc;

  // 指令字段提取
  wire [5:0] op = inst_sram_rdata[31:26];
  wire [5:0] funct = inst_sram_rdata[5:0];
  wire [4:0] rs = inst_sram_rdata[25:21];
  wire [4:0] rt = inst_sram_rdata[20:16];
  wire [4:0] rd = inst_sram_rdata[15:11];
  wire [4:0] shamt = inst_sram_rdata[10:6];
  wire [15:0] offset = inst_sram_rdata[15:0];
  wire [25:0] instr_index = inst_sram_rdata[25:0];

  // 译码信号定义
  wire do_alu;
  wire [4:0] alu_op;
  wire do_movz;
  wire do_mem_read;
  wire do_mem_write;
  wire do_bit_test;
  wire do_jump;

  // 译码器实例化
  my_decoder U_decoder (
      .op(op),
      .funct(funct),
      .do_alu(do_alu),
      .alu_op(alu_op),
      .do_movz(do_movz),
      .do_mem_read(do_mem_read),
      .do_mem_write(do_mem_write),
      .do_bit_test(do_bit_test),
      .do_jump(do_jump)
  );

  // 寄存器堆相关
  wire reg_write;  // 稍后赋值
  wire [4:0] reg_write_addr = do_mem_read ? rt : rd;
  wire no_write_r0 = |reg_write_addr;
  wire reg_write_filtered = reg_write & no_write_r0;
  wire [31:0] rs_data;
  wire [31:0] rt_data;
  wire [31:0] reg_write_data;  // 稍后赋值

  reg_heap U_reg_heap (
      .clk(clk),
      .resetn(resetn),
      .raddr1(rs),
      .raddr2(rt),
      .we(reg_write_filtered),
      .waddr(reg_write_addr),
      .wdata(reg_write_data),
      .rdata1(rs_data),
      .rdata2(rt_data)
  );

  // 存储器相关
  assign data_sram_wen = do_mem_write & T2 ? 4'b1111 : 4'b0000;
  assign data_sram_en  = (do_mem_write & T2) | (do_mem_read & T1);
  wire [31:0] offset_ext = {{16{offset[15]}}, offset};
  assign data_sram_addr  = rs_data + offset_ext;
  assign data_sram_wdata = rt_data;

  // ALU相关
  wire [31:0] alu_res;
  my_alu U_alu (
      .A(rs_data),
      .B(rt_data),
      .shamt(shamt),
      .alu_op(alu_op),
      .F(alu_res)
  );

  // 其他杂项,
  wire rt_is_zero = ~|rt_data;
  wire exec_movz = do_movz & rt_is_zero;

  // 寄存器写使能、写数据信号赋值
  assign reg_write = do_mem_read | do_alu | exec_movz;
  assign reg_write_data = exec_movz ? rs_data :
          do_alu ? alu_res :
          do_mem_read ? data_sram_rdata : `NULL;

  // 跳转与位测试相关
  wire [31:0] jump_addr = {npc[31:28], instr_index, 2'b00};
  wire [31:0] bit_test_addr = npc + {offset_ext[29:0], 2'b00};
  wire [31:0] branch_addr = do_jump ? jump_addr : bit_test_addr;
  wire bit_test_res = rs_data[rt];
  wire do_branch = do_jump | (do_bit_test & bit_test_res);

  // 程序计数器更新逻辑
  always @(posedge T3) begin
    if (!resetn) begin
      pc <= 32'h00000000;
    end else begin
      pc <= do_branch ? branch_addr : npc;
    end
  end

  // 调试信息相关
  reg [31:0] pc_cached;
  always @(posedge T1) begin
    pc_cached <= pc;
  end
  assign debug_wb_pc = pc_cached;
  assign debug_wb_rf_wen = reg_write_filtered & T3;
  assign debug_wb_rf_wnum = reg_write_addr;
  assign debug_wb_rf_wdata = reg_write_data;

endmodule

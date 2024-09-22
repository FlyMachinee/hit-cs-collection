// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Wed Nov  8 18:25:23 2023
// Host        : Other_Laptop running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub
//               e:/Users/14276/counter_12/counter_12.srcs/sources_1/ip/JK_0/JK_0_stub.v
// Design      : JK_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7a35tcsg324-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "JK,Vivado 2020.1" *)
module JK_0(clk, Reset, Set, J, K, Q)
/* synthesis syn_black_box black_box_pad_pin="clk,Reset,Set,J,K,Q" */;
  input clk;
  input Reset;
  input Set;
  input J;
  input K;
  output Q;
endmodule

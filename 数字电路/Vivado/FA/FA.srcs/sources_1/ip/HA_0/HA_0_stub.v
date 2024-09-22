// Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
// --------------------------------------------------------------------------------
// Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
// Date        : Wed Nov  1 15:23:58 2023
// Host        : Other_Laptop running 64-bit major release  (build 9200)
// Command     : write_verilog -force -mode synth_stub e:/Users/14276/FA/FA.srcs/sources_1/ip/HA_0/HA_0_stub.v
// Design      : HA_0
// Purpose     : Stub declaration of top-level module interface
// Device      : xc7vx485tffg1157-1
// --------------------------------------------------------------------------------

// This empty module with port declaration file causes synthesis tools to infer a black box for IP.
// The synthesis directives are for Synopsys Synplify support to prevent IO buffer insertion.
// Please paste the declaration into a Verilog source file or add the file as an additional source.
(* X_CORE_INFO = "HA,Vivado 2020.1" *)
module HA_0(a, b, S, C)
/* synthesis syn_black_box black_box_pad_pin="a,b,S,C" */;
  input a;
  input b;
  output S;
  output C;
endmodule

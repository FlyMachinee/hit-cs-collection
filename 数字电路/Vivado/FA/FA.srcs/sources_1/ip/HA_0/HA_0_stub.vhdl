-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Nov  1 15:23:58 2023
-- Host        : Other_Laptop running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode synth_stub e:/Users/14276/FA/FA.srcs/sources_1/ip/HA_0/HA_0_stub.vhdl
-- Design      : HA_0
-- Purpose     : Stub declaration of top-level module interface
-- Device      : xc7vx485tffg1157-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

entity HA_0 is
  Port ( 
    a : in STD_LOGIC;
    b : in STD_LOGIC;
    S : out STD_LOGIC;
    C : out STD_LOGIC
  );

end HA_0;

architecture stub of HA_0 is
attribute syn_black_box : boolean;
attribute black_box_pad_pin : string;
attribute syn_black_box of stub : architecture is true;
attribute black_box_pad_pin of stub : architecture is "a,b,S,C";
attribute X_CORE_INFO : string;
attribute X_CORE_INFO of stub : architecture is "HA,Vivado 2020.1";
begin
end;

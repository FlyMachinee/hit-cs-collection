-- Copyright 1986-2020 Xilinx, Inc. All Rights Reserved.
-- --------------------------------------------------------------------------------
-- Tool Version: Vivado v.2020.1 (win64) Build 2902540 Wed May 27 19:54:49 MDT 2020
-- Date        : Wed Nov  8 18:25:23 2023
-- Host        : Other_Laptop running 64-bit major release  (build 9200)
-- Command     : write_vhdl -force -mode funcsim
--               e:/Users/14276/counter_12/counter_12.srcs/sources_1/ip/JK_0/JK_0_sim_netlist.vhdl
-- Design      : JK_0
-- Purpose     : This VHDL netlist is a functional simulation representation of the design and should not be modified or
--               synthesized. This netlist cannot be used for SDF annotated simulation.
-- Device      : xc7a35tcsg324-1
-- --------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity JK_0_JK is
  port (
    Q : out STD_LOGIC;
    clk : in STD_LOGIC;
    Reset : in STD_LOGIC;
    Set : in STD_LOGIC;
    K : in STD_LOGIC;
    J : in STD_LOGIC
  );
  attribute ORIG_REF_NAME : string;
  attribute ORIG_REF_NAME of JK_0_JK : entity is "JK";
end JK_0_JK;

architecture STRUCTURE of JK_0_JK is
  signal \^q\ : STD_LOGIC;
  signal q_i_1_n_0 : STD_LOGIC;
begin
  Q <= \^q\;
q_i_1: unisim.vcomponents.LUT5
    generic map(
      INIT => X"2AAA0A8A"
    )
        port map (
      I0 => Reset,
      I1 => \^q\,
      I2 => Set,
      I3 => K,
      I4 => J,
      O => q_i_1_n_0
    );
q_reg: unisim.vcomponents.FDRE
     port map (
      C => clk,
      CE => '1',
      D => q_i_1_n_0,
      Q => \^q\,
      R => '0'
    );
end STRUCTURE;
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library UNISIM;
use UNISIM.VCOMPONENTS.ALL;
entity JK_0 is
  port (
    clk : in STD_LOGIC;
    Reset : in STD_LOGIC;
    Set : in STD_LOGIC;
    J : in STD_LOGIC;
    K : in STD_LOGIC;
    Q : out STD_LOGIC
  );
  attribute NotValidForBitStream : boolean;
  attribute NotValidForBitStream of JK_0 : entity is true;
  attribute CHECK_LICENSE_TYPE : string;
  attribute CHECK_LICENSE_TYPE of JK_0 : entity is "JK_0,JK,{}";
  attribute DowngradeIPIdentifiedWarnings : string;
  attribute DowngradeIPIdentifiedWarnings of JK_0 : entity is "yes";
  attribute IP_DEFINITION_SOURCE : string;
  attribute IP_DEFINITION_SOURCE of JK_0 : entity is "package_project";
  attribute X_CORE_INFO : string;
  attribute X_CORE_INFO of JK_0 : entity is "JK,Vivado 2020.1";
end JK_0;

architecture STRUCTURE of JK_0 is
  attribute X_INTERFACE_INFO : string;
  attribute X_INTERFACE_INFO of Reset : signal is "xilinx.com:signal:reset:1.0 Reset RST";
  attribute X_INTERFACE_PARAMETER : string;
  attribute X_INTERFACE_PARAMETER of Reset : signal is "XIL_INTERFACENAME Reset, POLARITY ACTIVE_LOW, INSERT_VIP 0";
  attribute X_INTERFACE_INFO of clk : signal is "xilinx.com:signal:clock:1.0 clk CLK";
  attribute X_INTERFACE_PARAMETER of clk : signal is "XIL_INTERFACENAME clk, ASSOCIATED_RESET Reset, FREQ_HZ 100000000, FREQ_TOLERANCE_HZ 0, PHASE 0.000, INSERT_VIP 0";
begin
inst: entity work.JK_0_JK
     port map (
      J => J,
      K => K,
      Q => Q,
      Reset => Reset,
      Set => Set,
      clk => clk
    );
end STRUCTURE;

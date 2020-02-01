library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity MixColumns is 
port(
	incol : in std_logic_vector(127 downto 0);
	outcol : out std_logic_vector(127 downto 0)
);
end MixColumns;


ARCHITECTURE default of MixColumns is



component GLPLUT2
port(
	inval : in std_logic_vector(7 downto 0);
	outval : out std_logic_vector(7 downto 0)
);
end component;

component GLPLUT3
port(
	inval : in std_logic_vector(7 downto 0);
	outval : out std_logic_vector(7 downto 0)
);
end component;

component XOR32 is

port(
 in1 : in std_logic_vector(7 downto 0);
 in2 : in std_logic_vector(7 downto 0);
 in3 : in std_logic_vector(7 downto 0);
 in4 : in std_logic_vector(7 downto 0);
 out1 : out std_logic_vector(7 downto 0)
);
end component;

SIGNAL glp2out0 : std_logic_vector(31 downto 0);
SIGNAL glp3out0 : std_logic_vector(31 downto 0);
SIGNAL glp2out1 : std_logic_vector(31 downto 0);
SIGNAL glp3out1 : std_logic_vector(31 downto 0);
SIGNAL glp2out2 : std_logic_vector(31 downto 0);
SIGNAL glp3out2 : std_logic_vector(31 downto 0);
SIGNAL glp2out3 : std_logic_vector(31 downto 0);
SIGNAL glp3out3 : std_logic_vector(31 downto 0);
BEGIN

	m:for k in 0 to 3 generate
		inst0 : GLPLUT2 port map (incol(k*8+7 downto k*8), glp2out1(k*8+7 downto k*8));
		inst1 : GLPLUT3 port map (incol(4*8+k*8+7 downto 4*8+k*8), glp3out1(k*8+7 downto k*8));
		inst2 : XOR32 port map(glp2out1(k*8+7 downto k*8), glp3out1(k*8+7 downto k*8), incol(8*8+k*8+7 downto 8*8+k*8),incol(12*8+k*8+7 downto 12*8+k*8),outcol(k*8+7 downto k*8));
		
		inst3 : GLPLUT2 port map (incol(4*8+k*8+7 downto 4*8+k*8), glp2out2(k*8+7 downto k*8));
		inst4 : GLPLUT3 port map (incol(8*8+k*8+7 downto 8*8+k*8), glp3out2(k*8+7 downto k*8));
		inst5 : XOR32 port map(glp2out2(k*8+7 downto k*8), glp3out2(k*8+7 downto k*8), incol(12*8+k*8+7 downto 12*8+k*8),incol(k*8+7 downto k*8),outcol(4*8+k*8+7 downto 4*8+k*8));
		
		inst6 : GLPLUT2 port map (incol(8*8+k*8+7 downto 8*8+k*8), glp2out3(k*8+7 downto k*8));
		inst7 : GLPLUT3 port map (incol(12*8+k*8+7 downto 12*8+k*8), glp3out3(k*8+7 downto k*8));
		inst8 : XOR32 port map(glp2out3(k*8+7 downto k*8), glp3out3(k*8+7 downto k*8), incol(k*8+7 downto k*8),incol(4*8+k*8+7 downto 4*8+k*8),outcol(8*8+k*8+7 downto 8*8+k*8));

		inst9 : GLPLUT2 port map (incol(12*8+k*8+7 downto 12*8+k*8), glp2out0(k*8+7 downto k*8));
		inst10 : GLPLUT3 port map (incol(k*8+7 downto k*8), glp3out0(k*8+7 downto k*8));
		inst11 : XOR32 port map(glp2out0(k*8+7 downto k*8), glp3out0(k*8+7 downto k*8), incol(4*8+k*8+7 downto 4*8+k*8),incol(8*8+k*8+7 downto 8*8+k*8),outcol(12*8+k*8+7 downto 12*8+k*8));
				
	end generate;

END default;
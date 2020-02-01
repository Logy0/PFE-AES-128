library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity ASS is
port(
	ekey_k : in std_logic_vector(127 downto 0);
	instate : in std_logic_vector(127 downto 0);
	outstate : out std_logic_vector(127 downto 0)
	
);
end ASS;

ARCHITECTURE default of ASS is

SIGNAL xor_out : std_logic_vector(127 downto 0);
SIGNAL sbox_out : std_logic_vector(127 downto 0);

signal k: integer:=0;

component AddRoundKey
port(
		 in1 : in std_logic_vector(127 downto 0);
		 in2 : in std_logic_vector(127 downto 0);
		 out1 : out std_logic_vector(127 downto 0)
);
end component;

component Sbox
port(
		input : in std_logic_vector(7 downto 0);
		out_data : out std_logic_vector(7 downto 0)		
);
end component;

component RotWord
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)
);
end component;

component RotWord2
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)
);
end component;

component RotWord3
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)
);
end component;

BEGIN
	--A
	instA: AddRoundKey port map (instate, ekey_k, xor_out); 

	--S
	S:for k in 0 to 15 generate 
		inst1: Sbox port map (xor_out(k*8+7 downto k*8), sbox_out(k*8+7 downto k*8));
	end generate;
	  
	outstate(31 downto 0)<=sbox_out(31 downto 0);
	
	inst2: RotWord port map (sbox_out(63 downto 32), outstate(63 downto 32)); 
	inst3: RotWord2 port map (sbox_out(95 downto 64), outstate(95 downto 64));
	inst4: RotWord3 port map (sbox_out(127 downto 96), outstate(127 downto 96));

		 
END default;

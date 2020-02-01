library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.numeric_std;

entity AddRoundKey is

port(
 in1 : in std_logic_vector(127 downto 0);
 in2 : in std_logic_vector(127 downto 0);
 out1 : out std_logic_vector(127 downto 0)
);
end AddRoundKey;

ARCHITECTURE default of AddRoundKey is

signal k : integer:=0;

BEGIN
	
	a:for k in 0 to 127 generate
		 out1(k)<=in1(k) xor in2(k);
	  end generate;

end default;
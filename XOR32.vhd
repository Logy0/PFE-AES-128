library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
use ieee.numeric_std;

entity XOR32 is

port(
 in1 : in std_logic_vector(7 downto 0);
 in2 : in std_logic_vector(7 downto 0);
 in3 : in std_logic_vector(7 downto 0);
 in4 : in std_logic_vector(7 downto 0);
 out1 : out std_logic_vector(7 downto 0)
);
end XOR32;

ARCHITECTURE default of XOR32 is

signal k : integer:=0;

BEGIN
	a:for k in 0 to 7 generate
		 out1(k)<=in1(k) xor in2(k) xor in3(k) xor in4(k);
	  end generate;


end default;
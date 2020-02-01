library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity key_schedule is 
port(
		addr : out std_logic_vector(3 downto 0);
		key_data : in std_logic_vector(7 downto 0);
		clock : in std_logic;
		out_data : out std_logic_vector(7 downto 0);
		out_addr : out std_logic_vector(3 downto 0)
		
);
end key_schedule;


architecture keysch of key_schedule is 

	SIGNAL X : std_logic_vector(7 downto 0);
	
begin

	process (clock)
	variable AD : std_logic_vector(3 downto 0);	
	BEGIN
	AD:=("0000");
	if(clock'event and clock='0' and AD<"1111") then
		addr<=AD;
		if(clock'event and clock='1') then
			X<=key_data;
		end if;
		AD:=AD+1;
		
	end if;
	end process;
	
		
end keysch;
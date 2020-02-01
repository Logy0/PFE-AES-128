library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity RotWord is 
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)		
);
end RotWord;


architecture rot_arch of RotWord is 

SIGNAL B0 : std_logic_vector(7 downto 0);
SIGNAL B1 : std_logic_vector(7 downto 0);
SIGNAL B2 : std_logic_vector(7 downto 0);
SIGNAL B3 : std_logic_vector(7 downto 0);

begin

B0<=input(7 downto 0);
B1<=input(15 downto 8);
B2<=input(23 downto 16);
B3<=input(31 downto 24);

out_data<=(B0&B3&B2&B1);
	
end rot_arch;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity RotWord2 is 
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)		
);
end RotWord2;


architecture rot_arch of RotWord2 is 

SIGNAL B0 : std_logic_vector(7 downto 0);
SIGNAL B1 : std_logic_vector(7 downto 0);
SIGNAL B2 : std_logic_vector(7 downto 0);
SIGNAL B3 : std_logic_vector(7 downto 0);

begin

B0<=input(7 downto 0);
B1<=input(15 downto 8);
B2<=input(23 downto 16);
B3<=input(31 downto 24);

out_data<=(B1&B0&B3&B2);
	
end rot_arch;

library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity RotWord3 is 
port(
		input : in std_logic_vector(31 downto 0);
		out_data : out std_logic_vector(31 downto 0)		
);
end RotWord3;


architecture rot_arch of RotWord3 is 

SIGNAL B0 : std_logic_vector(7 downto 0);
SIGNAL B1 : std_logic_vector(7 downto 0);
SIGNAL B2 : std_logic_vector(7 downto 0);
SIGNAL B3 : std_logic_vector(7 downto 0);

begin

B0<=input(7 downto 0);
B1<=input(15 downto 8);
B2<=input(23 downto 16);
B3<=input(31 downto 24);

out_data<=(B2&B1&B0&B3);
	
end rot_arch;
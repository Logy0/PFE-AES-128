LIBRARY ieee;
USE ieee.std_logic_1164.all; 
LIBRARY work;

ENTITY Vhdl6 IS 
	PORT
	(
		I1 :  IN  STD_LOGIC;
		I2 :  IN  STD_LOGIC;
		CO :  OUT  STD_LOGIC;
		O : OUT STD_LOGIC;
		IO1 : OUT STD_LOGIC;
		IO2 : OUT STD_LOGIC
	);
END Vhdl6;

ARCHITECTURE bdf_type OF Vhdl6 IS 
	

BEGIN 

	O<=I1 xor I2;
	CO<=I1 and I2;
	IO1<=I1;
	IO2<=I2;

END bdf_type;
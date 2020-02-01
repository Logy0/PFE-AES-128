library IEEE;
use IEEE.STD_LOGIC_1164.all;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;
USE ieee.numeric_std; 


entity AES is 

port(
	mclk ,mrst ,mrx			: in	std_logic;		-- Main clock
	mtx : out std_logic;
	
	SEG1, SEG2, SEG3 : out std_logic_vector(6 downto 0);
	sel : in std_logic_vector(3 downto 0);
	addr : in std_logic_vector(3 downto 0)
);

end AES;


ARCHITECTURE aes_arch of AES is

 signal sendready : std_logic;
 signal req_tx : std_logic;
 signal data : std_logic_vector(7 downto 0);
 signal mrx_ready : std_logic;
 signal mrx_data : std_logic_vector(7 downto 0);
 
 signal ass_out : std_logic_vector(127 downto 0);
 signal mixcol_out : std_logic_vector(127 downto 0);
 signal aes_out : std_logic_vector(127 downto 0);
 signal disp : std_logic_vector(7 downto 0);
 signal carry : std_logic:='0';
 signal enable: std_logic:='0';
 signal counter : std_logic_vector(3 downto 0):="0000";
 signal ekey : std_logic_vector(127 downto 0):=x"00000000000000000000000000000000";
 signal state : std_logic_vector(127 downto 0):=x"FFBB7733EEAA6622DD995511CC884400";
 
signal key0 : std_logic_vector(127 downto 0):=x"0F0B07030E0A06020D0905010C080400";
signal key1 : std_logic_vector(127 downto 0):=x"FEF1FAFD76787274ABA6AFAAD6DAD2D6";
signal key2 : std_logic_vector(127 downto 0):=x"FE00F10BB3C5BDCF309B3D9268BE64B6";
signal key3 : std_logic_vector(127 downto 0):=x"41BFBF4EBF0CC9746959C2FF046CD2B6";
signal key4 : std_logic_vector(127 downto 0):=x"FDBC03BC8D323EF7056C35F7FDF99547";
signal key5 : std_logic_vector(127 downto 0):=x"AA57EBE822AF9DA3F6F39FAAAD50A93C";
signal key6 : std_logic_vector(127 downto 0):=x"6BC1967D1F3D920FA355A6390AA7F75E";
signal key7 : std_logic_vector(127 downto 0):=x"264D8C1AC0DFE270A90A5FF94E44E314";
signal key8 : std_logic_vector(127 downto 0):=x"D2F4B9357ABA6587BF161C43AEE0A447";
signal key9 : std_logic_vector(127 downto 0):=x"4E9C68D197ED57322C938599BE10F054";
signal keyA : std_logic_vector(127 downto 0):=x"C58B177F30A74A1D2B0794114DF3E313";
 
 

component mux11
	PORT
	(
		data0x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data10x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data1x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data2x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data3x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data4x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data5x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data6x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data7x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data8x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		data9x		: IN STD_LOGIC_VECTOR (127 DOWNTO 0);
		sel		: IN STD_LOGIC_VECTOR (3 DOWNTO 0);
		result		: OUT STD_LOGIC_VECTOR (127 DOWNTO 0)
	);
END component;

component HEXDISP IS 
	PORT
	(
		E :  IN  STD_LOGIC_VECTOR(3 downto 0);
		SEG :  OUT  STD_LOGIC_VECTOR(6 downto 0);
		enable : IN std_logic:='0'
	);
end component;

 
 component UART
	port(
	clk			: in	std_logic;		-- Main clock
	rst			: in	std_logic;		-- Main reset
	-- External Interface
	rx			: in	std_logic;		-- RS232 received serial data
	tx			: out	std_logic;		-- RS232 transmitted serial data
	-- RS232/UART Configuration
	par_en		: in	std_logic;		-- Parity bit enable
	-- uPC Interface
	tx_req		: in	std_logic;						-- Request SEND of data
	tx_end		: out	std_logic;						-- Data SENDED
	tx_data		: in	std_logic_vector(7 downto 0);	-- Data to transmit
	rx_ready	: out	std_logic;						-- Received data ready to uPC read
	rx_data		: out	std_logic_vector(7 downto 0)	-- Received data 

	);
 end component;
	
  
 
 component ASS 
 port(
		ekey_k : in std_logic_vector(127 downto 0);
		instate : in std_logic_vector(127 downto 0);
		outstate : out std_logic_vector(127 downto 0)
 );
 end component;
  
 component MixColumns
 port(
	incol : in std_logic_vector(127 downto 0);
	outcol : out std_logic_vector(127 downto 0)
 );
 end component;
 
 component mod10count
	PORT
	(
		clk_en		: IN STD_LOGIC ;
		clock		: IN STD_LOGIC ;
		sclr		: IN STD_LOGIC ;
		cout		: OUT STD_LOGIC ;
		q		: OUT STD_LOGIC_VECTOR (3 DOWNTO 0)
	);
END component;
 
component AddRoundKey is
port(
 in1 : in std_logic_vector(127 downto 0);
 in2 : in std_logic_vector(127 downto 0);
 out1 : out std_logic_vector(127 downto 0)
);
end component;

 
begin
--inst1 : UART port map (mclk, mrst, mrx, mtx, '0', req_tx, sendready, data, mrx_ready, mrx_data);

	disp0 : HEXDISP port map(disp(3 downto 0), seg1, enable);
	disp1 : HEXDISP port map(disp(7 downto 4), seg2, enable);
	disp2 : HEXDISP port map(counter, seg3, '1');

	
	
	inst0 : mux11 port map(key0, keyA, key1, key2, key3, key4, key5, key6, key7, key8, key9, counter, ekey);
	inst2 : ASS port map(ekey, state, ass_out);
	inst3 : MixColumns port map(ass_out, mixcol_out);
	
	inst4 : mod10count port map('1', mclk, '0', carry, counter);
	
	inst5 : AddRoundKey port map(ass_out, keyA, aes_out);
	
	
	
	disp<=aes_out(7 downto 0) when(sel=x"0")else
	  aes_out(15 downto 8) when(sel=x"4")else
	  aes_out(23 downto 16) when(sel=x"8")else
	  aes_out(31 downto 24) when(sel=x"C")else
	  aes_out(39 downto 32) when(sel=x"1")else
	  aes_out(47 downto 40) when(sel=x"5")else
	  aes_out(55 downto 48) when(sel=x"9")else
	  aes_out(63 downto 56) when(sel=x"D")else
	  aes_out(71 downto 64) when(sel=x"2")else
	  aes_out(79 downto 72) when(sel=x"6")else
	  aes_out(87 downto 80) when(sel=x"A")else
	  aes_out(95 downto 88) when(sel=x"E")else
	  aes_out(103 downto 96) when(sel=x"3")else
	  aes_out(111 downto 104) when(sel=x"7")else
	  aes_out(119 downto 112) when(sel=x"B")else
	  aes_out(127 downto 120);
				  
--
--	disp<=aes_out(7 downto 0) when(sel=x"0")else
--		  aes_out(15 downto 8) when(sel=x"1")else
--		  aes_out(23 downto 16) when(sel=x"2")else
--		  aes_out(31 downto 24) when(sel=x"3")else
--		  aes_out(39 downto 32) when(sel=x"4")else
--		  aes_out(47 downto 40) when(sel=x"5")else
--		  aes_out(55 downto 48) when(sel=x"6")else
--		  aes_out(63 downto 56) when(sel=x"7")else
--		  aes_out(71 downto 64) when(sel=x"8")else
--		  aes_out(79 downto 72) when(sel=x"9")else
--		  aes_out(87 downto 80) when(sel=x"A")else
--		  aes_out(95 downto 88) when(sel=x"B")else
--		  aes_out(103 downto 96) when(sel=x"C")else
--		  aes_out(111 downto 104) when(sel=x"D")else
--		  aes_out(119 downto 112) when(sel=x"E")else
--		  aes_out(127 downto 120);
			

		  
	aes:process(mclk, carry)
	begin 
		if mclk'event and mclk = '1' then
			if carry/='1' then
				state<=mixcol_out;
			else
				state<=x"FFBB7733EEAA6622DD995511CC884400";
			end if;
			if counter="1000" then
				enable<='1';
			else 
				enable<='0';
			end if;
		end if;
	end process;
	
	
	
--	timer_manager:process(mclk)
--	variable counter	:	integer range 0 to 128;
--	begin
--
--		if mclk'event and mclk = '1'
--				-- Normal Operation
--				memaddr <= sel;
--				if counter = 127 and sendready = '1' then
--					req_tx	<=	'1';
--
--							  
--					counter		:=	0;
--				else
--					req_tx	<=	'0';
--					counter		:=	counter + 1;
--				end if;
--				
--			
--				
--				if mrst = '1' then
--					memaddr <= "0000";
--					counter := 0;
--				end if;
--		
--				
--		end if;
--		
--	end process;

end aes_arch;
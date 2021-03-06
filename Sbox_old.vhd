library ieee;
use ieee.std_logic_1164.all;
use ieee.std_logic_unsigned.all;
use ieee.std_logic_arith.all;

entity Sbox_old is 
port(
		input : in std_logic_vector(7 downto 0);
		out_data : out std_logic_vector(7 downto 0)		
);
end Sbox_old;


architecture sbox_arch of Sbox_old is 


begin
	  out_data<=x"63" when(input=x"00") else
					x"7c" when(input=x"01") else
					x"77" when(input=x"02") else
					x"7b" when(input=x"03") else
					x"f2" when(input=x"04") else
					x"6b" when(input=x"05") else
					x"6f" when(input=x"06") else
					x"c5" when(input=x"07") else
					x"30" when(input=x"08") else
					x"01" when(input=x"09") else
					x"67" when(input=x"0a") else
					x"2b" when(input=x"0b") else
					x"fe" when(input=x"0c") else
					x"d7" when(input=x"0d") else
					x"ab" when(input=x"0e") else
					x"76" when(input=x"0f") else
					x"ca" when(input=x"10") else
					x"82" when(input=x"11") else
					x"c9" when(input=x"12") else
					x"7d" when(input=x"13") else
					x"fa" when(input=x"14") else
					x"59" when(input=x"15") else
					x"47" when(input=x"16") else
					x"f0" when(input=x"17") else
					x"ad" when(input=x"18") else
					x"d4" when(input=x"19") else
					x"a2" when(input=x"1a") else
					x"af" when(input=x"1b") else
					x"9c" when(input=x"1c") else
					x"a4" when(input=x"1d") else
					x"72" when(input=x"1e") else
					x"c0" when(input=x"1f") else
					x"b7" when(input=x"20") else
					x"fd" when(input=x"21") else
					x"93" when(input=x"22") else
					x"26" when(input=x"23") else
					x"36" when(input=x"24") else
					x"3f" when(input=x"25") else
					x"f7" when(input=x"26") else
					x"cc" when(input=x"27") else
					x"34" when(input=x"28") else
					x"a5" when(input=x"29") else
					x"e5" when(input=x"2a") else
					x"f1" when(input=x"2b") else
					x"71" when(input=x"2c") else
					x"d8" when(input=x"2d") else
					x"31" when(input=x"2e") else
					x"15" when(input=x"2f") else
					x"04" when(input=x"30") else
					x"c7" when(input=x"31") else
					x"23" when(input=x"32") else
					x"c3" when(input=x"33") else
					x"18" when(input=x"34") else
					x"96" when(input=x"35") else
					x"05" when(input=x"36") else
					x"9a" when(input=x"37") else
					x"07" when(input=x"38") else
					x"12" when(input=x"39") else
					x"80" when(input=x"3a") else
					x"e2" when(input=x"3b") else
					x"eb" when(input=x"3c") else
					x"27" when(input=x"3d") else
					x"b2" when(input=x"3e") else
					x"75" when(input=x"3f") else
					x"09" when(input=x"40") else
					x"83" when(input=x"41") else
					x"2c" when(input=x"42") else
					x"1a" when(input=x"43") else
					x"1b" when(input=x"44") else
					x"6e" when(input=x"45") else
					x"5a" when(input=x"46") else
					x"a0" when(input=x"47") else
					x"52" when(input=x"48") else
					x"3b" when(input=x"49") else
					x"d6" when(input=x"4a") else
					x"b3" when(input=x"4b") else
					x"29" when(input=x"4c") else
					x"e3" when(input=x"4d") else
					x"2f" when(input=x"4e") else
					x"84" when(input=x"4f") else
					x"53" when(input=x"50") else
					x"d1" when(input=x"51") else
					x"00" when(input=x"52") else
					x"ed" when(input=x"53") else
					x"20" when(input=x"54") else
					x"fc" when(input=x"55") else
					x"b1" when(input=x"56") else
					x"5b" when(input=x"57") else
					x"6a" when(input=x"58") else
					x"cb" when(input=x"59") else
					x"be" when(input=x"5a") else
					x"39" when(input=x"5b") else
					x"4a" when(input=x"5c") else
					x"4c" when(input=x"5d") else
					x"58" when(input=x"5e") else
					x"cf" when(input=x"5f") else
					x"d0" when(input=x"60") else
					x"ef" when(input=x"61") else
					x"aa" when(input=x"62") else
					x"fb" when(input=x"63") else
					x"43" when(input=x"64") else
					x"4d" when(input=x"65") else
					x"33" when(input=x"66") else
					x"85" when(input=x"67") else
					x"45" when(input=x"68") else
					x"f9" when(input=x"69") else
					x"02" when(input=x"6a") else
					x"7f" when(input=x"6b") else
					x"50" when(input=x"6c") else
					x"3c" when(input=x"6d") else
					x"9f" when(input=x"6e") else
					x"a8" when(input=x"6f") else
					x"51" when(input=x"70") else
					x"a3" when(input=x"71") else
					x"40" when(input=x"72") else
					x"8f" when(input=x"73") else
					x"92" when(input=x"74") else
					x"9d" when(input=x"75") else
					x"38" when(input=x"76") else
					x"f5" when(input=x"77") else
					x"bc" when(input=x"78") else
					x"b6" when(input=x"79") else
					x"da" when(input=x"7a") else
					x"21" when(input=x"7b") else
					x"10" when(input=x"7c") else
					x"ff" when(input=x"7d") else
					x"f3" when(input=x"7e") else
					x"d2" when(input=x"7f") else
					x"cd" when(input=x"80") else
					x"0c" when(input=x"81") else
					x"13" when(input=x"82") else
					x"ec" when(input=x"83") else
					x"5f" when(input=x"84") else
					x"97" when(input=x"85") else
					x"44" when(input=x"86") else
					x"17" when(input=x"87") else
					x"c4" when(input=x"88") else
					x"a7" when(input=x"89") else
					x"7e" when(input=x"8a") else
					x"3d" when(input=x"8b") else
					x"64" when(input=x"8c") else
					x"5d" when(input=x"8d") else
					x"19" when(input=x"8e") else
					x"73" when(input=x"8f") else
					x"60" when(input=x"90") else
					x"81" when(input=x"91") else
					x"4f" when(input=x"92") else
					x"dc" when(input=x"93") else
					x"22" when(input=x"94") else
					x"2a" when(input=x"95") else
					x"90" when(input=x"96") else
					x"88" when(input=x"97") else
					x"46" when(input=x"98") else
					x"ee" when(input=x"99") else
					x"b8" when(input=x"9a") else
					x"14" when(input=x"9b") else
					x"de" when(input=x"9c") else
					x"5e" when(input=x"9d") else
					x"0b" when(input=x"9e") else
					x"db" when(input=x"9f") else
					x"e0" when(input=x"a0") else
					x"32" when(input=x"a1") else
					x"3a" when(input=x"a2") else
					x"0a" when(input=x"a3") else
					x"49" when(input=x"a4") else
					x"06" when(input=x"a5") else
					x"24" when(input=x"a6") else
					x"5c" when(input=x"a7") else
					x"c2" when(input=x"a8") else
					x"d3" when(input=x"a9") else
					x"ac" when(input=x"aa") else
					x"62" when(input=x"ab") else
					x"91" when(input=x"ac") else
					x"95" when(input=x"ad") else
					x"e4" when(input=x"ae") else
					x"79" when(input=x"af") else
					x"e7" when(input=x"b0") else
					x"c8" when(input=x"b1") else
					x"37" when(input=x"b2") else
					x"6d" when(input=x"b3") else
					x"8d" when(input=x"b4") else
					x"d5" when(input=x"b5") else
					x"4e" when(input=x"b6") else
					x"a9" when(input=x"b7") else
					x"6c" when(input=x"b8") else
					x"56" when(input=x"b9") else
					x"f4" when(input=x"ba") else
					x"ea" when(input=x"bb") else
					x"65" when(input=x"bc") else
					x"7a" when(input=x"bd") else
					x"ae" when(input=x"be") else
					x"08" when(input=x"bf") else
					x"ba" when(input=x"c0") else
					x"78" when(input=x"c1") else
					x"25" when(input=x"c2") else
					x"2e" when(input=x"c3") else
					x"1c" when(input=x"c4") else
					x"a6" when(input=x"c5") else
					x"b4" when(input=x"c6") else
					x"c6" when(input=x"c7") else
					x"e8" when(input=x"c8") else
					x"dd" when(input=x"c9") else
					x"74" when(input=x"ca") else
					x"1f" when(input=x"cb") else
					x"4b" when(input=x"cc") else
					x"bd" when(input=x"cd") else
					x"8b" when(input=x"ce") else
					x"8a" when(input=x"cf") else
					x"70" when(input=x"d0") else
					x"3e" when(input=x"d1") else
					x"b5" when(input=x"d2") else
					x"66" when(input=x"d3") else
					x"48" when(input=x"d4") else
					x"03" when(input=x"d5") else
					x"f6" when(input=x"d6") else
					x"0e" when(input=x"d7") else
					x"61" when(input=x"d8") else
					x"35" when(input=x"d9") else
					x"57" when(input=x"da") else
					x"b9" when(input=x"db") else
					x"86" when(input=x"dc") else
					x"c1" when(input=x"dd") else
					x"1d" when(input=x"de") else
					x"9e" when(input=x"df") else
					x"e1" when(input=x"e0") else
					x"f8" when(input=x"e1") else
					x"98" when(input=x"e2") else
					x"11" when(input=x"e3") else
					x"69" when(input=x"e4") else
					x"d9" when(input=x"e5") else
					x"8e" when(input=x"e6") else
					x"94" when(input=x"e7") else
					x"9b" when(input=x"e8") else
					x"1e" when(input=x"e9") else
					x"87" when(input=x"ea") else
					x"e9" when(input=x"eb") else
					x"ce" when(input=x"ec") else
					x"55" when(input=x"ed") else
					x"28" when(input=x"ee") else
					x"df" when(input=x"ef") else
					x"8c" when(input=x"f0") else
					x"a1" when(input=x"f1") else
					x"89" when(input=x"f2") else
					x"0d" when(input=x"f3") else
					x"bf" when(input=x"f4") else
					x"e6" when(input=x"f5") else
					x"42" when(input=x"f6") else
					x"68" when(input=x"f7") else
					x"41" when(input=x"f8") else
					x"99" when(input=x"f9") else
					x"2d" when(input=x"fa") else
					x"0f" when(input=x"fb") else
					x"b0" when(input=x"fc") else
					x"54" when(input=x"fd") else
					x"bb" when(input=x"fe") else
					x"16" when(input=x"ff");
	
end sbox_arch;

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

std::string resloc = "try.txt";
// The packet in it's initial hex format
std::string hex_pkt;
// The packet converted to binary
std::string bin_pkt;

int version, type_id;


void get_input()
{
	std::ifstream resfile(resloc);
	getline(resfile, hex_pkt);
	// Well, that was easy
}

std::string hextobin(std::string hex)
{
	std::string bin;
	std::unordered_map<char, std::string> conv_table =
	{
		{'0', "0000"},
		{'1', "0001"},
		{'2', "0010"},
		{'3', "0011"},
		{'4', "0100"},
		{'5', "0101"},
		{'6', "0110"},
		{'7', "0111"},
		{'8', "1000"},
		{'9', "1001"},
		{'A', "1010"},
		{'B', "1011"},
		{'C', "1100"},
		{'D', "1101"},
		{'E', "1110"},
		{'F', "1111"}
	};
	// I bet there's a really smart solution for this, but I don't really care
	for (int i = 0; i<hex.size(); i++)
	{
		bin += conv_table[hex[i]];
	}
	return bin;
}

void set_meta(std::string bin)
{
	std::string str_vers;
	for (int i = 0; i<3; i++)
		str_vers += bin[i];
	version = std::stoi(str_vers, nullptr, 2);
	std::string str_id;
	for (int i = 2; i<6; i++)
		str_id += bin[i];
	type_id = std::stoi(str_id, nullptr, 2);
}

int get_lit_val(std::string bin)
{
	std::string str_value;
	int leader_bit_pos = 6;
	char leader_bit;
	int header_pos = 6;
	do
	{
		leader_bit = bin[leader_bit_pos];
		for (++header_pos; header_pos < leader_bit_pos+5; header_pos++)
		{
			std::cout << bin[header_pos];
			str_value += bin[header_pos];
		}
		std::cout << " ";
		leader_bit_pos += 5;
	} 
	while(leader_bit == '1');
	std::cout << std::endl;
	return std::stoi(str_value, nullptr, 2);
}

int main()
{
	get_input();
	std::cout << "Message in hex format: " << hex_pkt << std::endl;
	 
	bin_pkt = hextobin(hex_pkt);
	std::cout << "Message converted to binary: " << bin_pkt << std::endl;
	 
	set_meta(bin_pkt);
	std::cout << "Version: " << version << "; Type ID: " << type_id << std::endl;

	if (type_id == 4)
	{
		// The package is a literal value
		std::cout << "Decoding literal value: " << std::endl;
		int lit_val = get_lit_val(bin_pkt);
		std::cout << lit_val << std::endl;
	}
}

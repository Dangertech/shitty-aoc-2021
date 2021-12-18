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

int parttoi(std::string& str, int from, int to)
{
	std::string str_part;
	for (int i = from; i < to; i++)
	{
		str_part += str[i];
	}
	return std::stoi(str_part, nullptr, 2);
}

std::string part(std::string& str, int from, int to)
{
	std::string str_part;
	for (int i = from; i<to; i++)
	{
		if (i<str.size()-1)
			str_part+=str[i];
	}
	return str_part;
}

struct pkg_meta
{
	int version;
	int leader_bit;
};

struct lit_data
{
	int val;
	int total_bits;
};

std::pair <pkg_meta, lit_data> get_lit_val(std::string bin)
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
			str_value += bin[header_pos];
		}
		leader_bit_pos += 5;
	} 
	while(leader_bit == '1');
	pkg_meta metadata = {std::stoi(part(bin, 0, 2), nullptr, 2), std::stoi(part(bin, 3, 5), nullptr, 2)};
	lit_data data = {std::stoi(str_value, nullptr, 2), leader_bit_pos};
	return std::make_pair(metadata, data);
}

int main()
{
	get_input();
	std::cout << "Message in hex format: " << hex_pkt << std::endl;
	 
	bin_pkt = hextobin(hex_pkt);
	std::cout << "Message converted to binary: " << bin_pkt << std::endl;
	 
	version = parttoi(bin_pkt, 0, 3);
	type_id = parttoi(bin_pkt, 3, 6);
	std::cout << "Version: " << version << "; Type ID: " << type_id << std::endl;

	// TODO: Now all this just has to be adapted for infinite recursion
	// It's something something move header_pos I think
	if (type_id == 4)
	{
		// The package is a literal value
		std::cout << "Decoding literal value:" << std::endl;
		int lit_val = get_lit_val(bin_pkt).second.val;
		std::cout << lit_val << std::endl;
	}
	else
	{
		std::cout << "Decoding operator packet:" << std::endl;
		// Check for the length type ID
		if (bin_pkt[6] == '0')
		{
			std::cout << "Getting total bits: ";
			int sub_total = parttoi(bin_pkt, 7, 22);
			std::cout << sub_total << std::endl;;
			int header_pos = 22;
			for (header_pos; header_pos<22+sub_total; header_pos++)
			{
				auto out = get_lit_val(part(bin_pkt, header_pos, 22+sub_total));
				std::cout << out.second.val << " ";
				header_pos+=out.second.total_bits-1;
			}
			std::cout << std::endl;
		}
		else
		{
			std::cout << "Getting sub-packet count: ";
			int sub_total = parttoi(bin_pkt, 7, 18);
			std::cout << sub_total << std::endl;
			int header_pos = 18;
			for (int i = 0; i<sub_total; i++)
			{
				//std::cout << get_lit_val(part(bin_pkt, header_pos, header_pos+11)).first << " ";
				std::cout << "Giving " << part(bin_pkt, header_pos, bin_pkt.size()) << " ";
				auto out = get_lit_val(part(bin_pkt, header_pos, bin_pkt.size()-1));
				std::cout << out.second.val << std::endl;
				header_pos+=out.second.total_bits;
			}
			std::cout << std::endl;
		}
	}
}

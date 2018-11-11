//Boyer-Moore string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ALPHABET_LEN 256
#define max(a, b) ((a < b) ? b : a)

using namespace std;

string print_buffer(std::vector<char>& b);
char uppercase(char c);

int main(int argc, char* argv[])
{
	if(argc != 3)
	{
		std::cout << "Usage ./Boyer_Moore <file.txt> <pattern>" <<std::endl;
		return -1;
	}
	std::string line;
	std::vector<char> buffer;
	std::ifstream f(argv[1]);
	std::string pat = argv[2];
	if(f.is_open())
	{
		while(getline (f,line))
		{
			for(int i=0;i<line.length();i++)
			{	
				char c = line[i];
				c = uppercase(c);
				buffer.push_back(c);
			}
		}
		f.close();

		std::string l = print_buffer(buffer);
	}
	else std::cout << "Unable to open file" << std::endl;
	return 0;
}

std::string print_buffer(std::vector<char>& b)
{
	std::string r;
	for(int i=0;i<b.size();i++)
	{
		r += b.at(i);
	}
	return r;
}

char uppercase(char c)
{
	int k = static_cast<int>(c);
        if(k >= 97 && k <= 122) 
	{
		c = static_cast<char>(k-32);
	}
	return c;
}

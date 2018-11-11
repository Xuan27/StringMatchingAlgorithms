//Boyer-Moore string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#define ALPHABET_LEN 256

void print_buffer(std::vector<char>& b);
char uppercase(char c);

int main(int argc, char* argv[])
{
	std::string line;
	std::vector<char> buffer;
	std::ifstream f(argv[1]);
	if(f.is_open())
	{
		while(getline (f,line))
		{
			std::cout << line << std::endl;
			
			for(int i=0;i<line.length();i++)
			{	
				char c = line[i];
				c = uppercase(c);
				buffer.push_back(c);
			}
		}
		f.close();

		print_buffer(buffer);
	}
	else std::cout << "Unable to open file" << std::endl;
	return 0;
}

void print_buffer(std::vector<char>& b)
{
	for(int i=0;i<b.size();i++)
	{
		std::cout << b.at(i);
	}
	std::cout<<std::endl;
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

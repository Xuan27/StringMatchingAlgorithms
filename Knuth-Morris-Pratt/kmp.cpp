// string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

std::vector<uint> function_failure(std::string pattern);
uint KMP(std::string text, std::string pattern);

int comparisons = 0;

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
        std::string pat_upper;
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

                for(int i=0;i<pat.length();i++)
                {
                        char c = pat[i];
                        c = uppercase(c);
                        pat_upper.push_back(c);
                }

                std::string text = print_buffer(buffer);
	}
	return 0;
}	

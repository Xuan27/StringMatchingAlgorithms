//KMP string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

void function_failure(std::string& pattern, std::vector<int>& function_results);
int KMP(std::string& text, std::string& pattern);
std::string print_buffer(std::vector<char>& b);
char uppercase(char c);

int comparisons = 0;

int main(int argc, char* argv[])
{
        if(argc != 3)
        {
                std::cout << "Usage ./KMP <file.txt> <pattern>" <<std::endl;
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
                        for(unsigned int i=0;i<line.length();i++)
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

		std::string str = "ABABDABACDABABCABAB";
		std::string pat = "ABABCABAB";

		std::cout<<std::endl<<KMP(str,pat);
	}
	return 0;
}

void function_failure(std::string& pattern, )
{
	int length = pattern.length();
	std::vector<int> function_results;
	//function_results.resize(length);
	//function_results[0] = 0;
	function_results.push_back(0);
	int l = 0;
	int i = 0;

	while (i < length)
	{
		if(pattern[i] == pattern[l])
		{
			++l;
			function_results[i] = l;
			++i;
		}
		else
		{
			if(l!=0)
			{
				l = function_results[l-1];
			}
			else
			{
				function_results[i] = 0;
				++i;
			}
		}
	}

	return function_results;
}

int KMP(std::string& text, std::string& pattern)
{
	int patl = pattern.length();
	int textl = text.length();

	vector<int> function_results = function_failure(pattern);

	int i = 0;
	int j = 0;

	while(i < textl)
	{
		if(text[i] == pattern[j])
		{
			++i;
			++j;
		}
		else
		{
			if(j != 0)
			{
				j = function_results[j-1];
			}
			else
			{
				i += 1;
			}
		}

		if(j == patl)
		{
			return i -j;
		}
	}
	return -1;

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

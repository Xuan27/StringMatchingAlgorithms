//KMP string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

using namespace std;

//Declaring functions
void function_failure(std::string& pattern, std::vector<int>& function_results);
int KMP(std::string& text, std::string& pattern);
std::string print_buffer(std::vector<char>& b);
char uppercase(char c);

//Declaring global variables
int comparisons = 0;
int last_index_compared = 0;

//Main function
int main(int argc, char* argv[])
{
	//Displays the correct usage if the numbers of arguments are not satisfied
        if(argc != 3)
        {
                std::cout << "Usage ./KMP <file.txt> <pattern>" <<std::endl;
                return -1;
        }

	//Creating the containers to hold the text from the file
        std::string line;
        std::vector<char> buffer;
        std::ifstream f(argv[1]);
        std::string pat = argv[2];
        std::string pat_upper;
        if(f.is_open())
        {
		//The document is read line by line meanwhile is stored into the memory at runtime
                while(getline (f,line))
                {
                        for(unsigned int i=0;i<line.length();i++)
                        {
                                char c = line[i];
                                c = uppercase(c);	//The character is converted to uppercase
                                buffer.push_back(c);	//The converted character is introduced into the container
			}
                }
                f.close();

		//The pattern is also converted to uppercase
                for(int i=0;i<pat.length();i++)
                {
                        char c = pat[i];
                        c = uppercase(c);
                        pat_upper.push_back(c);
                }


		//The vector of chars is converted to a string
                std::string text = print_buffer(buffer);

		//The index of the match is retrieved from the algorithm
		std::cout<<std::endl<<"Index: "<<KMP(text,pat_upper)<<std::endl;

		
		//The results are displayed 
		std::cout<<"Comparisons: "<<comparisons<<std::endl;

		std::cout<<"Last index compared: "<< last_index_compared << std::endl;

		float result = (float)comparisons/(float)last_index_compared;

		std::cout<<"Result: "<<result<<std::endl;
	}
	return 0;
}

//Function to calculate the failure table
void function_failure(std::string& pattern, std::vector<int>& function_results )
{
	int length = pattern.length();		//Get the length of the pattern
	function_results[0] = 0;		//Function_results[0] will be always 0
	int l = 0;				//Lenght of previous longest prefix suffix
	int i = 1;				//Auxiliary variable

	while (i < length)			//Execute until the end  of the pattern is reached
	{
		//Calculates the integers for i = 1 to M-1 
		if(pattern[i] == pattern[l])	//Checks if the prefix is equal to suffix
		{
			++l;
			function_results[i] = l;
			++i;
		}
		else
		{
			if(l != 0)  //If different of zero acommodate it into the lenght of the pattern
			{
				l = function_results[l-1];
			}
			else	//No prefix / suffix match found
			{
				function_results[i] = 0;
				++i;
			}
		}
	}

}

//Function that contains the KMP algorithm
int KMP(std::string& text, std::string& pattern)
{
	int patl = pattern.length();	//Store the length of the pattern
	int textl = text.length();	//Store the lenght of the text to be processed

	vector<int> function_results(patl);	//Empty failure table
	function_failure(pattern,function_results);	//Calculates the failure table

	int i = 0;			//Auxiliary variables
	int j = 0;

	while(i < textl)		//Continue until the end of the string
	{
		if(text[i] == pattern[j])	//Perfom similar behaviour as the naive algoithm
		{
			++i;
			++j;
			comparisons++;		//A comparison is made every time
		}
		else
		{
			if(j != 0)     //The failure table is asked to know the corresponding shift
			{
				j = function_results[j-1];
			}
			else
			{
				i += 1;
			}
			comparisons++;		//A comparison has been made
		}

		if(j == patl)		//If the end of the pattern is reached return the index
		{
			last_index_compared = i-1;
			return i -j;
		}
	}
	last_index_compared = i-1;
	return -1;			//Return -1 if the pattern was not found

}

//Convert all the characters stored in the vector to the string
std::string print_buffer(std::vector<char>& b)
{
        std::string r;
        for(int i=0;i<b.size();i++)
        {
                r += b.at(i);
        }
        return r;
}

//Converts the lowercase characters to uppercase characters
char uppercase(char c)
{
        int k = static_cast<int>(c);
        if(k >= 97 && k <= 122)
        {
                c = static_cast<char>(k-32);
        }
        return c;
}

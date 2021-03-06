#include "stdafx.h"
#include <iostream>
#include <istream>
#include <string>
#include <locale>
#include <vector>
#include <fstream>
#include <cstring>
using namespace std;

class Rabin_Karp {
private:
	int HashP;
	int M;//Lenght of the pattern
	int Q;//Modulus
	int R;//Radix
	int RM1;
	//Calculates the hash value for the text and pattern characters
	int hashPattern(string pattern, int m) {
		int h = 0;
		int ascii = 0;
		for (int j = 0; j < m; j++) {
			//Character to integer value
			int ascii = (int)pattern[j];
			//Hash value
			h = (h * R + ascii) % Q;
		}
		return h;
	};
public:
	//Constructor of the class with the pattern as arguments
	Rabin_Karp(string pattern) {
		M = pattern.length();
		//Radix
		R = 256;
		//Modulus large prime number
		Q = 20011;
		RM1 = 1;
		for (int i = 1; i <= M - 1; i++) {
			RM1 = (R*RM1) % Q;
		}
		//Pattern hash
		HashP = hashPattern(pattern, M);
	};
	
	//Search the text file to match the pattern using rolling hash
	int search(string txt) {
		int N = txt.length();
		int comparisons = 1;
		//Text hash
		int txtHash = hashPattern(txt, M);
		//Initial text characters match the pattern
		if (HashP == txtHash)
			return 0;
		for (int i = M; i < N; i++) {
			//Rolling hash
			txtHash = (txtHash + Q - RM1 * ((int)txt[i - M]) % Q) % Q;
			txtHash = (txtHash*R + ((int)txt[i])) % Q;
			//Number of comparisons calculated
			comparisons++;
			if (HashP == txtHash) {
				double value = (double)comparisons / (double)i;
				cout << "Comparisons: " << comparisons << endl;
				cout << "Last Index: " << i << endl;
				cout << "Value: " << value << endl;
				return i - M + 1;
			}
		}
		return N;
	}
	//Sets the characters to uppercase characters
	char uppercase(char c) {
		int k = static_cast<int>(c);
		if (k >= 97 && k <= 122)
		{
			c = static_cast<char>(k - 32);
		}
		return c;
	}
};

int main()
{
	string patternStr = "";
	string text;
	string pattern = "y";

	while (pattern == "y") {
		
		string str;
		cout << "Key: ";
		cin >> patternStr;

		//Size of pattern
		int m = patternStr.length();

		//Pattern all characters to uppercase
		locale loc;
		for (int up = 0; up < m; up++) {
			str += toupper(patternStr[up], loc);
		}
		patternStr = str;

		//Rabin-Karp object
		Rabin_Karp* RK = new Rabin_Karp(patternStr);
		int match;
		std::string line;
		string strLine;
		ifstream f("../The Gettysburg Address.txt");
		if (f.is_open())
		{
			//Read and transforms to uppercase the text document
			while (getline(f, line))
			{
				for (int i = 0;i<line.length();i++)
				{
					char c = line[i];
					c = RK->uppercase(c);
					strLine += c;
				}
			}
			f.close();
			//Search the text file with the initilized pattern hash in the class
			match = RK->search(strLine);
			cout << "Match: " << match << endl << endl;

			//Prints the text after matched index
			/*for (int p = match;p < strLine.length();p++) {
				cout << strLine[p];
			}
			cout << endl;*/

			cout << "New pattern (y||n): ";
			cin >> pattern;
			//if pattern input is wrong
			while (pattern != "y" && pattern != "n") {
				cout << "New pattern (y||n): ";
				cin >> pattern;
			}

		}
		else std::cout << "Unable to open file" << std::endl;	}
    return 0;
}
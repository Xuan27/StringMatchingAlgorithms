// Rabin_Karp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <string>
#include <locale>
#include <vector>
#include <fstream>
using namespace std;

class Rabin_Karp {
private:
	int HashP;
	int M;
	int Q;
	int R;
	int RM1;
	int hashPattern(string pattern, int m) {
		int h = 0;
		for (int j = 0; j < m; j++) {
			int ascii = (int)pattern[j];
			int key = ascii - 64;
			h = (h * R + ((int)pattern[j] - 64)) % Q;
		}
		return h;
	};
public:
	Rabin_Karp(string pattern) {
		M = pattern.length();
		R = 256;
		Q = 104729;
		RM1 = 1;
		for (int i = 1; i <= M - 1; i++) {
			RM1 = (R*RM1) % Q;
		}
		HashP = hashPattern(pattern, M);
	};
	
	int search(string txt) {
		int N = txt.length();
		int comparisons = 1;
		int txtHash = hashPattern(txt, M);
		if (HashP == txtHash)
			return 0;
		for (int i = M; i < N; i++) {
			txtHash = ((txtHash + ((int)txt[i - M]-64) * (Q - RM1))*R + ((int)txt[i])-64) % Q;
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

		//Rabin-Karp Algorithm
		Rabin_Karp* RK = new Rabin_Karp(patternStr);
		int match;
		std::string line;
		string strLine;
		ifstream f("../Gettysburg_Address1.txt");
		if (f.is_open())
		{
			while (f >> line)
			{
				for (int i = 0;i<line.length();i++)
				{
					strLine += toupper(line[i], loc);
				}
				//strLine += " ";
				line = strLine;
			}
			f.close();
			match = RK->search(line);
			cout << "Match: " << match << endl << endl;
			cout << "New pattern (y||n): ";
			cin >> pattern;
			while (pattern != "y" && pattern != "n") {
				cout << "New pattern (y||n): ";
				cin >> pattern;
			}

		}
		else std::cout << "Unable to open file" << std::endl;
		//RK.search(text);
	}
    return 0;
}
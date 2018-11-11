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
			cout << key << " ";
			h = (h * 26 + ((int)pattern[j] - 64)) % Q;
		}
		return h;
	};
public:
	Rabin_Karp(string pattern) {
		M = pattern.length();
		R = 256;
		srand(time(0));
		Q = rand();
		RM1 = 1;
		for (int i = 1; i <= M - 1; i++) {
			RM1 = (R*RM1) % Q;
		}
		HashP = hashPattern(pattern, M);
	};
	
	int search(string txt) {
		int N = txt.length();
		int txtHash = hashPattern(txt, M);
		if (HashP == txtHash)
			return 0;
		for (int i = M; i < N; i++) {
			txtHash = (txtHash + Q - RM1 * (int)txt[i - M] % Q) % Q;
			txtHash = (txtHash*R + (int)txt[i]) % Q;
			if (HashP == txtHash)
				return i - M + 1;
		}
		return N;
	}
};

int main()
{
	string patternStr;
	string str;
	string text;

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
	Rabin_Karp RK(patternStr);
	int match;
	std::string line;
	string strLine;
	//vector<char> buffer;
	ifstream f("../Gettysburg_Address.txt");
	if(f.is_open())
	{
		while (f >> line)
		{
			for (int i = 0;i<line.length();i++)
			{
				strLine += toupper(line[i], loc);
			}
			line = strLine;
		}
		f.close();
		match = RK.search(line);
		cout << "Match: " << match;
		//print_buffer(buffer);
	}
	else std::cout << "Unable to open file" << std::endl;
	//RK.search(text);

    return 0;
}
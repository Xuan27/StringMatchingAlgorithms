// Rabin_Karp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <istream>
#include <string>
#include <locale>
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
			h = (h * 26 + ((int)pattern[j] - 64)) % 227;
		}
		return h;
	};
public:
	Rabin_Karp(string pattern) {
		M = pattern.length();
		R = 256;
		Q = rand();
		for (int i = 1; i <= M - 11; i++) {
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
			txtHash = (txtHash + Q - R * (int)txt[i - M] % Q) % Q;
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

	RK.search(text);

    return 0;
}



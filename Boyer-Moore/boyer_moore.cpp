//Boyer-Moore string-search algorithm
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstring>

#define ALPHABET_LEN 256
#define NOT_FOUND patlen

using namespace std;

string print_buffer(std::vector<char>& b);
char uppercase(char c);
static int max(int a, int b);
int is_prefix(uint8_t *word, int wordlen, int pos);
int suffix_length(uint8_t *word, int wordlen, int pos);
void make_delta1(int *delta1, uint8_t *pat, int32_t patlen);
void make_delta2(int *delta2, uint8_t *pat, int32_t patlen);
uint8_t* boyer_moore (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen);

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

		const char *l = text.c_str();
		const char *p = pat_upper.c_str();
		uint8_t *u = (uint8_t*) l;
		uint8_t *w = (uint8_t*) p;
		uint8_t *o = boyer_moore(u,strlen(l),w,strlen(p));
		
		if(o == NULL)
		{	
			std::cout<<"Pattern not found"<<std::endl;
			std::cout<<"Comparisons: "<<comparisons<<std::endl;
			return 0;
		}
		uint result = o - u;
		std::cout<<"Match at index: "<<result<<std::endl;
		std::cout<<"Comparisons: "<<comparisons<<std::endl;
		float ans = (float)comparisons / (float)result;
		std::cout<<"Result: "<<ans<<std::endl;
		/*
		for(int i = result; i < text.length(); i++)
			std::cout<<buffer[i];*/
		std::cout<<std::endl;


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

static int max(int a, int b)
{
	return ((a < b) ? b : a);
}

int is_prefix(uint8_t *word, int wordlen, int pos) {
    int i;
    int suffixlen = wordlen - pos;
    for (i = 0; i < suffixlen; i++) {
        if (word[i] != word[pos+i]) {
            return 0;
        }
    }
    return 1;
}

int suffix_length(uint8_t *word, int wordlen, int pos) {
    int i;
    for (i = 0; (word[pos-i] == word[wordlen-1-i]) && (i < pos); i++);
    return i;
}

void make_delta1(int *delta1, uint8_t *pat, int32_t patlen) {
    int i;
    for (i=0; i < ALPHABET_LEN; i++) {
        delta1[i] = NOT_FOUND;
    }
    for (i=0; i < patlen-1; i++) {
        delta1[pat[i]] = patlen-1 - i;
    }
}

void make_delta2(int *delta2, uint8_t *pat, int32_t patlen) {
    int p;
    int last_prefix_index = patlen-1;

    // first loop
    for (p=patlen-1; p>=0; p--) {
        if (is_prefix(pat, patlen, p+1)) {
            last_prefix_index = p+1;
        }
        delta2[p] = last_prefix_index + (patlen-1 - p);
    }

    // second loop
    for (p=0; p < patlen-1; p++) {
        int slen = suffix_length(pat, patlen, p);
        if (pat[p - slen] != pat[patlen-1 - slen]) {
            delta2[patlen-1 - slen] = patlen-1 - p + slen;
        }
    }
}

uint8_t* boyer_moore (uint8_t *string, uint32_t stringlen, uint8_t *pat, uint32_t patlen) {
    int i;
    int delta1[ALPHABET_LEN];
    int *delta2 = (int *)malloc(patlen * sizeof(int));
    make_delta1(delta1, pat, patlen);
    make_delta2(delta2, pat, patlen);

    // The empty pattern must be considered specially
    if (patlen == 0) {
        free(delta2);
        return string;
    }

    i = patlen-1;
    while (i < stringlen) {
        int j = patlen-1;
        while (j >= 0 && (string[i] == pat[j])) 
	{
	    comparisons++;
            --i;
            --j;
        }
        if (j < 0) {
            free(delta2);
            return (string + i+1);
        }
	comparisons++;

        i += max(delta1[string[i]], delta2[j]);
    }
    free(delta2);
    return NULL;
}

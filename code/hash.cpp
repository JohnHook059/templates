#include <cstdio>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

const long long P = 257, MOD = 1e9 + 9; // P = 263, MOD = 1e9 + 7;
const char min_symbol = 0;

vector <long long> h, p;

void build_hash_arr(string s) { // s - не пустая
	int len = s.length() + 1;
	h.resize(len);
	p.resize(len);
	p[0] = 1;
	h[0] = 0;
	for (int i = 1; i < len; i++) {
		p[i] = (p[i] * P) % MOD;
		h[i] = (h[i - 1] * P + s[i - 1] - min_symbol + 1) % MOD;
	}
}

long long hash_sub_str(int l, int r) { // нумерация символов с нуля; полуинтервал; 0 <= l,r <= s.length() 
	return ((h[r] - h[l] * p[r - l]) % MOD + MOD) % MOD;
}
#include <cstdio>
#include <iostream>
#include <string>
#include <algorithm>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <memory.h>

#include <vector>
#include <queue>

#define file_name "f"

using namespace std;

int n, m, arr[100000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	freopen(file_name".in", "r", stdin);
	freopen(file_name".out", "w", stdout);
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	cin >> n;
	for (int i = 0; i < n; i++) {
		cin >> arr[i];
	}
}

// Authors = Vito
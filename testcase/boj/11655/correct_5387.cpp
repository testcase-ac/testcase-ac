#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>
#include <cctype>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	string str;
	getline(cin, str);
	rep(i, sz(str)) {
		if(!isalpha(str[i])) {
			continue;
		}
		char addi = (islower(str[i]) ? 'a' : 'A');
		str[i] = ((str[i] - addi + 13) % 26) + addi;
	}
	cout << str;
}

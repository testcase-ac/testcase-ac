#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

inline int d2i(char c) {return c-'0';}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string str;
	cin >> str;
	if(str == "0") return !(cout << 0);
	int l = sz(str);
	int i=0, out=0;
	for(;i<l%3;i++) {
		out *= 2;
		out += d2i(str[i]);
	}
	if(out) cout << out;
	for(;i<l;i+=3) {
		cout << d2i(str[i])*4+d2i(str[i+1])*2+d2i(str[i+2]);
	}
}

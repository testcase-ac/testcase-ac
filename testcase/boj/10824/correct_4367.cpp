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
inline ll stoll(string &s) {
	return stoi(s);
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string a, b, c, d;
	cin >> a >> b >> c >> d;
	ll ai = stoi(a), ci = stoi(c);
	rep(i, sz(b)) ai *= 10;
	rep(i, sz(d)) ci *= 10;
	cout << (ai+stoll(b)+ci+stoll(d));
}

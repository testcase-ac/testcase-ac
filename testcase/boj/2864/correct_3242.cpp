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

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string a, b;
	cin >> a >> b;
	rep(i, sz(a)) {
		if(a[i] == '6') a[i] = '5';
	}
	rep(i, sz(b)) {
		if(b[i] == '6') b[i] = '5';
	}
	cout << (stoi(a) + stoi(b)) << ' ';
	rep(i, sz(a)) {
		if(a[i] == '5') a[i] = '6';
	}
	rep(i, sz(b)) {
		if(b[i] == '5') b[i] = '6';
	}
	cout << (stoi(a) + stoi(b));
}

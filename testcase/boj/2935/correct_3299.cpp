#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <stack>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s1, s2;
	char op;
	cin >> s1 >> op >> s2;
	if(op == '*') {
		cout << '1';
		rep(i, sz(s1)+sz(s2)-2)
			cout << '0';
	} else {
		if(sz(s1) == sz(s2)) {
			cout << '2';
			rep(i, sz(s1)-1)
				cout << '0';
		} else {
			cout << '1';
			rep(i, abs(sz(s1)-sz(s2))-1)
				cout << '0';
			cout << '1';
			rep(i, min(sz(s1), sz(s2))-1)
				cout << '0';
		}
	}
}

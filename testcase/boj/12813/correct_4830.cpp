#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <algorithm>
#include <functional>
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
#define def function
#define deb(v) cerr << #v << ':' << v << '\n';
#define ldb long double
using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	string s1, s2;
	cin >> s1 >> s2;
	int n = sz(s1);
	rep(i, n)
		cout << ((s1[i]=='1')&&(s2[i]=='1') ? '1' : '0');
	cout << '\n';
	rep(i, n)
		cout << ((s1[i]=='1')||(s2[i]=='1') ? '1' : '0');
	cout << '\n';
	rep(i, n)
		cout << ((s1[i]!=s2[i]) ? '1' : '0');
	cout << '\n';
	rep(i, n)
		cout << (s1[i]=='0' ? '1' : '0');
	cout << '\n';
	rep(i, n)
		cout << (s2[i]=='0' ? '1' : '0');
}

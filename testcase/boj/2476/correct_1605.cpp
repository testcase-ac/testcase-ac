#include <iostream>
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <algorithm>
#include <vector>

#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int f(int a, int b, int c) {
	if(a == b && a == c)
		return 10000 + 1000*a;
	if(a == b || a == c)
		return 1000 + 100*a;
	if(b == c)
		return 1000 + 100*b;
	return max(max(a, b),c)*100;
}

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int m = 0;
	rep(i, n) {
		int a, b, c;
		cin >> a >> b >> c;
		m = max(m, f(a,b,c));
	}
	cout << m;
}

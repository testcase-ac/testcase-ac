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

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	int p1 = 100, p2 = 100;
	while(n--) {
		int a, b;
		cin >> a >> b;
		if(a > b)
			p2 -= a;
		else if(a < b)
			p1 -= b;
	}
	cout << p1 << '\n' << p2;
}

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
#define deb(v) cout << #v << ':' << v

using namespace std;
int gcd(int a, int b) {
	return (b ? gcd(b, a%b) : a);
}
int main() {
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int n, r, q;
	cin >> n >> r;
	rep(i, n-1) {
		cin >> q;
		int g = gcd(r, q);
		printf("%d/%d\n", r/g, q/g);
	}
}

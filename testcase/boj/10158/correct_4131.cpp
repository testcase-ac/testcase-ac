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

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	ll w, h, p, q, t;
	cin >> w >> h >> p >> q >> t;
	p += t, q += t;
	p = (p % (2*w));
	q = (q % (2*h));
	if(p > w) p = 2*w - p;
	if(q > h) q = 2*h - q;
	cout << p << ' ' << q;
}

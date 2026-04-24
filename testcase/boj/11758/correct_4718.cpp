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
	//ios::sync_with_stdio(false);cin.tie(NULL);
	int x1, y1, x2, y2, x3, y3, x4, y4, x5, y5;
	cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
	x4 = x1 - x2;
	y4 = y1 - y2;
	x5 = x3 - x2;
	y5 = y3 - y2;
	int p = x4 * y5 - x5 * y4;
	if(p < 0)
		cout << 1;
	else if(p > 0)
		cout << -1;
	else
		cout << 0;
}

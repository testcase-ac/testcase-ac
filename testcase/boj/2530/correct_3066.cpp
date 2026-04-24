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
	int a, b, c, t;
	cin >> a >> b >> c >> t;
	c += t;
	b += c / 60;
	c %= 60;
	a += b / 60;
	b %= 60;
	a %= 24;
	printf("%d %d %d", a, b, c);
}

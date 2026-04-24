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
	string str;
	int base;
	cin >> str >> base;
	int ans = 0;
	rep(i, sz(str)) {
		ans *= base;
		if(isdigit(str[i]))
			ans += (str[i] - '0');
		else
			ans += (str[i] - 'A' + 10);
	}
	cout << ans;

}

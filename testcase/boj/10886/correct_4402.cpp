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
	int n;
	cin >> n;
	int onecnt = 0;
	rep(i, n) {
		int inp;
		cin >> inp;
		if(inp) onecnt++;
	}
	if(onecnt * 2 >= n) {
		cout << "Junhee is cute!";
	} else {
		cout << "Junhee is not cute!";
	}
}

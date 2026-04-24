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
struct info {
	int g,s,b;
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, k;
	cin >> n >> k;
	vector<info> arr(n);
	int g, s, b;
	rep(i, n) {
		int j;
		cin >> j;
		j--;
		cin >> arr[j].g >> arr[j].s >> arr[j].b;
		if(j+1 == k) {
			g = arr[j].g;
			s = arr[j].s;
			b = arr[j].b;
		}
	}
	int ans = 1;
	for(info a: arr) {
		if(a.g > g || (a.g==g && a.s > s) || (a.g==g && a.s==s && a.b > b)) {
			ans++;
		}
	}
	cout << ans;
}

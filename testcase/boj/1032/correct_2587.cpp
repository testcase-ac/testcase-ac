#include <iostream>
#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <vector>

#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i, n) for(int i=0; i<(n); i++)
#define set0(arr) memset(arr, 0, sizeof(arr))

using namespace std;

int main() {
	int n;
	cin >> n;
	string ans;
	cin >> ans;
	vector<string> arr(n-1);
	rep(i, n-1) cin >> arr[i];
	int len = sz(ans);
	rep(i, len) {
		rep(j, n-1) {
			if(arr[j][i] != ans[i]) {
				ans[i] = '?';
				break;
			}
		}
	}
	cout << ans;
}

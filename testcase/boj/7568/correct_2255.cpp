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
	vector<pair<int,int>> arr(n);
	rep(i,n) cin >> arr[i].first >> arr[i].second;
	for(auto pr: arr) {
		int ans = 1;
		for(auto pr2: arr) {
			if(pr2.first > pr.first && pr2.second > pr.second) ans++;
		}
		cout << ans << ' ';
	}
}

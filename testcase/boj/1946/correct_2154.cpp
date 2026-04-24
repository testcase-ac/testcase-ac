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

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		pair<int,int> arr[n];
		rep(i, n) cin >> arr[i].first >> arr[i].second;
		sort(arr, arr+n);
		int chosen = MOD, ans = 0;
		for(auto &pr: arr) {
			if(pr.second < chosen) {
				chosen = pr.second;
				ans++;
			}
		}
		cout << ans << '\n';
	}
}

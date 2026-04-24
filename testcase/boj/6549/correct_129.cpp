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
	int n;
	while(1) {
		cin >> n;
		if(n == 0) return 0;
		vector<ll> arr(n);
		rep(i, n) cin >> arr[i];
		stack<pair<ll,int>> stk;
		vector<ll> fleft(n), fright(n);
		for(int i=0; i<n; i++) {
			if(stk.empty()) {
				fleft[i] = arr[i];
				stk.emplace(arr[i], 1);
			} else {
				int w = 1;
				ll h = arr[i];
				while(!stk.empty() && stk.top().first >= h) {
					w += stk.top().second;
					stk.pop();
				}
				fleft[i] = w * h;
				stk.emplace(h, w);
			}
		}
		stk = stack<pair<ll,int>>();
		for(int i=n-1;i>=0;i--) {
			if(stk.empty()) {
				fright[i] = arr[i];
				stk.emplace(arr[i], 1);				
			} else {
				int w = 1;
				ll h = arr[i];
				while(!stk.empty() && stk.top().first >= h) {
					w += stk.top().second;
					stk.pop();
				}
				fright[i] = w * h;
				stk.emplace(h, w);
			}
		}
		ll ans = 0;
		rep(i, n) {
			//printf("when index %d is min: left=%lld, right=%lld.\n", i, fleft[i], fright[i]);
			ans = max(ans, fleft[i]+fright[i]-arr[i]);
		}
		cout << ans << '\n';
	}
}

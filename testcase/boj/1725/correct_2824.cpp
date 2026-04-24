#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define pii pair<int,int>
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n;
	cin >> n;
	stack<pair<int,int>> stk;
	int ans = 0;
	while(n--) {
		int h;
		int width = 1;
		cin >> h;
		int temph;
		while(!stk.empty() && stk.top().first >= h) {
			temph = stk.top().first;
			width += stk.top().second;
			ans = max(ans, (width-1)*temph);
			stk.pop();
		}
		stk.emplace(h, width);
	}
	int width = 0;
	int h;
	while(!stk.empty()) {
		h = stk.top().first;
		width += stk.top().second;
		ans = max(ans, width*h);
		stk.pop();
	}
	cout << ans;
}

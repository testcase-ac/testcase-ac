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
	int arr[n];
	rep(i,n) cin >> arr[i];
	int ans[n];
	rep(i,n) ans[i] = i;
	do {
		rep(i,n) {
			int cnt = 0;
			rep(j, i)
				if(ans[j] > ans[i]) cnt++;
			if(cnt != arr[ans[i]]) goto nextp;
		}
		for(int a: ans) cout << a+1 << ' ';
		return 0;
		nextp:;
	} while(next_permutation(ans, ans+n));
}

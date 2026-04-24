#include <bits/stdc++.h>
using namespace std;
#define int long long
int dp[300][1<<11], n, m;
int f(int i, int bm) {
	if(i == n*m)
		return bm ? 0 : 1;
	if(dp[i][bm] != -1)
		return dp[i][bm];
	int& r = dp[i][bm];
	if(bm&1)
		return r = f(i+1, bm>>1);
	r = f(i+1, (bm>>1)|(1<<(m-1)));
	if(!(bm&3) && i%m != m-1)
		r += f(i+1, (bm>>1)|1);
	return r;
}
signed main() {
	ios::sync_with_stdio(0);cin.tie(0);
    while(cin >> n >> m) {
        if(!n) return 0;
    	memset(dp, -1, sizeof dp);
        if(n%2 && m%2)
            cout << "0\n";
        else
            cout << f(0, 0) << '\n';
    }
}

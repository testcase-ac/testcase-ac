#include <bits/stdc++.h>
using namespace std;
#define int long long
int arr[32], mask, dp[50];
#ifdef ONLINE_JUDGE
const int HLF = 16;
#else
const int HLF = 3;
#endif
int n, a, b;
int f(int t) {
	if(dp[t % a] != -1)
		return dp[t % a];
	int lg = t >> HLF;
	int &ret = dp[t % a];
	ret = 0;
	while(t % a)
		t++;
	while((t >> HLF) == lg) {
		if((t & mask) == mask)
			ret++;
		t += a;
	}
	return ret;
}
int fromto(int from, int to, int step) {
	int t = 0;
	while(from % step)
		from++;
	for(int i=from; i<=to; i+=step) {
		if((mask & i) == mask)
			t++;
	}
	return t;
}
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> a >> b;
	for(int i=0; i<n; i++) {
		cin >> arr[i];
		mask |= (1 << arr[i]);
	}
	if(a >= 50) {
		return !(cout << fromto(a, b, a));
	}
	memset(dp, -1, sizeof dp);
	int lgmask = (mask & (((1 << HLF) - 1) << HLF)) >> HLF, smmask = mask & ((1<<HLF)-1);
	int ans = 0;
	if(!n)
		ans--;
	for(int i=0; i<=b; i+=(1<<HLF)) {
		if(((i >> HLF) & lgmask) == lgmask) {
			if((i >> HLF) == (b >> HLF)) {
				ans += fromto(i, b, a);
				return !(cout << ans);
			}
			//printf("added at i=%d\n", i);
			ans += f(i);
		}
		//printf("after i=%d, ans = %d\n", i, ans);
	}
	cout << ans;
}

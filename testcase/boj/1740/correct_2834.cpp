#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
ll cb[40];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cb[0] = 1;
	for(int i=1; i<40; i++)
		cb[i] = cb[i-1]*3;
	ll n, ans = 0;
	cin >> n;
	for(int i=0; i<40; i++)
		if(n&(1ll<<i)) {
			ans += cb[i];
		}
	cout << ans;
}

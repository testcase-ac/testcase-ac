#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 100007;
int jmp[MX][101], arr[MX], ans[101];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
		memset(ans, 0, sizeof ans);
		int n;
		cin >> n;
		if(!n) break;
		for(int i=0; i<n; i++)
			cin >> arr[i];
		for(int i=0; i<101; i++) {
			jmp[n-1][i] = MX;
		}
		for(int i=n-1; i; i--) {
			memcpy(jmp[i-1], jmp[i], sizeof jmp[0]);
			for(int j=1; j<=100; j++) {
				if(arr[i] % j != 0)
					jmp[i-1][j] = i;
			}
		}
		for(int i=0; i<n; i++) {
			//printf("start from i=%d\n", i);
			int curi = i, curv = arr[i];
			ans[arr[i]] = 1;
			while(curi < MX && curv > 1) {
				curv = gcd(curv, arr[curi]);
				ans[curv] = 1;
				curi = jmp[curi][curv];
				//printf("will jump to curi=%d, now curv = %d\n", curi, curv);
			}
		}
		int v = 0;
		for(int i=1; i<=100; i++)
			if(ans[i])
				v++;
		cout << v << '\n';
	}
}

#include <bits/stdc++.h>
using namespace std;
const int MX = 1e5+3;
int arr[MX], buk[MX];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	int k = sqrt(n);
	while(m--) {
		int s, a, ans = 0;
		cin >> s >> a;
		for(int i=a; i<s+a;) {
			if((i-1)%k == 0 && (i+k-1<s+a || (i+k-1>n && s+a-1==n))) {
				buk[(i-1)/k]++;
				ans += buk[(i-1)/k];
				i += k;
			} else {
				arr[i]++;
				ans += arr[i];
				i++;
			}
		}
		cout << ans << '\n';
	}
}

#include <bits/stdc++.h>
using namespace std;
int pos[11];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	memset(pos, -1, sizeof pos);
	int n, ans = 0;
	cin >> n;
	while(n--) {
		int a, b;
		cin >> a >> b;
		if(pos[a] == -1)
			pos[a] = b;
		else if(pos[a] != b) {
			pos[a] = b;
			ans++;
		}
	}
	cout << ans;
}

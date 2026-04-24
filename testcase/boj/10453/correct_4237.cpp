#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string a, b;
		cin >> a >> b;
        if(a.size() != b.size()) {
            cout << -1 << '\n';
            continue; 
        }
		int j = 0, n = a.size(), ans = 0;
		for(int i=0; i<n; i++) {
			if(a[i] == 'a') {
				while(j < n && b[j] != 'a') j++;
				ans += abs(j-i);
				j++;
			}
		}
		cout << ans << '\n';
	}
}

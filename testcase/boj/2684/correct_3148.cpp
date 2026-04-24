#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string s;
		cin >> s;
		int cnt[8] = {};
		for(int i=0; i<=37; i++) {
			int h = 0;
			for(int j=0; j<3; j++) {
				h *= 2;
				h += (s[i+j] == 'H');
			}
			cnt[h]++;
		}
		for(int i=0; i<8; i++) {
			cout << cnt[i] << ' ';
		}
		cout << '\n';
	}
}

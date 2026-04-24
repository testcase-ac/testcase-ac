#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		string a, b;
		cin >> a >> b;
		int cnt = 0;
		for(int i=0; i<(int)a.size(); i++) {
			if(a[i] != b[i]) cnt++;
		}
		printf("Hamming distance is %d.\n", cnt);
	}
}

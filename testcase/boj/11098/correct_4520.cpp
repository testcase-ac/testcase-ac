#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	while(n--) {
		int p;
		cin >> p;
		int maxc = 0;
		string maxn;
		for(int i=0; i<p; i++) {
			int c;
			string nm;
			cin >> c >> nm;
			if(c > maxc) {
				maxc = c;
				maxn = nm;
			}
		}
		cout << maxn << '\n';
	}	
}

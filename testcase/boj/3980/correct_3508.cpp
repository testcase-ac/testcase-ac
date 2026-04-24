#include <bits/stdc++.h>
using namespace std;
vector<pair<int, int>> arr[11];
int ans;
bool has[11];
void f(int d, int a) {
	if(d == 11) {
		ans = max(ans, a);
		return;
	}
	for(auto pr: arr[d]) {
		if(!has[pr.first]) {
			has[pr.first] = 1;
			f(d+1, a+pr.second);
			has[pr.first] = 0;
		}
	}
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		for(int i=0; i<11; i++) {
            arr[i].clear();
			for(int j=0; j<11; j++) {
				int t;
				cin >> t;
				if(t)
					arr[i].push_back({j,t});
			}
		}
		ans = 0;
		f(0, 0);
		cout << ans << '\n';
	}
	
}

#include <iostream>
#include <vector>
#include <bit>
using namespace std;
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	for(int tc=1; tc<=T; tc++) {
		int n;
		cin >> n;
		vector<int> ans;
		for(int i=1; i<(1<<n); i++) {
			vector<int> v;
			if(i == 11) {
				(void)0;
			}
			for(int t=0; t<n; t++) {
				if(i & (1<<t))
					v.push_back(t+1);
			}
			if(v.size() <= ans.size())
				continue;
			bool ok = 1;
			for(int a=0; a<v.size(); a++) {
				for(int b=a+1; b<v.size(); b++) {
					for(int c=b+1; c<v.size(); c++) {
						if(((v[a] ^ v[b]) ^ v[c]) == 0) {
							ok = 0;
							goto check;
						}
					}
				}
			}
			check:;
			if(ok) {
				ans = v;
			}
		}
		cout << ans.size() << '\n';
		for(int a: ans)
			cout << a << ' ';
		cout << '\n';
	}
}

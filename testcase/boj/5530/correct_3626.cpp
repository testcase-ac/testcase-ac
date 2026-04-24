#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MX = 1e6+2;
bool used[MX];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	string s;
	int n;
	cin >> n >> s;
	reverse(s.begin(), s.end());
	int l = 0, r = n/3;
	vector<int> v;
	deque<int> dq;
	while(l < r) {
		int m = (l+r+1)/2;
		v.clear();
		dq.clear();
		memset(used, 0, sizeof used);
		int icnt = 0;
		bool ok = 1;
		for(int i=0; i<n; i++) {
			if(v.size() == m)
				break;
			if(s[i] == 'I') {
				icnt++;
				dq.push_back(i);
			}
			else if(s[i] == 'O' && icnt) {
				icnt--;
				used[dq.front()] = 1;
				dq.pop_front();
				v.push_back(i);
			}
		}
		if(v.size() < m)
			ok = 0;
		else {
			for(int i=n-1; i>=0; i--) {
				if(used[i]) continue;
				if(v.empty()) break;
				if(s[i] == 'J' || s[i] == 'I') {
					if(v.back() > i) {
						break;
					}
					v.pop_back();
				}
			}
			if(v.size())
				ok = 0;			
		}
		if(!ok) {
			r = m-1;
		} else {
			l = m;
		}
	}
	cout << l;
}

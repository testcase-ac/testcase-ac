#include <bits/stdc++.h>
using namespace std;

const int MX = 200005;
map<int, int> Amp, Bmp;
int acnt = 1, bcnt = 1, input[MX][3], segtree[2*MX];
set<pair<int, int>> bucket[MX];
vector<pair<int, int>> students = {{0,0}};
void update(int i, int v) {
	i += acnt;
	segtree[i] = max(segtree[i], v);
	while(i/=2) {
		segtree[i] = max(segtree[2*i], segtree[2*i+1]);
	}
}
int query(int l, int r) {
	l += acnt, r += acnt;
	int ret = -1;
	while(l < r) {
		if(l&1) ret = max(ret, segtree[l++]);
		if(r&1) ret = max(ret, segtree[--r]);
		l /= 2, r /= 2;
	}
	return ret;
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		char c;
		int a, b;
		cin >> c;
		if(c == 'D') {
			cin >> b >> a;
			Amp[a] = 0;
			Bmp[b] = 0;
			input[i][1] = a;
			input[i][2] = b;
		} else {
			cin >> a;
			input[i][0] = 1;
			input[i][1] = a;
		}
	}
	for(auto &pr: Amp)
		pr.second = acnt++;
	for(auto &pr: Bmp)
		pr.second = bcnt++;
	for(int i=0; i<n; i++) {
		int t = input[i][0];
		if(t) {
			int p = input[i][1], a, b, l, r, mid;
			tie(a, b) = students[p];
			auto it = bucket[a].lower_bound({b+1,0});
			if(it != bucket[a].end()) {
				cout << it->second << '\n';
			} else {
				l = a+1, r = acnt-1;
				while(l < r) {
					mid = (l+r)/2;
					if(query(l, mid+1) >= b) r = mid;
					else l = mid+1;
				}
				it = bucket[l].lower_bound({b,0});
				if(it == bucket[l].end()) cout << "NE\n";
				else cout << it->second << '\n';
			}
		} else {
			int a = Amp[input[i][1]], b = Bmp[input[i][2]];
			bucket[a].insert({b, students.size()});
			students.push_back({a,b});
			update(a, b);
		}
	}
}

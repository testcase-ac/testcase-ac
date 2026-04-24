#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		int n, t, mid;
		multiset<int> l, r;
		cin >> n >> mid;
		n /= 2;
		cout << n+1 << '\n';
		cout << mid << ' ';
		for(int i=0; i<n; i++) {
			if(i % 10 == 9) cout << '\n';
			for(int j=0; j<2; j++) {
				cin >> t;
				if(t < mid)
					l.insert(t);
				else
					r.insert(t);
			}
			if(l.size() > r.size()) {
				r.insert(mid);
				mid = *l.rbegin();				
				l.erase(prev(l.end()));
			} else if(l.size() < r.size()) {
				l.insert(mid);
				mid = *r.begin();
				r.erase(r.begin());
			}
			cout << mid << ' ';
		}
		cout << '\n';
	}
}

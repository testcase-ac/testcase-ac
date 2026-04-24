#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int T;
	cin >> T;
	while(T--) {
		multiset<int> ms;
		int k;
		cin >> k;
		while(k--) {
			char d;
			int n;
			cin >> d >> n;
			if(d == 'I')
				ms.insert(n);
			else if(n == 1) {
				if(!ms.empty())
					ms.erase(prev(ms.end()));
			}
			else {
				if(!ms.empty())
					ms.erase(ms.begin());
			}
		}
		if(ms.empty()) cout << "EMPTY\n";
		else cout << *ms.rbegin() << ' ' << *ms.begin() << '\n';
	}
}

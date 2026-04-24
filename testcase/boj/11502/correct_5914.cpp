#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	vector<int> prime = {2,3}, prime2;
	for(int i=5; i<=1000; i++) {
		bool ok = true;
		for(int p: prime) {
			if(p > sqrt(i)) break;
			if(i % p == 0) {
				ok = false;
				break;
			}
		}
		if(ok) prime.push_back(i);
	}
	for(int p: prime) for(int p2: prime) prime2.push_back(p+p2);
	sort(prime2.begin(), prime2.end());
	int T;
	cin >> T;
	while(T--) {
		int n;
		cin >> n;
		for(int p: prime) {
			if(binary_search(prime2.begin(), prime2.end(), n-p)) {
				for(int p2: prime) {
					if(binary_search(prime.begin(), prime.end(), n-p-p2)) {
						int ans[3] = {p, p2, n-p-p2};
						sort(ans, ans+3);
						for(int a: ans) cout << a << ' ';
						cout << '\n';
						goto nexttc;
					}
				}
			}
		}
		nexttc:;
	}
}

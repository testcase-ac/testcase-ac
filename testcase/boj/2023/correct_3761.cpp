#include <bits/stdc++.h>
using namespace std;

int ls[] = {1, 3, 7, 9};
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<int> primes = {2};
	for(int i=3; i<30000; i+=2) {
		bool ok = true;
		int s = (int)sqrt(i);
		for(int p: primes) {
			if(p > s) break;
			if(i % p == 0) {
				ok = false;
				break;
			}
		}
		if(ok)
			primes.push_back(i);
	}
	vector<int> prev, curr = {2,3,5,7};
	for(int t=2; t<=n; t++) {
		prev = curr;
		curr.clear();
		for(int p: prev) {
			for(int i: ls) {
				int tp = p*10 + i;
				int s = (int)sqrt(tp);
				bool ok = true;
				for(int k: primes) {
					if(k > s) break;
					if(tp % k == 0) {
						ok = false;
						break;
					}
				}
				if(ok)
					curr.push_back(tp);
			}
		}
	}
	for(int p: curr) cout << p << '\n';
}

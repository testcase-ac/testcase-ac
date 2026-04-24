#include <bits/stdc++.h>
using namespace std;
int seq[100];
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, k;
	cin >> n >> k;
	set<int> nset;
	int ans = 0;
	for(int i=0; i<k; i++) {
		cin >> seq[i];
	}
	for(int i=0; i<k; i++) {
		if(nset.size() < n)
			nset.insert(seq[i]);
		else {
			if(nset.count(seq[i])) continue;
			set<int> tset = nset;
			for(int j=i+1; j<k; j++) {
				if(tset.size() == 1)
					break;
				tset.erase(seq[j]);
			}
			int torm = *tset.begin();
			nset.erase(torm);
			nset.insert(seq[i]);
			ans++;
		}
	}
	cout << ans;
}

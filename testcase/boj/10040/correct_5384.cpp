#include <bits/stdc++.h>
using namespace std;

int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n, m;
	cin >> n >> m;
	vector<int> a(n), cnt(n);
	for(int i=0; i<n; i++) {
		cin >> a[i];
	}
	for(int i=0; i<m; i++) {
		int b;
		cin >> b;
		for(int j=0; j<n; j++) {
			if(a[j] <= b) {
				cnt[j]++;
				break;
			}
		}
	}
	cout << max_element(cnt.begin(), cnt.end()) - cnt.begin()+1;
}

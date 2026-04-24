#include <bits/stdc++.h>
using namespace std;
int main() {
	int n, c;
	cin >> n >> c;
    int a[n];
	map<int,int> cnt, occ;
	for(int i=0; i<n; i++) {
		cin >> a[i];
		cnt[a[i]]++;
	}
    for(int i=n-1; i>=0; i--) {
        occ[a[i]] = i;
    }
	sort(a, a+n, [&](int i, int j){return cnt[i]==cnt[j] ? occ[i]<occ[j] :cnt[i]>cnt[j];});
    for(int i: a)
        cout << i << ' ';
}

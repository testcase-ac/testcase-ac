#include <bits/stdc++.h>
using namespace std;

struct Ball {
	int color, size;
};
Ball arr[200000];
vector<int> bysz[2001];
int colsum[200001], ans[200000], tsum;
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	for(int i=0; i<n; i++) {
		cin >> arr[i].color >> arr[i].size;
		bysz[arr[i].size].push_back(i);
	}
	for(int sz=1; sz<=2000; sz++) {
		for(int i: bysz[sz])
			ans[i] = tsum - colsum[arr[i].color];
		for(int i: bysz[sz]) {
			tsum += arr[i].size;
			colsum[arr[i].color] += arr[i].size;
		}
	}
	for(int i=0; i<n; i++) {
		cout << ans[i] << '\n';
	}
}

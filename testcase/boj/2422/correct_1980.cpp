#include <bits/stdc++.h>
using namespace std;
int n, m, ans;
vector<int> v;
pair<int, int> prs[10000];
void f(int t) {
	v.push_back(t);
	if(v.size() == 3) {
		for(int i=0; i<3; i++) {
			for(int j=i+1; j<3; j++) {
				if(binary_search(prs, prs+m, make_pair(v[i],v[j]))) {
					v.pop_back();
					return;
				}
			}
		}
		ans++;
	} else {
		for(int i=t+1; i<=n-2+(int)v.size(); i++)
			f(i);
	}
	v.pop_back();
}
int main() {
	ios::sync_with_stdio(0);cin.tie(0);
	cin >> n >> m;
	if(n < 3) return !(cout << 0);
	for(int i=0; i<m; i++) {
		auto &pr = prs[i];
		cin >> pr.first >> pr.second;
		if(pr.first > pr.second)
			swap(pr.first, pr.second);
	}
	sort(prs, prs+m);
	for(int i=1; i<=n-2; i++)
		f(i);
	cout << ans;
}

#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
int n, k, p;
vector<int> child, parent;
void buildchild(int i) {
	if(2*i<=n) {
		child.push_back(2*i);
		buildchild(2*i);
	}
	if(2*i+1<=n) {
		child.push_back(2*i+1);
		buildchild(2*i+1);
	}
}
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	cin >> n >> k >> p;
	int t = p;
	while(t > 1) {
		t /= 2;
		parent.push_back(t);
	}
	reverse(parent.begin(), parent.end());
	buildchild(p);
	sort(child.begin(), child.end());
	//printf("sz(parent)=%d\n", sz(parent));
	if(sz(parent) >= k || sz(child) > (n-k)) return !(cout << -1);
	int nextsm = 1, nextlg = n, nextfree = sz(parent)+1;
	for(int i=1; i<=n; i++) {
		if(i == p) {
			cout << k << '\n';
		} else if(binary_search(parent.begin(), parent.end(), i)) {
			cout << nextsm++ << '\n';
		} else if(binary_search(child.begin(), child.end(), i)) {
			cout << nextlg-- << '\n';
		} else {
			if(nextfree == k) nextfree++;
			cout << nextfree++ << '\n';
		}
	}
}

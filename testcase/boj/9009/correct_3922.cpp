#include <bits/stdc++.h>
#define sz(x) ((int)((x).size()))
#define all(x) x.begin(), x.end()
using namespace std;
vector<int> v = {1,2}, vc = {1,3};
vector<int> stored[100001];
int canuse = 0;
vector<int> find(int n) {
    if(n <= canuse)
        return stored[n];
    if(binary_search(all(v), n))
        return {n};
    int lb = lower_bound(all(vc), n) - vc.begin();
    auto it = v.begin() + lb;
    vector<int> ret;
    int s = INT_MAX;
    for(;it!=v.end();it++) {
        if(*it <= n/2) continue;
        if(*it > n) break;
        auto f = find(n - *it);
        if(sz(f) < s) {
            s = sz(f);
            ret = f;
            ret.push_back(*it);
        }
    }
    assert(s != INT_MAX);
    return ret;
}
int main() {
    ios::sync_with_stdio(0);cin.tie(0);
	while(1) {
        int nxt = v[sz(v)-1] + v[sz(v)-2];
        if(nxt > 1000000000) break;
        v.push_back(nxt);
        vc.push_back(vc.back()+nxt);
	}
	for(int i=1; i<=100000; i++) {
        stored[i] = find(i);
        canuse = i;
	}
	//printf("ok at %.3f\n", (double)clock() / CLOCKS_PER_SEC);
	int T;
	cin >> T;
	while(T--) {
        int n;
        cin >> n;
        auto f = find(n);
        sort(all(f));
        for(int i: f) cout << i << ' ';
        cout << '\n';
	}
}

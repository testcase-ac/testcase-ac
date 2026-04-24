#include <bits/stdc++.h>
using namespace std;
#define int long long
struct segtree {
	vector<pair<int, int>> tree;
	vector<int> lazy;
	int n, h;
	segtree(int _n) {
		n = _n;
		tree.resize(2*n);
		lazy.resize(n);
		h = 32 - __builtin_clz(n);
	}
	pair<int, int> combine(pair<int, int> a, pair<int, int> b) {
		return {min(a.first, b.first), max(a.second, b.second)};
	}
	// p번 노드에 val만큼의 수정을 추가로 반영함.
	void apply_lazy(int p, int val) { 
		tree[p].first += val;
		tree[p].second += val;
	}
	// p번 노드가 update나 push로부터 lazy정보를 받았을 때, 노드 자체 정보와 lazy에 그걸 반영함.
	void apply(int p, int val) { 
		apply_lazy(p, val);
		if(p < n) lazy[p] += val;
	}
	// p번 노드의 부모가 자식들의 값과 자신의 레이지 값으로 자신을 다시 빌드함.
	// update의 base에서 호출됨으로서 update범위와 교차하는 노드들의 tree값을 정확하게 바꿈. ("Modification on interval [l, r) affects t[i] values only in the parents of border leaves..")
	void build(int p) {
		while(p > 1) {
			p /= 2;
			tree[p] = combine(tree[p*2], tree[p*2+1]);
			apply_lazy(p, lazy[p]);
		}
	}
	// p번 노드의 부모가 자신의 lazy를 밑으로 전파하도록 함.
	// query의 base에서 호출됨으로서 query범위 위의 미처 반영되지 않은 레이지 정보를 가져옴. (ex. 긴 노드에 레이지가 있고 쿼리범위는 그 안)
	void push(int p) {
		for(int s=h; s; s--) {
			int i = p >> s;
			if(lazy[i] != 0) {
				apply(i*2, lazy[i]);
				apply(i*2+1, lazy[i]);
				lazy[i] = 0;
			}
		}
	}
	void update(int l, int r, int diff) {
		l += n, r += n;
		int l0 = l, r0 = r;
		while(l < r) {
			if(l&1) apply(l++, diff);
			if(r&1) apply(--r, diff);
			l /= 2, r /= 2;
		}
		build(l0);
		build(r0-1);
	}
	pair<int, int> query(int l, int r) {
		l += n, r += n;
		push(l);
		push(r-1);
		pair<int, int> res = {INT_MAX, INT_MIN};
		while(l < r) {
			if(l&1) res = combine(res, tree[l++]);
			if(r&1) res = combine(res, tree[--r]);
			l /= 2, r /= 2;
		}
		return res;
	}
};
int ended[200001], started[200001], cnts[200001], cnte[200001];
int32_t main() {
	ios::sync_with_stdio(0);cin.tie(0);
	int n;
	cin >> n;
	vector<pair<int, int>> a(n);
	vector<int> num(2*n);
	for(int i=0; i<n; i++) {
		int t;
		cin >> t >> a[i].second >> t >> a[i].first;
		num[2*i] = a[i].first;
		num[2*i+1] = a[i].second;
	}
	sort(num.begin(), num.end());
	num.erase(unique(num.begin(), num.end()), num.end());
	for(int i=0; i<n; i++) {
		a[i].first = lower_bound(num.begin(), num.end(), a[i].first) - num.begin();
		a[i].second = lower_bound(num.begin(), num.end(), a[i].second) - num.begin();
		cnts[a[i].first]++;
		cnte[a[i].second]++;
	}
	segtree seg(num.size());
	sort(a.begin(), a.end(), [](auto x, auto y){return x.second < y.second;});
	int j = 0;
	for(int i=0; i<num.size(); i++) {
		while(j < a.size() && a[j].second == i) {
			seg.update(a[j].first, a[j].second+1, 1);
			j++;
		}
		ended[i] = seg.query(0, num.size()).second;
	}

	seg = segtree(num.size());	
	sort(a.begin(), a.end(), [](auto x, auto y){return x.first > y.first;});
	j = 0;
	for(int i=num.size()-1; i>=0; i--) {
		while(j < a.size() && a[j].first == i) {
			seg.update(a[j].first, a[j].second+1, 1);
			j++;
		}
		started[i] = seg.query(0, num.size()).second;
	}
	
	int cnt = 0, ans = 0;
	for(int i=0; i<num.size(); i++) {
		cnt += cnts[i];
		if(i && i+1 < num.size()) {
			ans = max(ans, cnt + max(ended[i-1], started[i+1]));
		}
		cnt -= cnte[i];
	}
	cout << ans;
}

#include <bits/stdc++.h>
using namespace std;
using lint = long long;
using pi = pair<lint, lint>;

map<pi, int> mp;

int query(lint s, lint e){
	if(s == 0 && e == 0) return 0;
	if(mp.find(pi(s, e)) != mp.end()) return mp[pi(s, e)];
	int ret = 0;
	for(int i=1; i<40; i++){ 
		lint st = (1ll << i) - 1, ed = (2ll << i) - 2;
		st = max(st, s);
		ed = min(ed, e);
		if(st <= ed) ret = max(ret, query(st - (1ll << i) + 1, ed - (1ll << i) + 1) + i);
	}
	return mp[pi(s, e)] = ret;
}

int main(){
	int t; cin >> t;
	while(t--){
		int l, r; cin >> l >> r;
		printf("%d\n", query(l, r));
	}
  return 0;
}

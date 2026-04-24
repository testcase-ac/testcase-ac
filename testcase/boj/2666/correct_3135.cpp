#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;

int n, m, order[20];
bool seen[21][400];
struct State {
	int ua, ub, depth;
	State() {
		ua = ub = depth = 0;
	}
	int hash() {
		if(ua > ub) swap(ua, ub);
		return ua*20+ub;
	}
	bool seenthis() {
		return seen[depth][hash()];
	}
	void updateDepth() {
		while(depth < m && (ua == order[depth] || ub == order[depth]))
			depth++;
	}
	bool finished() {
		updateDepth();
		return depth == m;
	}
	void markseen() {
		seen[depth][hash()] = true;
	}
	bool nextstate(int i) {
		if(i == 0) {
			if(!ua) return false;
			ua--;			
		} else if(i == 1) {
			if(ua+1 == ub) return false;
			ua++;			
		} else if(i == 2) {
			if(ub-1==ua) return false;
			ub--;			
		} else if(i == 3) {
			if(ub+1==n) return false;
			ub++;
		}
		updateDepth();
		if(seenthis()) return false;
		markseen();
		return true;
	}
	void print() {
		printf("ua,ub,depth=%d,%d,%d\n", ua,ub,depth);
	}
};

int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	State state;
	cin >> n >> state.ua >> state.ub >> m;
	state.ua--, state.ub--;
	rep(i,m) {
		cin >> order[i];
		order[i]--;
	}
	if(state.finished()) return !(cout << 0);
	queue<State> que;
	state.markseen();
	que.push(state);
	int t = 1;
	while(!que.empty()) {
		int z = sz(que);
		//printf("at t=%d:\n", t);
		while(z--) {
			State s = que.front();
			que.pop();
			rep(i,4) {
				State ns = s;
				if(!ns.nextstate(i)) continue;
				//ns.print();
				if(ns.finished()) return !(cout << t);
				que.push(ns);
			}
		}
		t++;
	}
}

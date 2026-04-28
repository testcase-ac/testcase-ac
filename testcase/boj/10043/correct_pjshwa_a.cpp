#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int in() {
	int a;
	scanf("%d", &a);
	return a;
}

typedef vector<int> vint;
typedef pair<int, int> pint;
typedef vector<pint> vpint;

const int INF = 1001001001;

#define pb push_back
#define mp make_pair
#define rep(i,n) for(int i = 0; i < n; i++)

struct Taxi {
	int C, R;
	vint edges, edges2;
	bool flag;
	int ans;
	Taxi ()
		: flag(false), ans(INF) {
	}
} taxis[5010];

int main() {
	int N, K;
	N = in();
	K = in();
	
	for (int i = 0; i < N; i++) {
		taxis[i].C = in();
		taxis[i].R = in();
	}
	for (int i = 0; i < K; i++) {
		int to, from;
		to = in() - 1;
		from = in() - 1;
		taxis[to].edges.pb(from);
		taxis[from].edges.pb(to);
	}
	
	// make a graph
	rep(i, N) {
		queue<int> q;
		q.push(i);
		rep(k, taxis[i].R) {
			queue<int> q2;
			while (! q.empty()) {
				int n = q.front();
				q.pop();
				rep(j, taxis[n].edges.size()) {
					int to = taxis[n].edges[j];
					if (! taxis[to].flag) {
						taxis[to].flag = true;
						q2.push(to);
					}
				}
			}
			q = q2;
		}
		rep(k, N) {
			if (i != k && taxis[k].flag) {
				taxis[i].edges2.pb(k);
			}
			taxis[k].flag = false;
		}
	}
	
	// Dijkstra
	priority_queue<pint> pq;
	pq.push(mp(0, 0));
	while (pq.size()) {
		pint a = pq.top();
		pq.pop();
		int cost = - a.first;
		int n = a.second;
		
		if (cost < taxis[n].ans) {
			taxis[n].ans = cost;
			if (n == N - 1) {
				break;
			}
			for (vint::iterator iter = taxis[n].edges2.begin(); iter != taxis[n].edges2.end(); ++iter) {
				if (taxis[*iter].ans == INF) {
					pq.push(mp(- (cost + taxis[n].C), *iter));
				}
			}
		}
	}
	
	cout << taxis[N - 1].ans << endl;
	return 0;
}

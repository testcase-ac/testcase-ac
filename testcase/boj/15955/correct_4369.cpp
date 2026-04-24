#include <bits/stdc++.h>
#define MOD 1000000007
#define ll long long
#define sz(x) ((int)(x).size())
#define rep(i,n) for(int i=0; i<(n); i++)
#define deb(v) cout << #v << ':' << v << '\n';

using namespace std;
struct Point {
	int x, y, index;
};
Point pointsX[250000], pointsY[250000];
int parent[250000];
int find(int i) {return parent[i] == i ? i : parent[i] = find(parent[i]);}
void joinroot(int i, int j) {
	parent[i] = j;
}
struct Query {
	int a, b, x, index;
	bool operator< (const Query &q) const {
		return x < q.x;
	}
};
Query querys[250000];
bool ans[250000];
struct JoinInfo {
	int dist, i, j;
	bool operator< (const JoinInfo &ji) const {
		return dist > ji.dist;
	}
};
int main() {
	ios::sync_with_stdio(false);cin.tie(NULL);
	int n, q;
	cin >> n >> q;
	rep(i,n) {
		cin >> pointsX[i].x >> pointsX[i].y;
		pointsX[i].index = i;
		pointsY[i] = pointsX[i];
		parent[i] = i;
	}
	sort(pointsX, pointsX+n, [](const Point &a, const Point &b){return a.x < b.x;});
	sort(pointsY, pointsY+n, [](const Point &a, const Point &b){return a.y < b.y;});
	priority_queue<JoinInfo> pq;
	for(int i=0; i<n-1; i++) {
		pq.push({pointsX[i+1].x-pointsX[i].x, pointsX[i].index, pointsX[i+1].index});
		pq.push({pointsY[i+1].y-pointsY[i].y, pointsY[i].index, pointsY[i+1].index});
	}
	rep(i,q) {
		cin >> querys[i].a >> querys[i].b >> querys[i].x;
		querys[i].a--, querys[i].b--;
		querys[i].index = i;
	}
	sort(querys, querys+q);
	for(int i=0; i<q; i++) {
		Query &qry = querys[i];
		while(!pq.empty() && pq.top().dist <= qry.x) {
			joinroot(find(pq.top().i), find(pq.top().j));
			pq.pop();
		}
		ans[qry.index] = (find(qry.a) == find(qry.b) ? true: false);
	}
	for(int i=0; i<q; i++) cout << (ans[i] ? "YES\n" : "NO\n");
}

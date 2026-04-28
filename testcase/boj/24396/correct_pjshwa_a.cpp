#include <bits/stdc++.h>
#define X first
#define Y second
#define pb push_back
#define all(x) x.begin(), x.end()
#define fastio ios::sync_with_stdio(false); cin.tie(nullptr); cout.tie(nullptr);
#define MS(x,y) memset(x,y,sizeof(x))
#define rep(x) for(int i=0;i<x;i++)
#define repp(x) for(int j=0;j<x;j++)
#define READGRID(x,y) rep(x)repp(y) cin>>arr[i][j]
#define INF 2147483647
#define MAX 300001
#define DEBUG(x) cout<<#x<<" is "<<x<<"\n";
using namespace std;
typedef long long ll;
typedef pair<int,int> pi;
typedef pair<ll,ll> pl;
const int dx[] = { -1, 1, 0, 0, -1, 1, 1, -1 };
const int dy[] = { 0, 0, -1, 1, 1, 1, -1, -1 };

int n,m,a,b,visited[MAX];
vector<int> adj[MAX];
int main(void){
	fastio
	
	cin>>n>>m;

	rep(m){
		cin>>a>>b;	
		adj[a].pb(b);
		adj[b].pb(a);
	}
	for(int i=1;i<=n;i++){
		sort(all(adj[i]));
	}
    MS(visited,-1);
	queue<int> q;
	set<int> not_visited;
	for(int i=2;i<=n;i++) not_visited.insert(i);
	visited[1]=0;
	q.push(1);
	while(!q.empty()){
		ll now = q.front(); q.pop();
		
		for(auto it = not_visited.begin();it!=not_visited.end();){
			ll next = *it;
			if (!binary_search(all(adj[now]), next)) {
                visited[next] = visited[now] + 1;
                q.push(next);
                it = not_visited.erase(it);
            }
            else
                it++;

		}
	}
	for(int j=1;j<=n;j++){
		cout<<visited[j]<<"\n";
	}
}

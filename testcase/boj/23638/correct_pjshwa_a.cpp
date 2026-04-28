#include<bits/stdc++.h>
using namespace std;
vector<int>graph[200005];
bool v[200005];
bool fin[200005];
int target = 0,ans = 0;
vector<int>cycle;
bool DFS(int cur,int p){
	v[cur] = 1;
	for(int nxt:graph[cur]){
		if(nxt==p) continue;
		if(!v[nxt]){
			bool in = DFS(nxt,cur);
			if(in){
				cycle.emplace_back(cur);
				fin[cur] = 1;
				if(cur==target) return 0;
				else return 1;
			}
		}
		else if(!fin[nxt]){
			target = nxt;
			cycle.emplace_back(cur);
			fin[cur] = 1;
			return 1;
		}
	}
	fin[cur] = 1;
	return 0;
}
int dist[200005];
int f(int cur){
	dist[cur] = 0;
	vector<int>child;
	for(int nxt:graph[cur]){
		if(dist[nxt]!=-1) continue;
		child.emplace_back(f(nxt));
	}
	sort(child.begin(),child.end());
	if(child.size()){
		if(child.size()==1){
			dist[cur] = child.back()+1;
			ans = max(ans,dist[cur]);
		}
		else{
			ans = max(ans,child.back()+child[child.size()-2]+2);
			dist[cur] = child.back()+1;
		}
	}
	return dist[cur];
}
int D[200005];
int prefix[200005];
int suffix[200005];

int main(){
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; cin>>n;
	for(int i=1; i<=n; i++){
		int a,b; cin>>a>>b;
		graph[a].emplace_back(b);
		graph[b].emplace_back(a);
	}	
	DFS(1,0); cout<<cycle.size()<<" ";
	memset(dist,-1,sizeof(dist));
	for(int x : cycle) dist[x] = 0;
	for(int i=0; i<cycle.size(); i++) D[i+1] = f(cycle[i]);
	n = cycle.size();
	for(int i=1; i<=n; i++){
		prefix[i] = D[i]+i;
		prefix[i] = max(prefix[i],prefix[i-1]);
	}
	for(int i=n; i>=1; i--){
		suffix[i] = D[i]+(n-i);
		suffix[i] = max(suffix[i],suffix[i+1]);
	}
	int mx = D[1]-1;
	for(int i=2; i<=n; i++){
		ans = max(ans,D[i]+i+mx);
		mx = max(mx,D[i]-i);
	}

	for(int i=1; i<n; i++) ans = max(ans,prefix[i]+suffix[i+1]);
	cout<<ans;
}

#include <bits/stdc++.h>
using namespace std;
int a[1000][1000];
bool vis[1000][1000];
int n,m;
int d[19][4][2]={
	{{0,0},{0,1},{0,2},{0,3}},
    {{0,0},{1,0},{2,0},{3,0}},
    {{0,0},{0,1},{1,1},{1,0}},
    {{0,0},{1,0},{2,0},{2,1}},
    {{0,0},{1,0},{2,0},{2,-1}},
    {{0,0},{0,1},{1,0},{2,0}},
    {{0,0},{0,-1},{1,0},{2,0}},
    {{0,0},{1,0},{0,-1},{0,-2}},
    {{0,0},{1,0},{0,1},{0,2}},
    {{0,0},{1,0},{1,1},{1,2}},
    {{0,0},{1,0},{1,-1},{1,-2}},
    {{0,0},{1,0},{1,1},{2,1}},
    {{0,0},{1,0},{1,-1},{2,-1}},
    {{0,0},{0,1},{1,1},{1,2}},
    {{0,0},{0,1},{-1,1},{-1,2}},
    {{0,0},{-1,-1},{-1,0},{-1,1}},
    {{0,0},{1,-1},{1,0},{1,1}},
    {{0,0},{-1,-1},{0,-1},{1,-1}},
    {{0,0},{-1,1},{0,1},{1,1}}
};
bool chk(int x,int y,int k) {
	for(int l=0;l<4;l++) {
		int nx=x+d[k][l][0],ny=y+d[k][l][1];
		if(nx<0||nx>=n||ny<0||ny>=m) return 0;
		if(vis[nx][ny]) return 0;
	} return 1;
}
int sum(int x,int y,int k) {
	int s=0;
	for(int l=0;l<4;l++) s+=a[x+d[k][l][0]][y+d[k][l][1]];
	return s;
}
bool cmp(pair<pair<int,int>,pair<int,int>> a,pair<pair<int,int>,pair<int,int>> b) {
    return a.second.second>b.second.second;
}
int main() {
    ios::sync_with_stdio(0);
	cin.tie(0);
	cin>>n>>m;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) cin>>a[i][j];
	int ans=0;
	vector<pair<pair<int,int>,pair<int,int>>> v;
	for(int i=0;i<n;i++) for(int j=0;j<m;j++) {
		for(int k=0;k<19;k++) {
			if(!chk(i,j,k)) continue;
			v.push_back({{i,j},{k,sum(i,j,k)}});
		}
	} sort(v.begin(),v.end(),cmp);
	for(int x=0;x<min((int)v.size(),5000);x++) {
	    int s=v[x].second.second;
	    int i=v[x].first.first,j=v[x].first.second,k=v[x].second.first;
	    for(int l=0;l<4;l++) {
			int nx=i+d[k][l][0],ny=j+d[k][l][1];
			vis[nx][ny]=1;
		} for(int y=x+1;y<min((int)v.size(),5000);y++) {
		    int ii=v[y].first.first,jj=v[y].first.second,kk=v[y].second.first;
		    if(!chk(ii,jj,kk)) continue;
		    ans=max(ans,s+v[y].second.second);
		    break;
		} for(int l=0;l<4;l++) {
			int nx=i+d[k][l][0],ny=j+d[k][l][1];
			vis[nx][ny]=0;
		}
	} cout<<ans;
}

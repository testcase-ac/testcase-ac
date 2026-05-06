#include <bits/stdc++.h>
using namespace std;
int n,m,x,y,k;
vector<string> a;
vector<pair<double,double>> p;
void sol(int y,int x,pair<double,double> l,pair<int,double> d) {
	if(x==-1||x==m||y==-1||y==n||a[y][x]=='#') {
		p.push_back(l);
		return;
	} int x1=x+(d.first>0?1:-1),x2=x+(d.first>0?1:0);
	int y1=y+(d.first*d.second>0?1:-1),y2=y+(d.first*d.second>0?1:0);
	double qx=l.first+(y2-l.second)/d.second,qy=l.second+d.second*(x2-l.first);
	if(y+1e-9<qy&&qy<y+1-1e-9&&(qx<x-1e-9||qx>x+1+1e-9)) sol(y,x1,{x2,qy},d);
	else if(x+1e-9<qx&&qx<x+1-1e-9&&(qy<y-1e-9||qy>y+1+1e-9)) sol(y1,x,{qx,y2},d);
	else {
		l={x2,y2};
		if((d.second>0&&(x1==-1||x1==m||a[y][x1]=='#'))||(d.second<0&&(y1==-1||y1==n||a[y1][x]=='#'))) p.push_back(l);
		sol(y1,x1,l,d);
		if((d.second>0&&(y1==-1||y1==n||a[y1][x]=='#'))||(d.second<0&&(x1==-1||x1==m||a[y][x1]=='#'))) p.push_back(l);
	}
}
int main() {
    vector<pair<int,double>> ang;
    pair<double,double> l;
	cin>>n>>m;
	a.resize(n);
	for(int i=0;i<n;i++) cin>>a[i];
	for(int i=0;i<n;i++) {
		for(int j=0;j<m;j++) {
			if(a[i][j]=='*') {
				y=i;x=j;
				l={x+0.5,y+0.5};
			} else if(a[i][j]=='#') k++;
		}
	} set<pair<int,double>> s;
	for(int i=0;i<2;i++) {
		for(int j=0;j<2;j++) {
			int tx=m*j,ty=n*i;
			if(tx==l.first)continue;
			int dx=tx-l.first>0?1:-1;
			double dy=(ty-l.second)/(tx-l.first);
			s.insert({dx,dy});
		}
	} for(int i=0;i<=n;++i) {
		for(int j=0;j<=m;++j) {
			if(j==l.first)continue;
			int dx=j-l.first>0?1:-1;
			double dy=(i-l.second)/(j-l.first);
			s.insert({dx,dy});
		}
	} ang.assign(s.begin(),s.end());
	for(auto &z:ang) sol(y,x,l,z);
	double ar=0;
	int sz=p.size();
	for(int i=0;i<sz;i++) {
		int j=(i+1)%sz;
		ar+=l.first*p[i].second+p[i].first*p[j].second+p[j].first*l.second
			-p[i].first*l.second-p[j].first*p[i].second-l.first*p[j].second;
	} cout<<fixed<<setprecision(15)<<n*m-abs(ar)/2-k;
}

#include <bits/stdc++.h>
using namespace std;
int n;
vector<double> px,py,pz;
double sq(double a) {return a*a;}
double f(const vector<double>& p) {
	double x=p[0],y=p[1],z=p[2],r=0;
	for(int i=0;i<n;i++) r=max(r,sqrt(1e-9+sq(x-px[i])+sq(y-py[i])+sq(z-pz[i])));
	return r;
}
tuple<double,double,double> grad(const vector<double>& p) {
	double x=p[0],y=p[1],z=p[2];
	double dx=0,dy=0,dz=0,m=0;
	for(int i=0;i<n;i++) {
	    double d=sqrt(1e-9+sq(x-px[i])+sq(y-py[i])+sq(z-pz[i]));
		if(d>m) {
		    m=d;
		    dx=(x-px[i])/d;dy=(y-py[i])/d;dz=(z-pz[i])/d;
		}
	} return {dx,dy,dz};
}
double descent(vector<double> p) {
	double w=1e6;
	for(int i=0;i<30000;i++) {
		auto g=grad(p);
		p[0]-=w*get<0>(g);
		p[1]-=w*get<1>(g);
		p[2]-=w*get<2>(g);
		w*=0.999;
	} return f(p);
}
int main() {
	cin>>n;
	px.resize(n);py.resize(n);pz.resize(n);
	for(int i=0;i<n;i++) cin>>px[i]>>py[i]>>pz[i];
	double sx=0,sy=0,sz=0;
	for(int i=0;i<n;i++) sx+=px[i],sy+=py[i],sz+=pz[i];
	sx/=n;sy/=n;sz/=n;
	cout<<fixed<<setprecision(2)<<descent({sx,sy,sz});
}

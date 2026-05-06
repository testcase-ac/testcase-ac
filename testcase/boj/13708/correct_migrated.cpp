#include <bits/stdc++.h>
using namespace std;
int n;
vector<double> px,py;
double sq(double a) {return a*a;}
double f(const vector<double>& p) {
	double x=p[0],y=p[1],r=0;
	for(int i=0;i<n;i++) r=max(r,sqrt(1e-9+sq(x-px[i])+sq(y-py[i])));
	return 2*r;
}
pair<double,double> grad(const vector<double>& p) {
	double x=p[0],y=p[1];
	double dx=0,dy=0,m=0;
	for(int i=0;i<n;i++) {
	    double d=sqrt(1e-9+sq(x-px[i])+sq(y-py[i]));
		if(d>m) {
		    m=d;
		    dx=(x-px[i])/d;dy=(y-py[i])/d;
		}
	} return {dx,dy};
}
double descent(vector<double> p) {
	double w=1e6;
	for(int i=0;i<25000;i++) {
		auto g=grad(p);
		p[0]-=w*g.first;
		p[1]-=w*g.second;
		w*=0.999;
	} return f(p);
}
int main() {
	cin>>n;
	px.resize(n);py.resize(n);
	for(int i=0;i<n;i++) cin>>px[i]>>py[i];
	double sx=0,sy=0;
	for(int i=0;i<n;i++) sx+=px[i],sy+=py[i];
	sx/=n;sy/=n;
	cout<<fixed<<setprecision(2)<<descent({sx,sy});
}

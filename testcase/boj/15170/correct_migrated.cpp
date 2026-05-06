#include <bits/stdc++.h>
using namespace std;
vector<double> ix,iy,nx,ny;
bool ok(double cx,double cy){
	double a=0,b=1e9;
	for(int i=0;i<ix.size();i++) a=max(a,hypot(cx-ix[i],cy-iy[i]));
	for(int i=0;i<nx.size();i++) b=min(b,hypot(cx-nx[i],cy-ny[i]));
	return a<=b;
}
int main() {
    int n;
	cin>>n;
	for(int i=0;i<n;i++) {
		double x,y;
        char p;
		cin>>x>>y>>p;
		if(p=='I') ix.push_back(x),iy.push_back(y);
		else nx.push_back(x),ny.push_back(y);
	} if(ix.size()<2||nx.empty()) {cout<<"No";return 0;}
    for(int i=0;i<ix.size();i++) for(int j=i+1;j<ix.size();j++) {
        double x1=ix[i],y1=iy[i],x2=ix[j],y2=iy[j];
        double cx=(x1+x2)/2,cy=(y1+y2)/2;
        if(ok(cx,cy)) {cout<<"No";return 0;}
    } for(int i=0;i<ix.size();i++) for(int j=i+1;j<ix.size();j++) for(int k=0;k<nx.size();k++) {
		double x1=ix[i],y1=iy[i],x2=ix[j],y2=iy[j],x3=nx[k],y3=ny[k];
		double a1=2*(x2-x1),b1=2*(y2-y1),c1=x2*x2+y2*y2-x1*x1-y1*y1;
	    double a2=2*(x3-x1),b2=2*(y3-y1),c2=x3*x3+y3*y3-x1*x1-y1*y1;
	    double d=a1*b2-a2*b1;
	    double cx=(c1*b2-c2*b1)/d,cy=(a1*c2-a2*c1)/d,r=hypot(cx-x1,cy-y1);
        if(ok(cx,cy)) {cout<<"No";return 0;}
	} cout<<"Yes";
}

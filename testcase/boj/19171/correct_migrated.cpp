#include <bits/stdc++.h>
using namespace std;
double X,Y,Z,XX,YY,ZZ,XXX,YYY,ZZZ;
double sq(double a) {return a*a;}
double f(double x,double y,double z) {return sqrt(1e-9+sq(x-X)+sq(y-Y)+sq(z-Z))+sqrt(1e-9+sq(x-XX)+sq(y-YY)+sq(z-ZZ))+sqrt(1e-9+sq(x-XXX)+sq(y-YYY)+sq(z-ZZZ));}
tuple<double,double,double> grad(double x,double y,double z) {
    double p=sqrt(1e-9+sq(x-X)+sq(y-Y)+sq(z-Z)),q=sqrt(1e-9+sq(x-XX)+sq(y-YY)+sq(z-ZZ)),r=sqrt(1e-9+sq(x-XXX)+sq(y-YYY)+sq(z-ZZZ));
    return {(x-X)/p+(x-XX)/q+(x-XXX)/r,(y-Y)/p+(y-YY)/q+(y-YYY)/r,(z-Z)/p+(z-ZZ)/q+(z-ZZZ)/r};
}
double descent(tuple<double,double,double> p) {
    double x=get<0>(p),y=get<1>(p),z=get<2>(p),w=1e6;
    for(int i=0;i<30000;i++) {
        auto [dx,dy,dz]=grad(x,y,z);
        x-=w*dx;
        y-=w*dy;
        z-=w*dz;
        w*=0.999;
    } return f(x,y,z);
}
int main() {
    cin>>X>>Y>>Z>>XX>>YY>>ZZ>>XXX>>YYY>>ZZZ;
    double a=(X+XX+XXX)/3,b=(Y+YY+YYY)/3,c=(Z+ZZ+ZZZ)/3;
    cout<<fixed<<setprecision(9)<<descent({a,b,c});
}

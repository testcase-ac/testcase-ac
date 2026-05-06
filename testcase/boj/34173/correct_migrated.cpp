#include <bits/stdc++.h>
using namespace std;
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int t;
    long double xa,ya,xc,yc,x,y,d,v,c;
    cin>>t;
    while(t--) {
        cin>>xa>>ya>>xc>>yc>>v;
        if(v==1) {cout<<"-1\n";continue;}
        x=hypot(xa-xc,ya-yc),y=x/sqrt(v*v-1),c=v*v*x/(v*v-1),d=x;
	    cout<<fixed<<setprecision(12)<<(d*d*(expl(acosl(-1)/sqrtl(v*v-1))-1)/(sqrtl(v*v-1)*4))*2+atanl(abs(y/(x-c)))*v*v*x*x/((v*v-1)*(v*v-1))-abs(x-c)*y<<'\n';
    }
}

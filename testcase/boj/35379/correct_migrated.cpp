#include <bits/stdc++.h>
using namespace std;
int main() {
    long p,q;
    cin>>p>>q;
    for(long r=1;r<=1000000;r++) {
        long a=p,b=2*p*r-p-2*r*q,c=p*(r*r-r);
        long D=b*b-4*a*c;
        if(D<0) continue;
        long t=sqrt(D);
        if(t*t!=D) continue;
        if(-b+t<0||(-b+t)%(a*2)) continue;
        long g=(-b+t)/(a*2);
        if(g<r) continue;
        cout<<r<<' '<<g;
        return 0;
    } cout<<"impossible";
}

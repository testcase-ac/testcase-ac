#include <bits/stdc++.h>
using namespace std;
int main() {
    double n,l,w,h,lo=1e-9,hi=1e9;
    cin>>n>>l>>w>>h;
    for(int i=0;i<100;i++) {
        double m=(lo+hi)/2;
        long long x=l/m,y=w/m,z=h/m;
        if(x*y*z<n) hi=m;
        else lo=m;
    } cout<<fixed<<setprecision(11)<<lo;
}

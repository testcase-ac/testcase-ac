#include <bits/stdc++.h>
using namespace std;
int sq(int n) {return n*n;}
int main() {
    int n;
    cin>>n;
    double a=0,s=0,s1=0,s2=0,x[n],y[n];
    for(int i=0;i<n;i++) cin>>x[i]>>y[i];
    for(int i=0;i<n;i++) {
        a+=x[i]*y[(i+1)%n]-x[(i+1)%n]*y[i];
        s+=(y[(i+1)%n]-y[i])*((x[i]*sq(x[i])+sq(x[i])*x[(i+1)%n]+x[i]*sq(x[(i+1)%n])+x[(i+1)%n]*sq(x[(i+1)%n])))-(x[(i+1)%n]-x[i])*((y[i]*sq(y[i])+sq(y[i])*y[(i+1)%n]+y[i]*sq(y[(i+1)%n])+y[(i+1)%n]*sq(y[(i+1)%n])));
        s1+=(y[(i+1)%n]-y[i])*(sq(x[i])+x[i]*x[(i+1)%n]+sq(x[(i+1)%n]));
        s2+=(x[(i+1)%n]-x[i])*(sq(y[i])+y[i]*y[(i+1)%n]+sq(y[(i+1)%n]));
    } cout<<fixed<<setprecision(9)<<(s*a/3-(s1*s1*2)/9-(s2*s2*2)/9)/(a*a);
}

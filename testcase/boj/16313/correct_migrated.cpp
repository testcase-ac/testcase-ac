#include <bits/stdc++.h>
using namespace std;
int main() {
    double a,b,c,d,s;
    cin>>a>>b>>c>>d;
    s=(a+b+c+d)/2;
    cout<<fixed<<setprecision(9)<<sqrt((s-a)*(s-b)*(s-c)*(s-d));
}

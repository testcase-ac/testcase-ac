#include <bits/stdc++.h>
using namespace std;
int main() {
    int t;
    long double x1,y1,x2,y2,x3,y3,x4,t1,t2;
    cin>>t;
    while(t--) {
        cin>>x1>>y1>>x2>>y2;
        if(x1>x2) swap(x1,x2);
        if(y1>y2) swap(y1,y2);
        if(x1==x2) {
            cout<<fixed<<setprecision(10)<<log(y2)-log(y1)<<'\n';
            continue;
        } x3=(x1+x2)/2;y3=(y1+y2)/2;x4=y3*(y2-y1)/(x2-x1)+x3;
        t1=atan(y1/(x4-x1));t2=atan(y2/(x4-x2));
        if(t2<0) t2+=acos(-1);
        cout<<fixed<<setprecision(10)<<log(abs(1/sin(t2)-1/tan(t2)))-log(abs(1/sin(t1)-1/tan(t1)))<<'\n';
    }
}

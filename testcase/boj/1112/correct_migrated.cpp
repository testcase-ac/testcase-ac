#include <bits/stdc++.h>
using namespace std;
string f(int n,int b) {
    if(!n) return "0";
    string s="";
    bool f=0;
    if(n<0&&b>0) f=1;
    if(b>0) n=abs(n);
    while(n) {
        int r=(n%b+abs(b))%abs(b);
        s+=char('0'+r);
        n=(n-r)/b;
    } if(f) s+='-';
    reverse(s.begin(),s.end());
    return s;
}
int main() {
    int n,b;
    cin>>n>>b;
    cout<<f(n,b);
}

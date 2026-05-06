#include <iostream>
using namespace std;
#define ui unsigned int
#define ull unsigned long long
int list[3] = {2, 7, 61};
ull p(ull a,ull b, ui m) {
    ull r=1;
    while(b) {
        if(b&1) {
            r=(r*a)%m;
        } b>>=1;
        a=(a*a)%m;
    } return r;
}
int mr(ull a,int b) {
    if(b%a==0) return 1;
    ui c=a-1;
    while(c%2==0) {
        if(p(b,c,a)==a-1) {
            return 1;
        } c/=2;
    } ui d=p(b,c,a);
    return d==1 || d==a-1;
}
int prime(ull n) {
    for(int i=0;i<3;i++) {
        if (!mr(n,list[i])) {
            return 0;
        }
    } return 1;
}

int main(){
    int n,m=0;
    ull a;
    cin>>n;
    for(int i=0;i<n;i++) {
        cin>>a;
        m+=prime(2*a+1);
    } cout<<m;
}

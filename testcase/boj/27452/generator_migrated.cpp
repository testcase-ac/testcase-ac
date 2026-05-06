#include "testlib.h"
using namespace std;
long long len[101];
int main(int argc,char*argv[]) {
    len[1]=len[2]=2;
    for(int i=3;i<85;i++) len[i]=len[i-1]+len[i-2]+2;
    for(int i=85;i<101;i++) len[i]=1e18;
    registerGen(argc,argv,1);
    int t=rnd.next(1,20);
    cout<<t<<'\n';
    while(t--) {
        int x=100;
        if(rnd.next(0,1)) cout<<rnd.next(1LL,(long long)1e18);
        else {x=rnd.next(1,100);cout<<x;}
        x=min(100,x+2);
        cout<<' '<<rnd.next(1LL,len[x])<<'\n';
    }
}

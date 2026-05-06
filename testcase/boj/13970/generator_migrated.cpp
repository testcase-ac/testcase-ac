#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int t=rnd.next(1,10);
    cout<<t<<' '<<rnd.next(2,1000000)<<'\n';
    for(int i=0;i<t;i++) {
        int n=rnd.next(1,100/t);
        cout<<n;
        while(n--) cout<<' '<<rnd.next(1,1000000);
        cout<<'\n';
    }
}

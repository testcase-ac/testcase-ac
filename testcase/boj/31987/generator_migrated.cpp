#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int q=rnd.next(1,30);
    cout<<q<<'\n';
    int mx=(1<<31)-1,sq=sqrt(mx);
    while(q--) {
        int i,j,k;
        if(rnd.next(0,1)) {
            j=rnd.next(1,sq);
            k=rnd.next(1,mx/j);
        } else {
            k=rnd.next(1,sq);
            j=rnd.next(1,mx/k);
        } i=rnd.next(1,j);
        cout<<i<<' '<<j<<' '<<k<<'\n';
    }
}

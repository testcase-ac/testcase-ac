#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int l=-1e8,r=1e8,x1,y1;
    for(int i=0;i<3;i++) cout<<rnd.next(l,r)<<' ';
    x1=rnd.next(l,r);y1=rnd.next(l,r);
    cout<<x1<<' '<<rnd.next(x1,r)<<' '<<y1<<' '<<rnd.next(y1,r);
}

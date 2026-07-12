#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int n=rnd.next(4,17),m=rnd.next(4,17);
    cout<<n<<' '<<m<<'\n';
    for(int i=0;i<n;i++) {
        for(int j=0;j<m;j++) {
            if(j) cout<<' ';
            cout<<rnd.next(1,99);
        }
        cout<<'\n';
    }
}

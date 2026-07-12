#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int mx=998244352;
    if(rnd.next(0,1)) {
        int n=rnd.next(1,9),q=rnd.next(1,19);
        cout<<n<<' '<<q<<'\n';
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) cout<<rnd.next(0,mx)<<(j+1==n?'\n':' ');
        }
        for(int i=0;i<q;i++) cout<<rnd.next(0,mx)<<(i+1==q?'\n':' ');
    } else {
        mx=9;
        int n=rnd.next(1,21),q=rnd.next(1,50);
        cout<<n<<' '<<q<<'\n';
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) cout<<rnd.next(0,mx)<<(j+1==n?'\n':' ');
        }
        for(int i=0;i<q;i++) cout<<rnd.next(0,mx)<<(i+1==q?'\n':' ');
    }
}

#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int mn=-1e9,mx=1e9;
    for(int i=0;i<3;i++) {
        for(int j=0;j<3;j++) cout<<rnd.next(mn,mx)<<(j==2?'\n':' ');
    }
}

#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int n=rnd.next(1,79);
    vector<int> p=rnd.perm(n,1);
    cout<<n<<'\n';
    for(int i:p) cout<<i<<'\n';
}

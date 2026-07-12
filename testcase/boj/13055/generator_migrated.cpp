#include "testlib.h"
using namespace std;
int main(int argc,char*argv[]) {
    registerGen(argc,argv,1);
    int n=rnd.next(1,80); //testcase.ac 출력이 80줄에서 끊김
    while(n--) cout<<(rnd.next(0,1)?'A':'B');
    cout<<'\n';
}

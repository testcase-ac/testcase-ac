#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;
int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int N=inf.readInt();
    int N1=ouf.readInt(-1,N);
    int N2=ans.readInt(-1,N);
    if(N1==-1&&N2==-1) quitf(_ok,"output is right");
    if(N1==-1||N2==-1) quitf(_wa,"reversed correctness");
    N1*=N1;
    int n=ouf.readInt(1,N);
    N1+=n*n;
    n=ouf.readInt(1,N);
    N1+=n*n;
    if(N==N1) quitf(_ok, "output is right");
    else quitf(_wa, "number isn't prime or sum of values is not N");
}

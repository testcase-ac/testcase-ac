//GPT 코드
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char*argv[]) {
    registerTestlibCmd(argc,argv);

    int n=inf.readInt(5,1000);
    vector<int>a(n);
    for(int i=0;i<n;i++)
        a[i]=inf.readInt(1,n);

    for(int k=0;k<3;k++) {
        int l=ouf.readInt(1,n);
        int r=ouf.readInt(1,n);
        if(l>r)
            quitf(_wa,"l>r");
        reverse(a.begin()+l-1,a.begin()+r);
    }

    for(int i=0;i<n;i++) {
        if(a[i]!=i+1)
            quitf(_wa,"not restored");
    }

    ouf.readEof();
    quitf(_ok,"ok");
}

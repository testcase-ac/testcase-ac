//GPT 코드
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char* argv[]){
    registerTestlibCmd(argc,argv);

    int n=inf.readInt(1,10000000);

    int m=ouf.readInt();
    if(m<0) quitf(_wa,"m is negative");

    vector<int> s(m);
    for(int i=0;i<m;i++)
        s[i]=ouf.readInt();

    int need=(int)floor(sqrt(0.5*n));
    if(m<need)
        quitf(_wa,"|S| is too small: %d < %d",m,need);

    vector<char> used(n+1,0);
    for(int i=0;i<m;i++){
        if(s[i]<1||s[i]>n)
            quitf(_wa,"element out of range");
        if(used[s[i]])
            quitf(_wa,"duplicate element");
        used[s[i]]=1;
    }

    unordered_set<int> st;
    st.reserve((size_t)m*(m-1)/2);
    for(int i=0;i<m;i++){
        for(int j=i+1;j<m;j++){
            int x=s[i]^s[j];
            if(st.count(x))
                quitf(_wa,"duplicate xor value");
            st.insert(x);
        }
    }

    quitf(_ok,"valid subset, size=%d",m);
}

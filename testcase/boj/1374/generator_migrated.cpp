//GPT코드
#include <bits/stdc++.h>
using namespace std;
int main() {
    random_device rd;
    mt19937 g(rd());

    int t=uniform_int_distribution<int>(0,1)(g);

    int n;
    if(t==0) n=uniform_int_distribution<int>(1,80)(g);
    else n=uniform_int_distribution<int>(1,30)(g);

    cout<<n<<'\n';

    vector<int> p(n);
    for(int i=0;i<n;i++) p[i]=i+1;
    shuffle(p.begin(),p.end(),g);

    for(int i=0;i<n;i++) {
        int s,e;
        if(t==0) {
            s=uniform_int_distribution<int>(0,99)(g);
            e=uniform_int_distribution<int>(s+1,100)(g);
        } else {
            s=uniform_int_distribution<int>(0,999999999)(g);
            e=uniform_int_distribution<int>(s+1,1000000000)(g);
        }
        cout<<p[i]<<' '<<s<<' '<<e<<'\n';
    }
}

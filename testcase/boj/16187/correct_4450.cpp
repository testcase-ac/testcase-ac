#include <bits/stdc++.h>
using namespace std;
int g[5001];
int main() {
    g[0] = g[1] = 0;
    g[2] = 1;
    for(int i=3;i<=5000;++i){
        set<int> S;
        for(int j=0;2*j+2<=i;++j){
            int a=g[j]^g[i-j-2];
            S.insert(a);
        }
        int num=0;
        while(1){
            if(S.find(num)==S.end()){
                break;
            }
            num++;
        }
        g[i]=num;
    }
    int T;
    cin >> T;
    while(T--) {
        int t;
        cin >> t;
        if(g[t]!=0)
            cout << "First" << "\n";
        else
            cout << "Second" << "\n";
    }
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
string S;
int D[10000000];
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin>>S;
    int x=0;
    int t=-1;
    int ans=0;
    for(int i=0;i<S.size();++i ){
        if(S[i]=='('){
            t++;
            D[i]=t;
        }else{
            t--;
            D[i]=t;
        }
        if(i!=0){
            if(S[i-1]=='('&&S[i]==')'){
                ans+=D[i-1];
            }
        }
        
    }  
    cout<<ans;
}

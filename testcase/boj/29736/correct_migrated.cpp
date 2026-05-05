#include<bits/stdc++.h>
using namespace std;
int main(){
    int A,B,K,X,p=0;
    cin>>A>>B>>K>>X;
    for(int i=A;i<=B;i++){
        if(abs(K-i)<=X)p++;
    }
    if(p)cout<<p;
    else cout<<"IMPOSSIBLE";
    return 0;
}

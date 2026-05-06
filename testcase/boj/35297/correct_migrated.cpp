#include <bits/stdc++.h>
using namespace std;
int main() {
    string s,a="KSA";
    cin>>s;
    int k=0,l=s.length(),p=(l-1)%3,t=(l-1)%2;
    for(int i=l-1;i>=0;i--) {
        if(s[i]==a[p]&&i%2==t) {
            k++;
            p=(p+2)%3;
            t=1-i%2;
        }
    } cout<<(l-k)*2;
}

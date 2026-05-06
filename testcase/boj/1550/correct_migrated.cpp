#include <iostream>
using namespace std;

int main() {
    int n=0,t=1;
    string s;
    cin>>s;
    for(int i=0;i<s.length();i++) {
        if(s[s.length()-i-1]<='9') n+=(s[s.length()-i-1]-'0')*t;
        else n+=(s[s.length()-i-1]-'A'+10)*t;
        t*=16;
    } cout<<n;
}

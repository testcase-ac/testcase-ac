#include <bits/stdc++.h>
using namespace std;
int main() {
    string s;
    cin>>s;
    int n=s.length();
    while(n>2) {
        string a="";
        int t=n;
        for(int i=0;i<t;i++) {
            if(i%3!=2) a+=s[i];
            else n--;
        } s.swap(a);
        reverse(s.begin(),s.end());
    } sort(s.begin(),s.end());
    cout<<s;
}

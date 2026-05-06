#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<string> v;
void asdf(int a,int b,string s) {
    if(b==m) {
        v.push_back(s);
        return;
    } else for(int i=a+1;i<n;i++) asdf(i,b+1,s+to_string(i));
}
int main() {
    cin>>n>>m;
    int a[n];
    for(int i=0;i<n;i++) cin>>a[i];
    sort(a,a+n);
    asdf(-1,0,"");
    sort(v.begin(),v.end());
    for(string s:v) {
        for(int i=0;i<m;i++) cout<<a[s[i]-'0']<<' ';
        cout<<'\n';
    }
}

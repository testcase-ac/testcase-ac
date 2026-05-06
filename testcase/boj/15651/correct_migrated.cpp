#include <bits/stdc++.h>
using namespace std;
int n,m;
vector<string> v;
void asdf(int a,int b,string s) {
    if(b==m) {
        v.push_back(s);
        return;
    } else for(int i=1;i<=n;i++) asdf(i,b+1,s+to_string(i));
}
int main() {
    cin>>n>>m;
    asdf(-1,0,"");
    sort(v.begin(),v.end());
    for(string s:v) {
        for(int i=0;i<m;i++) cout<<s[i]<<' ';
        cout<<'\n';
    }
}

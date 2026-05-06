#include <bits/stdc++.h>
using namespace std;
vector<int> v;
bool f(vector<int> id,int s,int k) {
    if(k==0) {
        if(s==0) {
            cout<<"YES\n";
            for(int i:id) cout<<v[i]<<' ';
            return 1;
        } return 0;
    } int x=0;
    if(!id.empty()) x=id.back()+1;
    for(int i=x;i<v.size();i++) {
        if(s-v[i]>=0&&s>=v[i]*k) {
            id.push_back(i);
            if(f(id,s-v[i],k-1)) return 1;
            id.pop_back();
        } else break;
    } return 0;
}
int main() {
    int n,k;
    cin>>n>>k;
    for(int i=1;i*i<n;i++) v.push_back(n-i*i);
    reverse(v.begin(),v.end());
    vector<int> id;
    if(!f(id,n,k)) cout<<"NO";
}

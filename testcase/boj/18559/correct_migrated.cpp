#include <bits/stdc++.h>
using namespace std;
int mu[100001];
vector<int> cyclo(int n) {
    vector<int> r={1};
    for(int d=1;d<=n;d++) {
        if(n%d||mu[n/d]!=1) continue;
        vector<int> t=r;
        r.insert(r.begin(),d,0);
        for(int i=0;i<t.size();i++) r[i]-=t[i];
    } for(int d=1;d<=n;d++) {
        if(n%d||mu[n/d]!=-1) continue;
        vector<int> t(r.size());
        for(int i=r.size()-1;i>=d;i--) {
            t[i-d]+=r[i];
            r[i-d]+=r[i];
        } while(!t.empty()&&!t.back()) t.pop_back();
        r=t;
    } return r;
}
bool cmp(vector<int> a,vector<int> b) {
    if(a.size()!=b.size()) return a.size()<b.size();
    for(int i=a.size()-1;;i--) {
        if(a[i]!=b[i]) return a[i]<b[i];
    }
}
int main() {
    mu[1]=1;
    for(int i=1;i<100001;i++) for(int j=i*2;j<100001;j+=i) mu[j]-=mu[i];
    int t,n;
    cin>>t;
    while(t--) {
        cin>>n;
        vector<vector<int>> v;
        for(int d=1;d<=n;d++) if(n%d==0) v.push_back(cyclo(d));
        sort(v.begin(),v.end(),cmp);
        for(auto c:v) {
            cout<<'(';
            for(int i=c.size()-1;i>1;i--) {
                if(!c[i]) continue;
                if(c[i]>0&&i!=c.size()-1) cout<<'+';
                if(c[i]==-1) cout<<'-';
                else if(c[i]!=1) cout<<c[i];
                cout<<"x^"<<i;
            } if(c[1]) {
                if(c[1]>=0&&c.size()!=2) cout<<'+';
                if(c[1]==-1) cout<<'-';
                else if(c[1]!=1) cout<<c[1];
                cout<<'x';
            } if(c[0]) {
                if(c[0]>=0) cout<<'+';
                cout<<c[0];
            } cout<<')';
        } cout<<'\n';
    }
}

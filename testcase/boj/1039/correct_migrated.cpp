#include <bits/stdc++.h>
using namespace std;
int main() {
    set<pair<int,int>> st;
    string s;
    int k;
    cin>>s>>k;
    int n=s.length();
    queue<pair<int,int>> q;
    q.push({stoi(s),0});
    int m=-1;
    while(!q.empty()) {
        auto [z,x]=q.front();
        string t=to_string(z);
        q.pop();
        if(x==k) {
            m=max(m,stoi(t));
            continue;
        } for(int i=0;i<n;i++) for(int j=i+1;j<n;j++) {
            string a=t;
            swap(a[i],a[j]);
            if(a[0]!='0') {
                pair<int,int> r={stoi(a),x+1};
                if(st.find(r)==st.end()) {
                    st.insert(r);
                    q.push(r);
                }
            }
        }
    } cout<<m;
}

#include <bits/stdc++.h>
using namespace std;
int main() {
    int n,m;
    cin>>n>>m;
    string s[n];
    for(int i=0;i<n;i++) cin>>s[i];
    vector<int> x,y;
    if(n==1) {
        for(int i=0;i<m;i++) {
            if(s[0][i]=='X') {
                if(i==m-1) x.push_back(i+1);
                else {
                    if(s[0][i+1]=='X') {
                        y.push_back(i+1);
                        y.push_back(i+2);
                        i++;
                    } else x.push_back(i+1);
                }
            }
        } cout<<x.size()+y.size()/2<<'\n';
        for(int i:x) cout<<"1 "<<i<<'\n';
        for(int i=0;i<y.size();i+=2) cout<<"2 "<<y[i]<<' '<<y[i+1]<<'\n';
        return 0;
    } for(int j=0;j<m;j++) {
        for(int i=0;i<n;i++) {
            if(s[i][j]=='X') {
                if(i==n-1) x.push_back(i+j*n+1);
                else {
                    if(s[i+1][j]=='X') {
                        y.push_back(i+j*n+1);
                        y.push_back(i+j*n+2);
                        i++;
                    } else x.push_back(i+j*n+1);
                }
            }
        }
    } cout<<x.size()+y.size()/2<<'\n';
    for(int i:x) cout<<"1 "<<i<<'\n';
    for(int i=0;i<y.size();i+=2) cout<<"2 "<<y[i]<<' '<<y[i+1]<<'\n';
}

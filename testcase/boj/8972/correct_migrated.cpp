#include <bits/stdc++.h>
using namespace std;

int dx[]={0,1,1,1,0,0,0,-1,-1,-1};
int dy[]={0,-1,0,1,-1,0,1,-1,0,1};
int main(){
    ios::sync_with_stdio(0);cin.tie(0);
    int R,C,Ix,Iy;cin>>R>>C;
    vector<string> a(R),b(R);
    for(int i=0;i<R;i++){
        cin>>a[i];
        for(int j=0;j<C;j++)
            if(a[i][j]=='I') Ix=i,Iy=j;
    }
    string s;cin>>s;
    for(int k=0;k<s.size();k++){
        Ix+=dx[s[k]-'0']; Iy+=dy[s[k]-'0'];
        if(a[Ix][Iy]=='R') return cout<<"kraj "<<k+1,0;

        vector<vector<int>> cnt(R,vector<int>(C));
        b.assign(R,string(C,'.'));
        b[Ix][Iy]='I';

        for(int i=0;i<R;i++)for(int j=0;j<C;j++)
            if(a[i][j]=='R'){
                int ni=i+(Ix>i)-(Ix<i);
                int nj=j+(Iy>j)-(Iy<j);
                cnt[ni][nj]++;
            }

        if(cnt[Ix][Iy]) return cout<<"kraj "<<k+1,0;

        for(int i=0;i<R;i++)for(int j=0;j<C;j++)
            if(cnt[i][j]==1) b[i][j]='R';

        a=b;
    }
    for(auto &r:a) cout<<r<<"\n";
}

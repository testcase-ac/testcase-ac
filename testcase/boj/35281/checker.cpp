//GPT 코드
#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc,char*argv[]){
    registerTestlibCmd(argc,argv);

    int n=inf.readInt();
    int m=inf.readInt();

    long long correct=ans.readLong();   // 정답 파일의 최소 개수
    long long out=ouf.readLong();       // 참가자 출력

    if(correct==-1){
        if(out!=-1)quitf(_wa,"answer should be -1");
        quitf(_ok,"correct");
    }

    if(out==-1)quitf(_wa,"solution exists");

    if(out!=correct)quitf(_wa,"not minimum");

    vector<string> g(n);
    for(int i=0;i<n;i++){
        g[i]=ouf.readToken();
        if((int)g[i].size()!=m)
            quitf(_wa,"wrong width");
    }

    vector<vector<int>> vis(n,vector<int>(m,0));
    long long cnt=0;

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(g[i][j]=='G'){
                cnt++;
                bool ok=false;

                if(j+1<m&&g[i][j+1]=='g'&&!vis[i][j]&&!vis[i][j+1]){
                    vis[i][j]=vis[i][j+1]=1;
                    ok=true;
                }
                if(i+1<n&&g[i+1][j]=='g'&&!vis[i][j]&&!vis[i+1][j]){
                    vis[i][j]=vis[i+1][j]=1;
                    ok=true;
                }

                if(!ok)quitf(_wa,"invalid domino");
            }
        }
    }

    for(int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            if(g[i][j]=='g'&&!vis[i][j])
                quitf(_wa,"body without head");
            if(g[i][j]!='.'&&g[i][j]!='G'&&g[i][j]!='g')
                quitf(_wa,"invalid character");
        }
    }

    if(cnt!=out)
        quitf(_wa,"count mismatch");

    for(int i=0;i<n;i++){
        int c=0;
        for(int j=0;j<m;j++)
            if(g[i][j]=='G')c++;
        if(c%2==0)
            quitf(_wa,"row parity");
    }

    for(int j=0;j<m;j++){
        int c=0;
        for(int i=0;i<n;i++)
            if(g[i][j]=='G')c++;
        if(c%2==0)
            quitf(_wa,"column parity");
    }

    quitf(_ok,"correct");
}

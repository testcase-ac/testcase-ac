#include <bits/stdc++.h>
using namespace std;

bool knight(int x1,int y1,int x2,int y2){
    int dx=abs(x1-x2);
    int dy=abs(y1-y2);
    return (dx==1&&dy==2)||(dx==2&&dy==1);
}

int main(int argc,char* argv[]){
    ifstream in(argv[1]);
    ifstream ans(argv[2]);   // unused
    ifstream user(argv[3]);

    int N,sx,sy;
    in>>N>>sx>>sy;

    vector<pair<int,int>> path;
    int x,y;

    while(user>>x>>y) path.push_back({x,y});

    if(path.size()==1 && path[0]==make_pair(-1,-1)){
        cout<<"Wrong Answer";
        return 1;
    }

    if((int)path.size()!=N*N){
        cout<<"Wrong Answer";
        return 1;
    }

    if(path[0]!=make_pair(sx,sy)){
        cout<<"Wrong Answer";
        return 1;
    }

    vector<vector<int>> vis(N+1,vector<int>(N+1,0));

    for(int i=0;i<N*N;i++){
        auto [cx,cy]=path[i];

        if(cx<1||cx>N||cy<1||cy>N){
            cout<<"Wrong Answer";
            return 1;
        }

        if(vis[cx][cy]){
            cout<<"Wrong Answer";
            return 1;
        }
        vis[cx][cy]=1;

        if(i){
            auto [px,py]=path[i-1];
            if(!knight(px,py,cx,cy)){
                cout<<"Wrong Answer";
                return 1;
            }
        }
    }

    cout<<"Accepted";
    return 0;
}

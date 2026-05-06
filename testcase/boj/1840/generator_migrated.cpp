/*/
백준 테스트 데이터에는 중복 좌표가 나오는 경우가 존재하지만,
testcase.ac 밸리데이터에서 중복을 거부해서 올바른 제너레이터를 만들 수 없는 상태입니다.
현재는 중복된 좌표가 나오지 않는 코드로 넣어놨습니다.
/*/
//GPT 코드
#include <bits/stdc++.h>
using namespace std;

int main() {
    random_device rd;
    mt19937 g(rd());

    int base[9][9]={
        {1,2,3,4,5,6,7,8,9},
        {4,5,6,7,8,9,1,2,3},
        {7,8,9,1,2,3,4,5,6},
        {2,3,4,5,6,7,8,9,1},
        {5,6,7,8,9,1,2,3,4},
        {8,9,1,2,3,4,5,6,7},
        {3,4,5,6,7,8,9,1,2},
        {6,7,8,9,1,2,3,4,5},
        {9,1,2,3,4,5,6,7,8}
    };

    vector<pair<int,int>> pos;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            pos.push_back({i,j});

    shuffle(pos.begin(),pos.end(),g);

    uniform_int_distribution<int> tdist(0,2);
    int type=tdist(g);

    if(type==0) {
        for(int i=0;i<81;i++) {
            int r=pos[i].first;
            int c=pos[i].second;
            cout<<r<<" "<<c<<" "<<base[r-1][c-1]<<"\n";
        }
    }
    else if(type==1) {
        // pos[0], pos[1] 사용 (중복 없음 보장)
        int r1=pos[0].first;
        int c1=pos[0].second;
        int v=base[r1-1][c1-1];

        cout<<r1<<" "<<c1<<" "<<v<<"\n";

        int r2=pos[1].first;
        int c2=pos[1].second;

        cout<<r2<<" "<<c2<<" "<<v<<"\n";

        for(int i=2;i<81;i++) {
            int r=pos[i].first;
            int c=pos[i].second;
            cout<<r<<" "<<c<<" "<<base[r-1][c-1]<<"\n";
        }
    }
    else {
        int bad=uniform_int_distribution<int>(10,40)(g);

        for(int i=0;i<81;i++) {
            int r=pos[i].first;
            int c=pos[i].second;
            int v=base[r-1][c-1];

            if(i==bad)
                v=v%9+1;

            cout<<r<<" "<<c<<" "<<v<<"\n";
        }
    }
}

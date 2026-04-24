#include <bits/stdc++.h>
int dr[] = {-1,1,0,0,-1,-1,1,1}, dc[] = {0,0,1,-1,-1,1,-1,1};
using namespace std;
bool ok(int r, int c) {
    return 0 <= r && r < 3 && 0 <= c && c < 3;
}
int main() {
    vector<string> arr(3);
    for(auto &s: arr) 
        cin >> s;
    string ans = "CCC";
    for(int r=0; r<3; r++) {
        for(int c=0; c<3; c++) {
            for(int t1=0; t1<8; t1++) {
                int r1 = r+dr[t1], c1 = c+dc[t1];
                if(!ok(r1, c1)) continue;
                for(int t2=0; t2<8; t2++) {
                    int r2 = r1+dr[t2], c2 = c1+dc[t2];
                    if(!ok(r2, c2) || (r == r2 && c == c2)) continue;
                    string cur;
                    cur.push_back(arr[r][c]);
                    cur.push_back(arr[r1][c1]);
                    cur.push_back(arr[r2][c2]);
                    ans = min(ans, cur);
                }
            }
        }
    }
    cout << ans;
}

#include <bits/stdc++.h>
using namespace std;
#define int long long
bool arr[20][20], seen[20][20][20][20][4];
int N;
int dr[] = {1, 0, -1, 0}, dc[] = {0, 1, 0, -1};
pair<int, int> mv(int r, int c, int dir) {
    int tr = r + dr[dir], tc = c + dc[dir];
    if(tr < 0 || tr >= N || tc < 0 || tc >= N || arr[tr][tc])
        return {r, c};
    return {tr, tc};
}
struct status {
    int r1, c1, r2, c2, dir;
    status left() {
        return {r1, c1, r2, c2, (dir + 3) % 4};
    }
    status right() {
        return {r1, c1, r2, c2, (dir + 1) % 4};
    }
    status front() {
        status s;
        if(r1 == N - 1 && c1 == N - 1) {
            s.r1 = r1;
            s.c1 = c1;
        } else {
            tie(s.r1, s.c1) = mv(r1, c1, dir);
        }
        if(r2 == N - 1 && c2 == N - 1) {
            s.r2 = r2;
            s.c2 = c2;
        } else {
            tie(s.r2, s.c2) = mv(r2, c2, (dir + 1) % 4);
        }
        s.dir = dir;
        return s;
    }
};
queue<status> q;

void visit(status s) {
    auto &v = seen[s.r1][s.c1][s.r2][s.c2][s.dir];
    if(v || arr[s.r1][s.c1] || arr[s.r2][s.c2])
        return;
    v = true;
    q.push(s);
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N;
    for(int i = N - 1; i >= 0; i--) {
        string s;
        cin >> s;
        for(int j = 0; j < N; j++) {
            arr[i][j] = s[j] == 'H';
        }
    }
    seen[0][0][0][0][0] = 0;
    q.push({0, 0, 0, 0, 0});
    int ans = 0;
    while(1) {
        ans++;
        int sz = q.size();
        while(sz--) {
            auto elem = q.front();
            q.pop();
            visit(elem.left());
            visit(elem.right());
            visit(elem.front());
        }

        for(int d = 0; d < 4; d++) {
            if(seen[N - 1][N - 1][N - 1][N - 1][d]) {
                return !(cout << ans);
            }
        }
    }
}

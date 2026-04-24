#include <bits/stdc++.h>
using namespace std;
#define int long long
struct pos {
    int r, c;
    bool in_same_group(pos p) {
        return p.r % 2 == r % 2 && p.c %2 == c % 2;
    }
};
int arr[1001][1001], ans[1001][1001], N, Q;
pos cur[5], orig[5];
pos get_original(pos p) {
    for(int i=1; i<=4; i++) {
        if(!cur[i].in_same_group(p)) {
            continue;
        }
        int dr = (p.r + N - cur[i].r) % N;
        int dc = (p.c + N - cur[i].c) % N;
        int real_r = (orig[i].r + dr - 1) % N + 1;
        int real_c = (orig[i].c + dc - 1) % N + 1;
        return pos{real_r, real_c};
    }
    assert(false);
}
int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    cin >> N >> Q;
    for(int i=1; i<=N; i++) {
        for(int j=1; j<=N; j++) {
            arr[i][j] = (i-1)*N+j;
        }
    }
    
    orig[1] = cur[1] = {1,1};
    orig[2] = cur[2] = {1,2};
    orig[3] = cur[3] = {2,1};
    orig[4] = cur[4] = {2,2};
    auto incr = [&](int &t) {
        t++;
        if(t == N + 1) {
            t = 1;
        }
    };
    for(int q=0; q<Q; q++) {
        string s;
        cin >> s;
        if(s == "RO") {
            for(int i=1; i<=4; i++) {
                if(cur[i].r % 2 == 1) {
                    incr(cur[i].c);
                }
            }
        } else if(s == "RE") {
            for(int i=1; i<=4; i++) {
                if(cur[i].r % 2 == 0) {
                    incr(cur[i].c);
                }
            }
        } else if(s == "CO") {
            for(int i=1; i<=4; i++) {
                if(cur[i].c % 2 == 1) {
                    incr(cur[i].r);
                }
            }
        } else if(s == "CE") {
            for(int i=1; i<=4; i++) {
                if(cur[i].c % 2 == 0) {
                    incr(cur[i].r);
                }
            }
        } else {
            pos s1, s2;
            cin >> s1.r >> s1.c >> s2.r >> s2.c;
            pos o1 = get_original(s1), o2 = get_original(s2);
            swap(arr[o1.r][o1.c], arr[o2.r][o2.c]);
        }
    }
    for(int r=1; r<=N; r++) {
        for(int c=1; c<=N; c++) {
            auto p = get_original({r, c});
            cout << arr[p.r][p.c] << ' ';
        }
        cout << '\n';
    }
}

#include <bits/stdc++.h>
using namespace std;
const int MX = 52 * 100005;
int par_all[MX];
int par[52][100005];
bool chk[52][100005];
int to1d(int x, int y) {
    return y * 52 + x;
}
int f_all(int i) {
    return par_all[i] == i ? i : par_all[i] = f_all(par_all[i]);
}
int f(int x, int y) {
    return par[x][y] == y ? y : par[x][y] = f(x, par[x][y]);
}

// by y direction
void merge(int x, int y) {
    // printf("merge %d %d\n", x, y);
    int a = f(x, y), b = f(x, y+1);
    if(a != b) {
        par[x][a] = b;
    }

    int ta = f_all(to1d(x, y)), tb = f_all(to1d(x, y+1));
    if(ta != tb) {
        par_all[ta] = tb;
    }
}

// by x direction
void merge_x(int x, int y) {
    int ta = f_all(to1d(x, y)), tb = f_all(to1d(x+1, y));
    if(ta != tb) {
        par_all[ta] = tb;
    }
}

int32_t main() {
    cin.tie(0)->sync_with_stdio(0);
    for(int i=0; i<MX; i++) {
        par_all[i] = i;
    }
    for(int i=0; i<52; i++) {
        for(int j=0; j<100005; j++) {
            par[i][j] = j;
        }
    }
    int L;
    cin >> L;
    for(int i=0; i<L; i++) {
        int t, x1, y1, x2, y2;
        cin >> t >> x1 >> y1 >> x2 >> y2;
        
        if(t == 0) {
            if(x1 > x2)
                swap(x1, x2);
            if(y1 > y2)
                swap(y1, y2);
            for(int x=x1; x<=x2; x++) {
                int y = y1;
                while(y < y2) {
                    chk[x][y] = 1;
                    if(chk[x-1][y]) {
                        merge_x(x-1, y);
                    }
                    if(chk[x+1][y]) {
                        merge_x(x, y);
                    }
                    if(f(x, y) == y) {
                        merge(x, y);
                        y++;
                    } else {
                        y = f(x, y);
                    }
                }
                chk[x][y2] = 1;
                if(chk[x-1][y2]) {
                    merge_x(x-1, y2);
                }
                if(chk[x+1][y2]) {
                    merge_x(x, y2);
                }
                if(chk[x][y2+1]) {
                    merge(x, y2);
                }
                if(chk[x][y1-1]) {
                    merge(x, y1-1);
                }
            }
            chk[x1][y1] = chk[x1][y2] = chk[x2][y1] = chk[x2][y2] = 1;
        } else {
            int ta = f_all(to1d(x1, y1)), tb = f_all(to1d(x2, y2));
            cout << (ta == tb && chk[x1][y1]) << '\n';
        }
    }
}

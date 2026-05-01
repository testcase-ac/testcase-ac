#include <iostream>
#include <array>
#include <vector>

using namespace std;
using u64 = unsigned long long;

array<array<array<array<int, 22>, 22>, 22>, 22> dp;
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int hlim, wlim;
    cin >> hlim >> wlim;
    for (int y = 1; y <= hlim; y++) {
        cin >> ws;
        for (int x = 1; x <= wlim; x++) {
            dp[y][x][y][x] = (cin.get() == '.');
        }
    }

    u64 vis;
    for (int h = 1; h <= hlim; h++) {
        for (int w = 1 + (h == 1); w <= wlim; w++) {
            for (int y1 = 1; y1 <= hlim-h+1; y1++) {
                for (int x1 = 1; x1 <= wlim-w+1; x1++) {
                    int y2 = y1+h-1;
                    int x2 = x1+w-1;

                    for (int ys = y1; ys <= y2; ys++) {
                        for (int xs = x1; xs <= x2; xs++) {
                            if (!dp[ys][xs][ys][xs]) { continue; }
                            int tl = dp[y1][x1][ys-1][xs-1];
                            int tr = dp[y1][xs+1][ys-1][x2];
                            int bl = dp[ys+1][x1][y2][xs-1];
                            int br = dp[ys+1][xs+1][y2][x2];
                            vis |= 1ULL << (tl ^ tr ^ bl ^ br);
                        }
                    }

                    int mex = __builtin_ctzll(~vis);
                    dp[y1][x1][y2][x2] = mex;

                    vis = 0;
                }
            }
        }
    }

    cout << (dp[1][1][hlim][wlim] == 0 ? "Second" : "First") << "\n";

    return 0;
}

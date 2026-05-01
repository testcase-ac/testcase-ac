#include "testlib.h"
#include <vector>
#include <string>
#include <cstdio>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Dimensions: keep manageable for manual verification
    int H = rnd.next(3, 15);
    int W = rnd.next(3, 15);

    // Hyper-parameter for density: sparse, medium, or dense
    int densityCat = rnd.next(0, 2);
    double density;
    if (densityCat == 0) density = rnd.next(0.0, 0.2);
    else if (densityCat == 1) density = rnd.next(0.3, 0.7);
    else density = rnd.next(0.8, 1.0);

    // Hyper-parameter for digit skew: bias toward small or large strengths
    vector<int> skvec = {-2, -1, 0, 1, 2};
    int skew = rnd.any(skvec);

    // Initialize grid with all empty ('.')
    vector<string> g(H, string(W, '.'));

    // Fill interior cells
    for (int i = 1; i < H - 1; i++) {
        for (int j = 1; j < W - 1; j++) {
            if (rnd.next() < density) {
                int d;
                if (skew == 0) {
                    d = rnd.next(1, 9);
                } else {
                    // rnd.wnext(9, skew) -> [0,8], bias by skew
                    d = rnd.wnext(9, skew) + 1;
                }
                g[i][j] = char('0' + d);
            }
        }
    }

    // Ensure at least one sand cell exists
    bool hasSand = false;
    for (int i = 1; i < H - 1 && !hasSand; i++) {
        for (int j = 1; j < W - 1; j++) {
            if (g[i][j] != '.') {
                hasSand = true;
                break;
            }
        }
    }
    if (!hasSand) {
        int i = rnd.next(1, H - 2);
        int j = rnd.next(1, W - 2);
        g[i][j] = char('0' + rnd.next(1, 9));
    }

    // Output
    println(H, W);
    for (int i = 0; i < H; i++) {
        printf("%s\n", g[i].c_str());
    }

    return 0;
}

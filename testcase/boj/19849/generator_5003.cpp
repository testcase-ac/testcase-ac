#include "testlib.h"
#include <vector>
using namespace std;
int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Small sizes
    int N = rnd.next(1, 5);
    int Q = rnd.next(1, 5);
    // Choose a scale for coordinates
    vector<int> scales = {10, 1000, 1000000000};
    int L = rnd.any(scales);
    // Choose distribution types for houses and lots
    // 1 = full range [-L, L], 2 = narrow range [-L/10, L/10], 3 = extremes only
    int distH = rnd.next(1, 3);
    int distL = rnd.next(1, 3);
    println(N, Q);
    // Generate houses
    for (int i = 0; i < N; i++) {
        vector<long long> coords(11);
        for (int j = 0; j < 11; j++) {
            if (distH == 1) {
                coords[j] = rnd.next(-L, L);
            } else if (distH == 2) {
                int d = max(1, L / 10);
                coords[j] = rnd.next(-d, d);
            } else {
                coords[j] = rnd.any(vector<long long>{-L, L});
            }
        }
        println(coords);
    }
    // Generate parking lots
    for (int i = 0; i < Q; i++) {
        vector<long long> coords(11);
        for (int j = 0; j < 11; j++) {
            if (distL == 1) {
                coords[j] = rnd.next(-L, L);
            } else if (distL == 2) {
                int d = max(1, L / 10);
                coords[j] = rnd.next(-d, d);
            } else {
                coords[j] = rnd.any(vector<long long>{-L, L});
            }
        }
        println(coords);
    }
    return 0;
}

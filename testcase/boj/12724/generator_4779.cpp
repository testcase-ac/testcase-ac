#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases between 1 and 10
    int T = rnd.next(1, 10);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // Ensure at least one smallest and one largest case if possible
        int n;
        if (tc == 0) n = 100;
        else if (tc == 1) n = 800;
        else n = rnd.next(100, 800);
        println(n);
        auto genVec = [&](vector<int>& v) {
            int mode = rnd.next(0, 5);
            for (int i = 0; i < n; i++) {
                int x;
                switch (mode) {
                    // wide uniform distribution
                    case 0:
                        x = rnd.next(-100000, 100000);
                        break;
                    // narrow small-range distribution
                    case 1:
                        x = rnd.next(-1000, 1000);
                        break;
                    // many zeros with some large values
                    case 2:
                        if (rnd.next(0, 9) < 7)
                            x = 0;
                        else
                            x = rnd.next(-100000, 100000);
                        break;
                    // only non-negative
                    case 3:
                        x = rnd.next(0, 100000);
                        break;
                    // only non-positive
                        case 4:
                        x = -rnd.next(0, 100000);
                        break;
                    // mixed extremes and small, random sign
                    default: {
                        int mag = (rnd.next(0, 1) ? rnd.next(0, 100000) : rnd.next(0, 1000));
                        x = rnd.next(0, 1) ? mag : -mag;
                        break;
                    }
                }
                v[i] = x;
            }
        };
        vector<int> v1(n), v2(n);
        genVec(v1);
        genVec(v2);
        // Output vectors
        println(v1);
        println(v2);
    }
    return 0;
}

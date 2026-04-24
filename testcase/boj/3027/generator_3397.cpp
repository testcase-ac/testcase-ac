#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    const int minC = 1, maxC = 999;
    int N = rnd.next(1, 10);
    println(N);
    for (int i = 0; i < N; i++) {
        // choose plane skewed by weight t in [-2,2]
        int t = rnd.next(-2, 2);
        int p = rnd.wnext(3, t); // 0=XY,1=YZ,2=ZX
        // fixed coordinate
        int f = rnd.next(minC, maxC);
        // choose two intervals ensuring positive area
        int a1 = rnd.next(minC, maxC - 1);
        int b1 = rnd.next(a1 + 1, maxC);
        int a2 = rnd.next(minC, maxC - 1);
        int b2 = rnd.next(a2 + 1, maxC);
        int x1, y1, z1, x2, y2, z2;
        if (p == 0) {
            // XY-plane: z=fixed, x∈[a1,b1], y∈[a2,b2]
            x1 = a1; y1 = a2; z1 = f;
            x2 = b1; y2 = b2; z2 = f;
        } else if (p == 1) {
            // YZ-plane: x=fixed, y∈[a1,b1], z∈[a2,b2]
            x1 = f; y1 = a1; z1 = a2;
            x2 = f; y2 = b1; z2 = b2;
        } else {
            // ZX-plane: y=fixed, z∈[a1,b1], x∈[a2,b2]
            x1 = a2; y1 = f; z1 = a1;
            x2 = b2; y2 = f; z2 = b1;
        }
        // output two opposite vertices in random order
        if (rnd.next(0, 1) == 0)
            println(x1, y1, z1, x2, y2, z2);
        else
            println(x2, y2, z2, x1, y1, z1);
    }
    return 0;
}

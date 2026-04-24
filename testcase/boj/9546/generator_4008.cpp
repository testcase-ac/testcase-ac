#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases: small, up to 10
    int T = rnd.next(1, 10);
    println(T);

    // For diversity, pick k from small, medium, or large ranges
    for (int i = 0; i < T; i++) {
        double p = rnd.next();
        int k;
        if (p < 0.3) {
            // small k
            k = rnd.next(1, 5);
        } else if (p < 0.6) {
            // medium k
            k = rnd.next(6, 15);
        } else {
            // large k
            k = rnd.next(16, 30);
        }
        println(k);
    }
    return 0;
}

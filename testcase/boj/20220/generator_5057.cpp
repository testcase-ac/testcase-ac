#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Height of pyramid
    int h = rnd.next(1, 10);
    int total = h * (h + 1) / 2;

    // With small probability pick extreme s = 0 or s = total
    int pick = rnd.next(0, 9);
    int s;
    if (pick == 0) {
        s = 0;
    } else if (pick == 1) {
        s = total;
    } else {
        // Otherwise choose distribution type
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            // Uniform in [0, total]
            s = rnd.next(0, total);
        } else if (mode == 1) {
            // Bias toward small s: minimum of a few samples
            int t = rnd.next(1, 3);
            s = rnd.wnext(total + 1, -t);
        } else {
            // Bias toward large s: maximum of a few samples
            int t = rnd.next(1, 3);
            s = rnd.wnext(total + 1, t);
        }
    }

    // Output the test case
    println(h, s);
    return 0;
}

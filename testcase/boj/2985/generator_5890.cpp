#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for op bias: t in [-1,0,1]
    vector<int> tvals = {-1, 0, 1};
    int t = rnd.any(tvals);
    // opIndex: 0:+, 1:-, 2:*, 3:/
    int op = rnd.wnext(4, t);
    // side = 0 means "a op b = c", side = 1 means "a = b op c"
    int side = rnd.next(0, 1);

    int a, b, c;
    if (side == 0) {
        // Generate a, b then c
        switch (op) {
            case 0: // a + b = c
                a = rnd.next(1, 99);
                b = rnd.next(1, 100 - a);
                c = a + b;
                break;
            case 1: // a - b = c
                a = rnd.next(2, 100);
                b = rnd.next(1, a - 1);
                c = a - b;
                break;
            case 2: // a * b = c
                a = rnd.next(1, 100);
                b = rnd.next(1, 100 / a);
                c = a * b;
                break;
            case 3: // a / b = c
                b = rnd.next(1, 100);
                c = rnd.next(1, 100 / b);
                a = b * c;
                break;
        }
    } else {
        // Generate b, c then a
        switch (op) {
            case 0: // a = b + c
                b = rnd.next(1, 99);
                c = rnd.next(1, 100 - b);
                a = b + c;
                break;
            case 1: // a = b - c
                b = rnd.next(2, 100);
                c = rnd.next(1, b - 1);
                a = b - c;
                break;
            case 2: // a = b * c
                b = rnd.next(1, 100);
                c = rnd.next(1, 100 / b);
                a = b * c;
                break;
            case 3: // a = b / c
                c = rnd.next(1, 100);
                a = rnd.next(1, 100 / c);
                b = a * c;
                break;
        }
    }

    // Output the three numbers preserving input order
    println(a, b, c);
    return 0;
}

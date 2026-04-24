#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameters for diversity
    vector<int> specials = {1, 8, 9, 10, 80, 81, 100, 999, 1000, 9999, 10000};
    double pickSpecial = rnd.next(0.0, 1.0);

    int T;
    if (pickSpecial < 0.2) {
        // 20% chance to pick a special boundary-like value
        T = rnd.any(specials);
    } else {
        // otherwise uniform random in full range
        T = rnd.next(1, 10000);
    }

    println(T);
    return 0;
}

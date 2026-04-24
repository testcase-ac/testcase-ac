#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Decide if we include the extreme case 1000000
    double r = rnd.next();
    int A = -1, B = -1;
    if (r < 0.05) {
        A = B = 1000000;
    } else if (r < 0.15) {
        A = 1000000;
    } else if (r < 0.25) {
        B = 1000000;
    }

    // Function to generate a random number between 1 and 999999 with varied digit-length
    auto genRand = [&]() {
        vector<int> biases = {-1, 0, 1};
        int t = rnd.any(biases);
        // wnext(6, t) gives [0..5], +1 -> length in [1..6]
        int len = rnd.wnext(6, t) + 1;
        int num = rnd.next(1, 9); // first digit 1-9
        for (int i = 1; i < len; i++) {
            num = num * 10 + rnd.next(0, 9);
        }
        return num;
    };

    if (A == -1) A = genRand();
    if (B == -1) B = genRand();

    println(A, B);
    return 0;
}

#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose an upper bound for n from a small diverse set
    vector<int> uppers = {3, 4, 5, 6, 7, 8, 9, 10, 12, 15, 20};
    int upper = rnd.any(uppers);

    // Hyper-parameter: sometimes bias n by its remainder modulo 3
    bool mod_bias = rnd.next(0, 1);
    int n;
    if (mod_bias) {
        int r = rnd.next(0, 2);
        vector<int> valid;
        for (int i = 3; i <= upper; ++i)
            if (i % 3 == r)
                valid.push_back(i);
        if (!valid.empty())
            n = rnd.any(valid);
        else
            n = rnd.next(3, upper);
    } else {
        n = rnd.next(3, upper);
    }

    // Output the single test case
    println(n);
    return 0;
}

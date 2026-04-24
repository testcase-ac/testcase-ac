#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Length of bit strings
    int L = rnd.next(1, 10);

    // Ensure we get both odd and even n in different cases
    bool want_odd = rnd.next(0, 1);
    int N;
    if (want_odd) {
        vector<int> odds;
        for (int i = 1; i <= 20; i += 2) odds.push_back(i);
        N = rnd.any(odds);
    } else {
        vector<int> evens;
        for (int i = 2; i <= 20; i += 2) evens.push_back(i);
        N = rnd.any(evens);
    }

    // Hyper-parameter: density mode (0=random, 1=mostly zeros, 2=mostly ones)
    int mode = rnd.next(0, 2);
    string before;
    before.reserve(L);
    for (int i = 0; i < L; ++i) {
        char c;
        if (mode == 1) {
            // mostly zeros
            c = (rnd.next(0, 9) == 0 ? '1' : '0');
        } else if (mode == 2) {
            // mostly ones
            c = (rnd.next(0, 9) == 0 ? '0' : '1');
        } else {
            // uniform
            c = char('0' + rnd.next(0, 1));
        }
        before.push_back(c);
    }

    // Decide if this test should succeed or fail
    bool succeed = rnd.next(0, 1);

    // Compute the correct "after" if program is correct
    string after = before;
    if (N % 2 == 1) {
        for (int i = 0; i < L; ++i)
            after[i] = (after[i] == '0' ? '1' : '0');
    }

    // If we want this case to fail, flip one random bit in the "after"
    if (!succeed) {
        int pos = rnd.next(0, L - 1);
        after[pos] = (after[pos] == '0' ? '1' : '0');
    }

    // Output
    println(N);
    printf("%s\n", before.c_str());
    printf("%s\n", after.c_str());

    return 0;
}

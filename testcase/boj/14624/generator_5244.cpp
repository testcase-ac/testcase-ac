#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Define small possible N values
    vector<int> odds{3, 5, 7, 9};
    vector<int> evens{4, 6, 8, 10};

    // Decide whether to generate odd or even N
    bool wantOdd = rnd.next(0, 1);
    int N;
    if (wantOdd) {
        // 20% chance to pick an extreme odd (smallest or largest)
        if (rnd.next() < 0.2) {
            N = rnd.next(0, 1) ? odds.front() : odds.back();
        } else {
            N = rnd.any(odds);
        }
    } else {
        // 20% chance to pick an extreme even (smallest or largest)
        if (rnd.next() < 0.2) {
            N = rnd.next(0, 1) ? evens.front() : evens.back();
        } else {
            N = rnd.any(evens);
        }
    }

    // Output single test case
    println(N);
    return 0;
}

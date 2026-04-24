#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Hyper-parameter: choose an upper bound for N
    vector<int> maxChoices = {10, 50, 100, 1000, 1000000};
    int maxN = rnd.any(maxChoices);

    // Precompute Fibonacci numbers (losing positions) up to maxN
    vector<int> fibs;
    int a = 1, b = 2;
    while (b <= maxN) {
        if (b >= 2) fibs.push_back(b);
        int c = a + b;
        a = b;
        b = c;
    }

    int N;
    // 10% of the time pick a Fibonacci (losing) state to force -1
    if (!fibs.empty() && rnd.next(0, 9) == 0) {
        N = rnd.any(fibs);
    } else {
        N = rnd.next(2, maxN);
    }

    println(N);
    return 0;
}

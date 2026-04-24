#include "testlib.h"
#include <vector>
#include <numeric>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter: bias for denominator B
    int t = rnd.next(-2, 2);
    int B = rnd.wnext(8, t) + 2; // yields B in [2,9]
    // Collect numerators A that are coprime with B
    vector<int> cand;
    for (int A = 1; A < B; ++A)
        if (gcd(A, B) == 1)
            cand.push_back(A);
    // Hyper-parameter: sometimes pick smallest or largest numerator
    int A;
    if (cand.size() > 1 && rnd.next(0, 2) == 0) {
        A = *min_element(cand.begin(), cand.end());
    } else if (cand.size() > 1 && rnd.next(0, 2) == 1) {
        A = *max_element(cand.begin(), cand.end());
    } else {
        A = rnd.any(cand);
    }
    // Output A B
    println(A, B);
    return 0;
}

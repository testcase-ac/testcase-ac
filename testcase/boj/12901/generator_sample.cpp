#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const long long maxValue = 1000000000000LL;
    int mode = rnd.next(0, 7);

    long long A;
    long long width;

    if (mode == 0) {
        A = rnd.next(1LL, 30LL);
        width = rnd.next(0LL, min(30LL, maxValue - A));
    } else if (mode == 1) {
        A = rnd.next(1LL, 500LL);
        width = rnd.next(1LL, min(200LL, maxValue - A));
    } else if (mode == 2) {
        A = rnd.next(999999000000LL, maxValue);
        width = rnd.next(0LL, min(1000000LL, maxValue - A));
    } else if (mode == 3) {
        A = rnd.next(1LL, maxValue - 1000000LL);
        width = rnd.next(500000LL, 1000000LL);
    } else if (mode == 4) {
        A = rnd.next(1LL, maxValue - 1000LL);
        width = rnd.next(0LL, 2LL);
    } else if (mode == 5) {
        A = rnd.next(2LL, 1000000LL);
        width = rnd.next(10LL, 300LL);
    } else {
        A = rnd.next(1LL, maxValue - 10000LL);
        width = rnd.next(1LL, 10000LL);
    }

    long long B = A + width;

    vector<long long> pChoices;
    pChoices.push_back(2);
    pChoices.push_back(B);
    pChoices.push_back(rnd.next(2LL, B));
    pChoices.push_back(rnd.next(2LL, min(B, 20LL)));
    pChoices.push_back(rnd.next(max(2LL, B - min(width, 1000LL)), B));

    if (B >= 3) pChoices.push_back(3);
    if (B >= 5) pChoices.push_back(5);
    if (B >= A) pChoices.push_back(max(2LL, min(B, A)));

    long long P = rnd.any(pChoices);
    println(A, B, P);

    return 0;
}

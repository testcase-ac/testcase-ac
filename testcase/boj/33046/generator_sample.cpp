#include "testlib.h"

#include <algorithm>
#include <utility>

using namespace std;

pair<int, int> randomPairWithSum(int sum) {
    int lo = max(1, sum - 6);
    int hi = min(6, sum - 1);
    int first = rnd.next(lo, hi);
    return {first, sum - first};
}

pair<int, int> randomPairWithResidue(int residue) {
    int sums[3];
    int count = 0;
    for (int sum = 2; sum <= 12; ++sum) {
        if (sum % 4 == residue) {
            sums[count++] = sum;
        }
    }
    return randomPairWithSum(sums[rnd.next(count)]);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    pair<int, int> first;
    pair<int, int> second;
    int mode = rnd.next(5);

    if (mode == 0) {
        first = {rnd.next(1, 6), rnd.next(1, 6)};
        second = {rnd.next(1, 6), rnd.next(1, 6)};
    } else if (mode == 1) {
        int firstResidue = rnd.next(4);
        int finalPlayer = rnd.next(4);
        int secondResidue = (finalPlayer + 2 - firstResidue + 8) % 4;
        first = randomPairWithResidue(firstResidue);
        second = randomPairWithResidue(secondResidue);
    } else if (mode == 2) {
        int a = rnd.next(1, 6);
        int c = rnd.next(1, 6);
        first = {a, a};
        second = {c, c};
    } else if (mode == 3) {
        first = rnd.next(2) == 0 ? make_pair(1, rnd.next(1, 6)) : make_pair(6, rnd.next(1, 6));
        second = rnd.next(2) == 0 ? make_pair(rnd.next(1, 6), 1) : make_pair(rnd.next(1, 6), 6);
    } else {
        first = randomPairWithSum(rnd.next(2, 12));
        second = randomPairWithSum(rnd.next(2, 12));
    }

    println(first.first, first.second);
    println(second.first, second.second);

    return 0;
}

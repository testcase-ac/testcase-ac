#include "testlib.h"
#include <vector>

using namespace std;

int randomNonMultiple(int first) {
    vector<int> candidates;
    for (int value = 1; value <= 100; ++value) {
        if (value % first != 0) candidates.push_back(value);
    }
    return candidates.empty() ? 1 : rnd.any(candidates);
}

int randomMultiple(int first) {
    int factor = rnd.next(1, 100 / first);
    return first * factor;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> values;
    int completeRounds = rnd.next(1, 8);

    for (int round = 0; round < completeRounds; ++round) {
        int first = rnd.next(1, 100);
        values.push_back(first);

        int beforeMult = rnd.next(0, 5);
        for (int i = 0; i < beforeMult; ++i) {
            values.push_back(randomNonMultiple(first));
        }

        values.push_back(randomMultiple(first));
    }

    if (rnd.next(0, 1)) {
        int first = rnd.next(1, 100);
        values.push_back(first);

        int extra = rnd.next(0, 4);
        for (int i = 0; i < extra; ++i) {
            values.push_back(randomNonMultiple(first));
        }
    }

    println((int)values.size());
    for (int value : values) {
        println(value);
    }

    return 0;
}

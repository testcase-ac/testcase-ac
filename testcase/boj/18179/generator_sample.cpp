#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeBefore(int n, int alphabetSize) {
    const string bases = "ACGT";
    string s;
    s.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (rnd.next(4) == 0) {
            s.push_back(bases[i % alphabetSize]);
        } else {
            s.push_back(bases[rnd.next(alphabetSize)]);
        }
    }

    return s;
}

void applyPairSwaps(string& s, int rounds) {
    int n = static_cast<int>(s.size());
    for (int i = 0; i < rounds; ++i) {
        int first = rnd.next(n);
        int second = rnd.next(n);
        swap(s[first], s[second]);
    }
}

void applyDistinctCycle(string& s, int cycleLength) {
    int n = static_cast<int>(s.size());
    vector<int> positions;
    for (int attempts = 0; attempts < 200 && static_cast<int>(positions.size()) < cycleLength; ++attempts) {
        int pos = rnd.next(n);
        bool used = false;
        for (int existing : positions) {
            used = used || existing == pos;
        }
        if (!used) {
            positions.push_back(pos);
        }
    }

    if (static_cast<int>(positions.size()) < cycleLength) {
        return;
    }

    char carry = s[positions.back()];
    for (int i = cycleLength - 1; i > 0; --i) {
        s[positions[i]] = s[positions[i - 1]];
    }
    s[positions[0]] = carry;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(5);
    int n;
    if (mode == 0) {
        n = 1;
    } else if (mode == 1) {
        n = rnd.next(2, 8);
    } else if (mode == 2) {
        n = rnd.next(9, 30);
    } else if (mode == 3) {
        n = rnd.next(31, 80);
    } else {
        n = rnd.next(81, 160);
    }

    int alphabetSize = rnd.next(1, 4);
    string before = makeBefore(n, alphabetSize);
    string after = before;

    if (mode == 0) {
        // Keep the single-character edge case unchanged.
    } else if (mode == 1) {
        applyPairSwaps(after, rnd.next(1, max(1, n / 2)));
    } else if (mode == 2) {
        applyDistinctCycle(after, rnd.next(3, min(4, n)));
        applyPairSwaps(after, rnd.next(1, n));
    } else if (mode == 3) {
        shuffle(after.begin(), after.end());
    } else {
        int rounds = rnd.next(n / 2, n * 2);
        applyPairSwaps(after, rounds);
        if (rnd.next(2) == 0) {
            shuffle(after.begin(), after.end());
        }
    }

    println(before);
    println(after);

    return 0;
}

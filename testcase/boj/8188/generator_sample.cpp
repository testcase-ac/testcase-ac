#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> makeSubsequence(const vector<int>& a) {
    vector<int> result;
    for (int value : a) {
        if (rnd.next(0, 1) == 1) {
            result.push_back(value);
        }
    }
    if (result.empty()) {
        result.push_back(a[rnd.next(static_cast<int>(a.size()))]);
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int baseLength = rnd.next(6, 35);
    int alphabetSize = rnd.next(2, 8);
    int maxValue = rnd.next(alphabetSize + 3, 30);

    vector<int> alphabet;
    for (int i = 0; i < alphabetSize; ++i) {
        alphabet.push_back(i + 1);
    }
    shuffle(alphabet.begin(), alphabet.end());

    vector<int> a(baseLength);
    for (int i = 0; i < baseLength; ++i) {
        if (i > 0 && rnd.next(0, 99) < 35) {
            a[i] = a[i - 1];
        } else {
            a[i] = rnd.any(alphabet);
        }
    }

    int queryCount = rnd.next(6, 15);
    vector<vector<int>> queries;
    queries.reserve(queryCount);

    for (int qi = 0; qi < queryCount; ++qi) {
        int mode = rnd.next(0, 5);
        vector<int> q = makeSubsequence(a);

        if (mode == 1) {
            q.insert(q.begin() + rnd.next(static_cast<int>(q.size()) + 1), maxValue);
        } else if (mode == 2) {
            int value = rnd.any(alphabet);
            int count = 0;
            for (int x : a) {
                count += (x == value);
            }
            q.assign(count + rnd.next(1, 3), value);
        } else if (mode == 3 && q.size() >= 2) {
            reverse(q.begin(), q.end());
        } else if (mode == 4) {
            int pos = rnd.next(static_cast<int>(q.size()));
            q[pos] = maxValue;
        } else if (mode == 5) {
            int from = rnd.next(0, baseLength - 2);
            q = {a[from + 1], a[from]};
        }

        queries.push_back(q);
    }

    println(baseLength);
    println(a);
    println(queryCount);
    for (const vector<int>& q : queries) {
        println(static_cast<int>(q.size()));
        println(q);
    }

    return 0;
}

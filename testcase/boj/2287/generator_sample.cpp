#include "testlib.h"

#include <algorithm>
#include <set>
#include <vector>

using namespace std;

int repeatedDigit(int k, int len) {
    int value = 0;
    for (int i = 0; i < len; ++i) value = value * 10 + k;
    return value;
}

vector<int> buildRepresentableValues(int k) {
    vector<set<int>> values(9);

    for (int len = 1; len <= 8; ++len) {
        int value = repeatedDigit(k, len);
        if (value <= 32000) values[len].insert(value);
    }

    for (int len = 1; len <= 8; ++len) {
        for (int leftLen = 1; leftLen < len; ++leftLen) {
            int rightLen = len - leftLen;
            for (int left : values[leftLen]) {
                for (int right : values[rightLen]) {
                    long long sum = 1LL * left + right;
                    long long diff = abs(left - right);
                    long long product = 1LL * left * right;

                    if (1 <= sum && sum <= 32000) values[len].insert((int)sum);
                    if (1 <= diff && diff <= 32000) values[len].insert((int)diff);
                    if (1 <= product && product <= 32000) values[len].insert((int)product);

                    if (right != 0 && left % right == 0) {
                        int quotient = left / right;
                        if (1 <= quotient && quotient <= 32000) values[len].insert(quotient);
                    }
                    if (left != 0 && right % left == 0) {
                        int quotient = right / left;
                        if (1 <= quotient && quotient <= 32000) values[len].insert(quotient);
                    }
                }
            }
        }
    }

    set<int> uniqueValues;
    for (int len = 1; len <= 8; ++len) {
        uniqueValues.insert(values[len].begin(), values[len].end());
    }
    return vector<int>(uniqueValues.begin(), uniqueValues.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int k = rnd.next(1, 9);
    vector<int> queries;
    vector<int> representable = buildRepresentableValues(k);

    int mode = rnd.next(0, 5);
    int n;
    if (mode == 5) {
        n = rnd.next(80, 1000);
    } else if (mode == 4) {
        n = rnd.next(20, 80);
    } else {
        n = rnd.next(1, 20);
    }

    auto addRandomRepresentable = [&]() {
        queries.push_back(rnd.any(representable));
    };

    auto addBoundaryOrRandom = [&]() {
        static const vector<int> boundaries = {1, 2, 3, 4, 5, 9, 10, 11, 55, 99, 100, 999, 1000, 31168, 31999, 32000};
        if (rnd.next(0, 2) == 0) {
            queries.push_back(rnd.any(boundaries));
        } else {
            queries.push_back(rnd.next(1, 32000));
        }
    };

    for (int i = 1; i <= min(8, n); ++i) {
        int value = repeatedDigit(k, i);
        if (value <= 32000) queries.push_back(value);
    }

    while ((int)queries.size() < n) {
        if (mode == 0) {
            addRandomRepresentable();
        } else if (mode == 1) {
            addBoundaryOrRandom();
        } else if (mode == 2) {
            if (rnd.next(0, 3) == 0) addBoundaryOrRandom();
            else addRandomRepresentable();
        } else if (mode == 3) {
            int base = rnd.any(representable);
            int delta = rnd.next(-20, 20);
            queries.push_back(max(1, min(32000, base + delta)));
        } else {
            if (rnd.next(0, 1) == 0) addRandomRepresentable();
            else queries.push_back(rnd.next(1, 32000));
        }
    }

    shuffle(queries.begin(), queries.end());

    println(k);
    println(n);
    for (int i = 0; i < n; ++i) println(queries[i]);

    return 0;
}

#include "testlib.h"

#include <cstdint>
#include <vector>

using namespace std;

int primeExponentInFactorial(int n, int p) {
    int result = 0;
    while (n > 0) {
        n /= p;
        result += n;
    }
    return result;
}

bool fitsUnsigned32(const vector<int>& rows) {
    int total = 0;
    for (int rowLength : rows) {
        total += rowLength;
    }

    vector<int> exponents(31, 0);
    const vector<int> primes = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    for (int p : primes) {
        exponents[p] = primeExponentInFactorial(total, p);
    }

    for (int row = 0; row < (int)rows.size(); ++row) {
        for (int col = 1; col <= rows[row]; ++col) {
            int below = 0;
            for (int nextRow = row + 1; nextRow < (int)rows.size(); ++nextRow) {
                if (rows[nextRow] >= col) {
                    ++below;
                }
            }

            int remaining = rows[row] - col + below + 1;
            for (int p : primes) {
                while (remaining % p == 0) {
                    --exponents[p];
                    remaining /= p;
                }
            }
            if (remaining != 1) {
                return false;
            }
        }
    }

    uint64_t arrangements = 1;
    for (int p : primes) {
        if (exponents[p] < 0) {
            return false;
        }
        for (int i = 0; i < exponents[p]; ++i) {
            if (arrangements > 4294967295ULL / (uint64_t)p) {
                return false;
            }
            arrangements *= (uint64_t)p;
        }
    }
    return true;
}

vector<int> randomPartition(int total, int rows) {
    vector<int> result;
    int remaining = total;
    int previous = total;
    for (int i = 0; i < rows; ++i) {
        int slotsLeft = rows - i - 1;
        int lo = (remaining + slotsLeft) / (slotsLeft + 1);
        int hi = min(previous, remaining - slotsLeft);
        int value = (i + 1 == rows) ? remaining : rnd.next(lo, hi);
        result.push_back(value);
        remaining -= value;
        previous = value;
    }
    return result;
}

vector<int> makeCase(int mode) {
    for (int attempt = 0; attempt < 1000; ++attempt) {
        vector<int> rows;
        if (mode == 0) {
            rows = {rnd.next(1, 30)};
        } else if (mode == 1) {
            int k = rnd.next(1, 5);
            rows.assign(k, 1);
        } else if (mode == 2) {
            int k = rnd.next(2, 5);
            int value = rnd.next(1, 30 / k);
            rows.assign(k, value);
        } else if (mode == 3) {
            int k = rnd.next(2, 5);
            int first = rnd.next(k, min(12, 30));
            for (int value = first; (int)rows.size() < k && value >= 1; --value) {
                rows.push_back(value);
            }
        } else {
            int k = rnd.next(1, 5);
            int total = rnd.next(k, 30);
            rows = randomPartition(total, k);
        }

        int total = 0;
        for (int rowLength : rows) {
            total += rowLength;
        }
        if (total <= 30 && fitsUnsigned32(rows)) {
            return rows;
        }
    }

    return vector<int>{1};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int testCount = rnd.next(8, 20);
    println(testCount);
    for (int tc = 0; tc < testCount; ++tc) {
        vector<int> rows = makeCase(rnd.next(0, 4));
        println((int)rows.size());
        println(rows);
    }

    return 0;
}

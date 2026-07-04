#include "testlib.h"

#include <algorithm>
#include <cstring>
#include <string>
#include <vector>

using namespace std;

const int MAX_HEADS = 30000000;
const int MAX_CUTS = 200000;

int targetOnes;
string binaryLimit;
int memo[32][32][2];

int countWithSameOnesDfs(int pos, int ones, int tight) {
    if (ones > targetOnes) {
        return 0;
    }
    if (pos == static_cast<int>(binaryLimit.size())) {
        return ones == targetOnes;
    }

    int& ret = memo[pos][ones][tight];
    if (ret != -1) {
        return ret;
    }

    ret = 0;
    int upper = tight ? binaryLimit[pos] - '0' : 1;
    for (int bit = 0; bit <= upper; ++bit) {
        ret += countWithSameOnesDfs(pos + 1, ones + bit,
                                    tight && bit == upper);
    }
    return ret;
}

int countPositiveNumbersWithSameOnes(int limit, int value) {
    targetOnes = __builtin_popcount(static_cast<unsigned>(value));
    binaryLimit.clear();
    for (int x = limit; x > 0; x >>= 1) {
        binaryLimit.push_back(static_cast<char>('0' + (x & 1)));
    }
    reverse(binaryLimit.begin(), binaryLimit.end());

    memset(memo, -1, sizeof(memo));
    return countWithSameOnesDfs(0, 0, 1);
}

vector<int> buildPreviousPrimeTable() {
    vector<char> isComposite(MAX_HEADS + 1, false);
    vector<int> previousPrime(MAX_HEADS + 1, 0);

    for (int i = 2; i * 1LL * i <= MAX_HEADS; ++i) {
        if (!isComposite[i]) {
            for (long long j = 1LL * i * i; j <= MAX_HEADS; j += i) {
                isComposite[static_cast<int>(j)] = true;
            }
        }
    }

    int lastPrime = 0;
    for (int i = 2; i <= MAX_HEADS; ++i) {
        if (!isComposite[i]) {
            lastPrime = i;
        }
        previousPrime[i] = lastPrime;
    }
    return previousPrime;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int heads = inf.readInt(2, MAX_HEADS, "K");
    inf.readSpace();
    int cuts = inf.readInt(2, MAX_CUTS, "N");
    inf.readEoln();

    vector<int> previousPrime = buildPreviousPrimeTable();

    for (int i = 1; i <= cuts; ++i) {
        int cut = inf.readInt(1, MAX_HEADS, "cut_i");
        inf.readEoln();

        ensuref(cut <= heads,
                "cut %d is head %d, but only %d heads remain before the strike",
                i, cut, heads);

        if (cut % 2 == 1) {
            if (cut == 1) {
                --heads;
            } else {
                int newHeads = previousPrime[cut - 1];
                heads = min(MAX_HEADS, heads - 1 + newHeads);
            }
        } else {
            heads -= countPositiveNumbersWithSameOnes(heads, cut);
        }

        ensuref(i == cuts || heads > 0,
                "monster has no heads after cut %d, before all cuts are read", i);
    }

    inf.readEof();
}

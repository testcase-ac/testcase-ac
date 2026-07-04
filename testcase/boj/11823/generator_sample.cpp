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

int countSameOnesDfs(int pos, int ones, int tight) {
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
        ret += countSameOnesDfs(pos + 1, ones + bit, tight && bit == upper);
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
    return countSameOnesDfs(0, 0, 1);
}

bool isPrime(int value) {
    if (value < 2) {
        return false;
    }
    for (int d = 2; 1LL * d * d <= value; ++d) {
        if (value % d == 0) {
            return false;
        }
    }
    return true;
}

int previousPrimeBelow(int value) {
    for (int candidate = value - 1; candidate >= 2; --candidate) {
        if (isPrime(candidate)) {
            return candidate;
        }
    }
    return 0;
}

int applyCut(int heads, int cut) {
    if (cut % 2 == 1) {
        if (cut == 1) {
            return heads - 1;
        }
        return min(MAX_HEADS, heads - 1 + previousPrimeBelow(cut));
    }
    return heads - countPositiveNumbersWithSameOnes(heads, cut);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int heads;
    if (mode == 0) {
        heads = rnd.next(2, 8);
    } else if (mode == 1) {
        heads = rnd.next(9, 80);
    } else if (mode == 2) {
        heads = rnd.next(81, 700);
    } else if (mode == 3) {
        heads = rnd.next(1000, 10000);
    } else if (mode == 4) {
        heads = rnd.next(MAX_HEADS - 1000, MAX_HEADS);
    } else {
        heads = rnd.any(vector<int>{2, 3, 4, 7, 15, 31, 63, 127, 255, 1023});
    }

    int initialHeads = heads;
    int maxGeneratedCuts = min(heads, mode >= 3 ? 18 : 35);
    int cutsCount = rnd.next(2, maxGeneratedCuts);
    vector<int> cuts;
    cuts.reserve(cutsCount);

    for (int i = 0; i < cutsCount; ++i) {
        bool isLast = i + 1 == cutsCount;
        vector<int> candidates;
        int scanLimit = min(heads, mode == 4 ? 80 : 900);

        for (int cut = 1; cut <= scanLimit; ++cut) {
            int nextHeads = applyCut(heads, cut);
            int remainingCuts = cutsCount - i - 1;
            bool leavesEnoughHeads = isLast || nextHeads >= remainingCuts;
            if (nextHeads >= 0 && leavesEnoughHeads) {
                candidates.push_back(cut);
            }
        }

        if (candidates.empty()) {
            break;
        }

        int cut;
        int style = rnd.next(0, 99);
        if (style < 20 && find(candidates.begin(), candidates.end(), 1) != candidates.end()) {
            cut = 1;
        } else if (style < 55) {
            vector<int> oddCuts;
            for (int candidate : candidates) {
                if (candidate % 2 == 1) {
                    oddCuts.push_back(candidate);
                }
            }
            cut = oddCuts.empty() ? rnd.any(candidates) : rnd.any(oddCuts);
        } else if (style < 85) {
            vector<int> evenCuts;
            for (int candidate : candidates) {
                if (candidate % 2 == 0) {
                    evenCuts.push_back(candidate);
                }
            }
            cut = evenCuts.empty() ? rnd.any(candidates) : rnd.any(evenCuts);
        } else {
            cut = candidates.back();
        }

        cuts.push_back(cut);
        heads = applyCut(heads, cut);
    }

    println(initialHeads, static_cast<int>(cuts.size()));
    for (int cut : cuts) {
        println(cut);
    }

    return 0;
}

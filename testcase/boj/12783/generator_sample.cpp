#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<int> randomCards(int minSize, int maxSize) {
    vector<int> digits;
    for (int d = 0; d <= 9; ++d) {
        digits.push_back(d);
    }
    shuffle(digits.begin(), digits.end());
    int n = rnd.next(minSize, maxSize);
    digits.resize(n);
    sort(digits.begin(), digits.end());
    return digits;
}

int numberFromCards(const vector<int>& cards, int maxLen) {
    int len = rnd.next(1, maxLen);
    int value = 0;
    for (int i = 0; i < len; ++i) {
        int digit = rnd.any(cards);
        if (i == 0 && len > 1) {
            for (int attempts = 0; attempts < 20 && digit == 0; ++attempts) {
                digit = rnd.any(cards);
            }
            if (digit == 0) {
                digit = 1;
            }
        }
        value = value * 10 + digit;
    }
    return max(1, value);
}

int boundedProductFromCards(const vector<int>& cards) {
    long long value = 1;
    int factors = rnd.next(2, 5);
    for (int i = 0; i < factors; ++i) {
        int factor = numberFromCards(cards, rnd.next(1, 3));
        if (factor == 0 || value * factor > 1000000) {
            break;
        }
        value *= factor;
    }
    return max(1, static_cast<int>(value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(4, 9);
    println(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(0, 5);
        vector<int> cards;
        if (mode == 0) {
            cards = randomCards(1, 2);
        } else if (mode == 1) {
            cards = randomCards(3, 6);
            if (find(cards.begin(), cards.end(), 0) == cards.end()) {
                cards[0] = 0;
                sort(cards.begin(), cards.end());
            }
        } else if (mode == 2) {
            cards = randomCards(7, 10);
        } else {
            cards = randomCards(2, 8);
        }

        int M = rnd.next(5, 12);
        println(static_cast<int>(cards.size()), cards);
        println(M);

        vector<int> special = {
            1, 2, 7, 10, 11, 16, 31, 64, 99, 101, 999,
            1000, 9999, 10000, 99991, 100000, 999983, 1000000
        };

        for (int i = 0; i < M; ++i) {
            int queryMode = rnd.next(0, 4);
            int k;
            if (queryMode == 0) {
                k = numberFromCards(cards, 6);
            } else if (queryMode == 1) {
                k = boundedProductFromCards(cards);
            } else if (queryMode == 2) {
                k = rnd.any(special);
            } else if (queryMode == 3) {
                k = rnd.next(1, 1000000);
            } else {
                k = rnd.next(900000, 1000000);
            }
            println(k);
        }
    }

    return 0;
}

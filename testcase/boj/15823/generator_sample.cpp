#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

static vector<int> shuffledDistinct(int count, int lo = 1) {
    vector<int> values;
    for (int i = 0; i < count; ++i) values.push_back(lo + i);
    shuffle(values.begin(), values.end());
    return values;
}

static void appendDistinctPack(vector<int>& cards, int len, int base) {
    vector<int> pack = shuffledDistinct(len, base);
    cards.insert(cards.end(), pack.begin(), pack.end());
}

static void addNoise(vector<int>& cards, int count, int alphabet, int base) {
    for (int i = 0; i < count; ++i) cards.push_back(base + rnd.next(alphabet));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> cards;
    int m = 1;
    int mode = rnd.next(6);

    if (mode == 0) {
        int n = rnd.next(1, 45);
        m = rnd.next(1, n);
        cards = shuffledDistinct(n);
    } else if (mode == 1) {
        int n = rnd.next(1, 70);
        m = rnd.next(1, n);
        int value = rnd.next(1, 20);
        cards.assign(n, value);
    } else if (mode == 2) {
        int alphabet = rnd.next(2, 8);
        int n = rnd.next(alphabet, 80);
        m = rnd.next(1, n);
        addNoise(cards, n, alphabet, 1);
    } else if (mode == 3) {
        int packLen = rnd.next(1, 12);
        m = rnd.next(1, 6);
        for (int i = 0; i < m; ++i) {
            appendDistinctPack(cards, packLen, 1 + i * 100);
            addNoise(cards, rnd.next(0, 3), max(1, packLen / 2), 400 + i * 20);
        }
        addNoise(cards, rnd.next(0, 8), rnd.next(1, 5), 900);
    } else if (mode == 4) {
        int blockLen = rnd.next(2, 10);
        int blocks = rnd.next(2, 8);
        m = rnd.next(1, min(blocks, 5));
        vector<int> block = shuffledDistinct(blockLen);
        for (int i = 0; i < blocks; ++i) {
            vector<int> cur = block;
            if (rnd.next(2)) shuffle(cur.begin(), cur.end());
            cards.insert(cards.end(), cur.begin(), cur.end());
        }
        if (rnd.next(2)) addNoise(cards, rnd.next(1, 6), blockLen, 200);
    } else {
        int n = rnd.next(2, 90);
        m = rnd.next(1, n);
        int runValue = rnd.next(1, 20);
        while ((int)cards.size() < n) {
            if (rnd.next(3) == 0) {
                int len = min(rnd.next(1, 8), n - (int)cards.size());
                appendDistinctPack(cards, len, rnd.next(30, 300));
            } else {
                int len = min(rnd.next(1, 8), n - (int)cards.size());
                for (int i = 0; i < len; ++i) cards.push_back(runValue + rnd.next(0, 3));
            }
        }
    }

    if (rnd.next(4) == 0) shuffle(cards.begin(), cards.end());

    println((int)cards.size(), m);
    println(cards);
    return 0;
}

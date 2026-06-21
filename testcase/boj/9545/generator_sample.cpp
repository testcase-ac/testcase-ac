#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string makePair(int first, int second) {
    string s;
    s.push_back(char('a' + first));
    s.push_back(char('a' + second));
    return s;
}

vector<string> allPairs() {
    vector<string> pairs;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            pairs.push_back(makePair(i, j));
        }
    }
    return pairs;
}

void addUnique(vector<string>& pairs, set<string>& used, const string& pair) {
    if (used.insert(pair).second) {
        pairs.push_back(pair);
    }
}

vector<string> makeCase(int mode) {
    vector<string> pairs;
    set<string> used;

    if (mode == 0) {
        return pairs;
    }

    if (mode == 1) {
        int k = rnd.next(1, 8);
        for (int i = 0; i < k; ++i) {
            addUnique(pairs, used, makePair(rnd.next(26), rnd.next(26)));
        }
        return pairs;
    }

    if (mode == 2) {
        int k = rnd.next(1, 7);
        vector<int> letters;
        for (int i = 0; i < k; ++i) {
            letters.push_back(i);
        }
        shuffle(letters.begin(), letters.end());

        int n = rnd.next(k, min(30, k * k));
        while (int(pairs.size()) < n) {
            int a = rnd.any(letters);
            int b = rnd.any(letters);
            addUnique(pairs, used, makePair(a, b));
        }
        return pairs;
    }

    if (mode == 3) {
        int k = rnd.next(2, 10);
        for (int i = 0; i < k; ++i) {
            addUnique(pairs, used, makePair(i, i));
        }
        int extras = rnd.next(0, 20);
        while (extras--) {
            addUnique(pairs, used, makePair(rnd.next(k), rnd.next(k)));
        }
        return pairs;
    }

    if (mode == 4) {
        int k = rnd.next(4, 12);
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < k; ++j) {
                if (i != j && rnd.next(100) < 70) {
                    addUnique(pairs, used, makePair(i, j));
                }
            }
        }
        return pairs;
    }

    if (mode == 5) {
        vector<string> candidates = allPairs();
        shuffle(candidates.begin(), candidates.end());
        int n = rnd.next(50, 180);
        pairs.assign(candidates.begin(), candidates.begin() + n);
        return pairs;
    }

    vector<string> candidates = allPairs();
    shuffle(candidates.begin(), candidates.end());
    int keepAllowed = rnd.next(1, 18);
    int n = int(candidates.size()) - keepAllowed;
    pairs.assign(candidates.begin(), candidates.begin() + n);
    return pairs;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int mode = tc == 0 ? rnd.next(0, 6) : rnd.next(0, 7);
        vector<string> pairs = makeCase(mode);
        shuffle(pairs.begin(), pairs.end());

        println(int(pairs.size()));
        for (const string& pair : pairs) {
            println(pair);
        }
    }

    return 0;
}

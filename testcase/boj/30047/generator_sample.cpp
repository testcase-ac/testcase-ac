#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeValid(int depth, int budget) {
    if (depth <= 0 || budget <= 1) {
        return "x";
    }

    int choice = rnd.next(100);
    if (choice < 35) {
        return "x";
    }
    if (choice < 65) {
        return "g" + makeValid(depth - 1, budget - 1);
    }

    int leftBudget = rnd.next(1, budget - 1);
    int rightBudget = max(1, budget - 1 - leftBudget);
    return "f" + makeValid(depth - 1, leftBudget) + makeValid(depth - 1, rightBudget);
}

string makeUnaryChain(int maxLen) {
    int count = rnd.next(1, maxLen - 1);
    return string(count, 'g') + "x";
}

string makeInvalid(int maxLen) {
    int mode = rnd.next(5);
    if (mode == 0) {
        return string(rnd.next(1, maxLen), rnd.any(string("fg")));
    }
    if (mode == 1) {
        string s = makeValid(5, maxLen / 2);
        int extra = rnd.next(1, max(1, maxLen - (int)s.size()));
        while (extra--) {
            s += rnd.any(string("fgx"));
        }
        return s;
    }
    if (mode == 2) {
        string s = makeValid(5, maxLen);
        if (!s.empty()) {
            s.pop_back();
        }
        if (s.empty()) {
            s = "f";
        }
        return s;
    }
    if (mode == 3) {
        int len = rnd.next(2, maxLen);
        string s;
        for (int i = 0; i < len; ++i) {
            s += rnd.any(string("fgx"));
        }
        return s;
    }
    return "f" + makeUnaryChain(max(2, maxLen - 1));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int maxLen = rnd.next(2, 80);
    int mode = rnd.next(7);
    string s;

    if (mode == 0) {
        s = "x";
    } else if (mode == 1) {
        s = makeUnaryChain(maxLen);
    } else if (mode == 2) {
        s = makeValid(8, maxLen);
    } else if (mode == 3) {
        vector<string> leaves;
        int count = rnd.next(2, 8);
        for (int i = 0; i < count; ++i) {
            leaves.push_back(makeUnaryChain(rnd.next(2, 12)));
        }
        while (leaves.size() > 1) {
            string a = leaves.back();
            leaves.pop_back();
            string b = leaves.back();
            leaves.pop_back();
            leaves.push_back("f" + a + b);
            shuffle(leaves.begin(), leaves.end());
        }
        s = leaves[0];
    } else {
        s = makeInvalid(maxLen);
    }

    println(s);
    return 0;
}

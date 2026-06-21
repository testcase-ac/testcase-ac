#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

namespace {

constexpr int kMod = 1000000007;

string numberToken() {
    int mode = rnd.next(100);
    if (mode < 18) {
        return "0";
    }
    if (mode < 36) {
        return "1";
    }
    if (mode < 54) {
        return to_string(rnd.next(2, 9));
    }
    if (mode < 76) {
        return to_string(rnd.next(10, 200));
    }
    if (mode < 90) {
        return to_string(rnd.next(1000, 1000000));
    }
    return to_string(rnd.next(kMod - 25, kMod - 1));
}

void appendFlat(vector<string>& tokens, int count) {
    for (int i = 0; i < count; ++i) {
        tokens.push_back(numberToken());
    }
}

void appendGroup(vector<string>& tokens, int depth, int budget);

void appendUnit(vector<string>& tokens, int depth, int budget) {
    if (depth > 0 && budget >= 3 && rnd.next(100) < 45) {
        appendGroup(tokens, depth - 1, budget);
    } else {
        tokens.push_back(numberToken());
    }
}

void appendGroup(vector<string>& tokens, int depth, int budget) {
    tokens.push_back("(");
    int start = static_cast<int>(tokens.size());
    int innerBudget = budget - 2;
    int parts = rnd.next(1, max(1, min(5, innerBudget)));
    for (int i = 0; i < parts; ++i) {
        int used = static_cast<int>(tokens.size()) - start;
        int remaining = innerBudget - used;
        appendUnit(tokens, depth, max(1, remaining));
    }
    tokens.push_back(")");
}

vector<string> makeNestedChain() {
    vector<string> tokens;
    int depth = rnd.next(1, 8);
    int prefix = rnd.next(0, 3);
    appendFlat(tokens, prefix);
    for (int i = 0; i < depth; ++i) {
        tokens.push_back("(");
        if (rnd.next(100) < 55) {
            tokens.push_back(numberToken());
        }
    }
    appendFlat(tokens, rnd.next(1, 4));
    for (int i = 0; i < depth; ++i) {
        if (rnd.next(100) < 55) {
            tokens.push_back(numberToken());
        }
        tokens.push_back(")");
    }
    appendFlat(tokens, rnd.next(0, 3));
    return tokens;
}

vector<string> makeSiblingGroups() {
    vector<string> tokens;
    int groups = rnd.next(1, 6);
    for (int i = 0; i < groups; ++i) {
        if (rnd.next(100) < 35) {
            tokens.push_back(numberToken());
        }
        appendGroup(tokens, rnd.next(0, 3), 16);
    }
    if (rnd.next(100) < 35) {
        appendFlat(tokens, rnd.next(1, 4));
    }
    return tokens;
}

vector<string> makeRecursiveCase() {
    vector<string> tokens;
    int topParts = rnd.next(1, 6);
    for (int i = 0; i < topParts; ++i) {
        appendUnit(tokens, rnd.next(1, 5), 30);
    }
    return tokens;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> tokens;
    int mode = rnd.next(4);
    if (mode == 0) {
        appendFlat(tokens, rnd.next(1, 20));
    } else if (mode == 1) {
        tokens = makeNestedChain();
    } else if (mode == 2) {
        tokens = makeSiblingGroups();
    } else {
        tokens = makeRecursiveCase();
    }

    println(static_cast<int>(tokens.size()));
    println(tokens);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>

using namespace std;

int tierRank(char tier) {
    const string tiers = "BSGPD";
    size_t pos = tiers.find(tier);
    ensuref(pos != string::npos, "unknown tier: %c", tier);
    return static_cast<int>(pos);
}

int stageValue(const string& token) {
    ensuref(token.size() >= 2, "difficulty token is too short: %s", token.c_str());
    ensuref(token[0] == 'B' || token[0] == 'S' || token[0] == 'G' || token[0] == 'P' || token[0] == 'D',
            "invalid difficulty tier: %c", token[0]);

    string stage = token.substr(1);
    ensuref(!stage.empty(), "missing stage in difficulty token: %s", token.c_str());
    ensuref(stage == "0" || stage[0] != '0', "stage has leading zero: %s", token.c_str());

    int value = 0;
    for (char ch : stage) {
        ensuref('0' <= ch && ch <= '9', "stage contains a non-digit: %s", token.c_str());
        value = value * 10 + (ch - '0');
        ensuref(value <= 1000, "stage is greater than 1000: %s", token.c_str());
    }
    ensuref(1 <= value && value <= 1000, "stage is outside [1, 1000]: %s", token.c_str());
    return value;
}

bool easierBefore(const string& a, const string& b) {
    int tierA = tierRank(a[0]);
    int tierB = tierRank(b[0]);
    if (tierA != tierB) {
        return tierA < tierB;
    }
    return stageValue(a) > stageValue(b);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(2, 1000, "N");
    inf.readEoln();

    vector<string> difficulties;
    set<string> seen;
    for (int i = 0; i < n; ++i) {
        string difficulty = inf.readToken("[BSGPD][0-9]{1,4}", "difficulty");
        stageValue(difficulty);
        ensuref(seen.insert(difficulty).second, "duplicate difficulty token: %s", difficulty.c_str());
        difficulties.push_back(difficulty);

        if (i + 1 == n) {
            inf.readEoln();
        } else {
            inf.readSpace();
        }
    }
    inf.readEof();

    vector<string> sorted = difficulties;
    sort(sorted.begin(), sorted.end(), easierBefore);

    int mismatchCount = 0;
    for (int i = 0; i < n; ++i) {
        if (difficulties[i] != sorted[i]) {
            ++mismatchCount;
        }
    }
    ensuref(mismatchCount == 0 || mismatchCount == 2,
            "difficulty order must be sorted or differ by one swap, mismatches=%d", mismatchCount);
}

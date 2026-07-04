#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

namespace {

const string kAlphabet = "ATGC";

string randomDna(int len) {
    string s;
    s.reserve(len);
    for (int i = 0; i < len; ++i) {
        s.push_back(kAlphabet[rnd.next(static_cast<int>(kAlphabet.size()))]);
    }
    return s;
}

int longestOverlap(const string& left, const string& right) {
    int best = 0;
    const int lim = min(left.size(), right.size());
    for (int len = 1; len <= lim; ++len) {
        if (left.substr(left.size() - len) == right.substr(0, len)) {
            best = len;
        }
    }
    return best;
}

void addUnique(vector<string>& sources, set<string>& used, const string& source) {
    if (used.insert(source).second) {
        sources.push_back(source);
    }
}

string makeChainTarget(vector<string>& sources, set<string>& used, int pieces) {
    string target = randomDna(rnd.next(1, 8));
    addUnique(sources, used, target);

    for (int i = 1; i < pieces; ++i) {
        const int overlap = rnd.next(1, min<int>(target.size(), 6));
        string next = target.substr(target.size() - overlap);
        next += randomDna(rnd.next(1, 8));
        if (next.size() > 20) {
            next.resize(20);
        }
        addUnique(sources, used, next);
        target += next.substr(overlap);
    }

    return target;
}

string makeAlternatingTarget(vector<string>& sources, set<string>& used) {
    const string a = rnd.next(2) == 0 ? "ATA" : "GCG";
    const string b = a == "ATA" ? "TAT" : "CGC";
    addUnique(sources, used, a);
    addUnique(sources, used, b);

    string target = a;
    const int pieces = rnd.next(3, 12);
    for (int i = 1; i < pieces; ++i) {
        const string& next = (i % 2 == 0) ? a : b;
        target += next.substr(longestOverlap(target, next));
    }
    return target;
}

string makeRepeatedTarget(vector<string>& sources, set<string>& used) {
    const char c = kAlphabet[rnd.next(static_cast<int>(kAlphabet.size()))];
    const int sourceLen = rnd.next(2, 8);
    const int targetLen = rnd.next(sourceLen, 35);
    string source(sourceLen, c);
    string target(targetLen, c);
    addUnique(sources, used, source);
    return target;
}

void addDistractors(vector<string>& sources, set<string>& used, int desiredN) {
    while (static_cast<int>(sources.size()) < desiredN) {
        addUnique(sources, used, randomDna(rnd.next(1, 12)));
    }
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<string> sources;
    set<string> used;

    string target;
    const int mode = rnd.next(3);
    if (mode == 0) {
        target = makeRepeatedTarget(sources, used);
    } else if (mode == 1) {
        target = makeAlternatingTarget(sources, used);
    } else {
        target = makeChainTarget(sources, used, rnd.next(2, 10));
    }

    if (rnd.next(3) == 0 && static_cast<int>(target.size()) <= 20) {
        addUnique(sources, used, target);
    }

    const int desiredN = rnd.next(static_cast<int>(sources.size()),
                                  static_cast<int>(sources.size()) + 12);
    addDistractors(sources, used, desiredN);

    shuffle(sources.begin(), sources.end());

    println(static_cast<int>(sources.size()));
    println(target);
    for (const string& source : sources) {
        println(source);
    }

    return 0;
}

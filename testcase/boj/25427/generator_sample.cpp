#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

char randomUppercase() {
    return char('A' + rnd.next(26));
}

char randomFiller() {
    const string filler = "ABCEFGIJLMNOPQRTUVWXYZ";
    return rnd.any(filler);
}

string repeatedBlocks() {
    vector<pair<char, int>> blocks = {
        {'D', rnd.next(1, 7)},
        {'K', rnd.next(1, 7)},
        {'S', rnd.next(1, 7)},
        {'H', rnd.next(1, 7)},
    };

    string s;
    for (const auto& block : blocks) {
        s += string(rnd.next(0, 3), randomFiller());
        s += string(block.second, block.first);
    }
    s += string(rnd.next(0, 3), randomFiller());
    return s;
}

string noisySubsequence() {
    string s;
    const string target = "DKSH";
    for (char ch : target) {
        s += string(rnd.next(0, 5), randomFiller());
        s += ch;
        if (rnd.next(0, 1)) s += ch;
    }
    s += string(rnd.next(0, 5), randomFiller());
    return s;
}

string missingTargetLetter(int n) {
    string alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char removed = rnd.any(string("DKSH"));
    alphabet.erase(remove(alphabet.begin(), alphabet.end(), removed), alphabet.end());

    string s;
    for (int i = 0; i < n; ++i) s += rnd.any(alphabet);
    return s;
}

string randomUppercaseString(int n) {
    string s;
    for (int i = 0; i < n; ++i) s += randomUppercase();
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = string(1, randomUppercase());
    } else if (mode == 1) {
        s = missingTargetLetter(rnd.next(2, 30));
    } else if (mode == 2) {
        s = repeatedBlocks();
    } else if (mode == 3) {
        s = noisySubsequence();
    } else if (mode == 4) {
        s = randomUppercaseString(rnd.next(4, 30));
    } else {
        s = rnd.next(0, 1) ? "DKSH" : "HSDK";
        int extra = rnd.next(0, 12);
        while (extra--) s.insert(s.begin() + rnd.next((int)s.size() + 1), randomFiller());
    }

    println((int)s.size());
    println(s);
    return 0;
}

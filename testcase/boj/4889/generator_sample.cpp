#include "testlib.h"
#include <string>
#include <vector>

using namespace std;

string repeated(char ch, int count) {
    return string(count, ch);
}

string randomBraces(int length) {
    string s;
    s.reserve(length);
    for (int i = 0; i < length; ++i) {
        s.push_back(rnd.next(2) == 0 ? '{' : '}');
    }
    return s;
}

string alternating(int pairs, bool startsOpen) {
    string s;
    s.reserve(2 * pairs);
    for (int i = 0; i < 2 * pairs; ++i) {
        bool open = (i % 2 == 0) == startsOpen;
        s.push_back(open ? '{' : '}');
    }
    return s;
}

string shuffledBalancedPairs(int pairs) {
    string s = repeated('{', pairs) + repeated('}', pairs);
    shuffle(s.begin(), s.end());
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int caseCount = mode == 5 ? rnd.next(8, 20) : rnd.next(1, 7);
    vector<string> cases;
    cases.reserve(caseCount);

    for (int i = 0; i < caseCount; ++i) {
        int pairs = mode == 5 ? rnd.next(20, 120) : rnd.next(1, 15);
        int localMode = mode == 0 ? rnd.next(1, 4) : mode;

        if (localMode == 1) {
            cases.push_back(repeated('{', pairs) + repeated('}', pairs));
        } else if (localMode == 2) {
            cases.push_back(repeated('}', pairs) + repeated('{', pairs));
        } else if (localMode == 3) {
            cases.push_back(alternating(pairs, rnd.next(2) == 0));
        } else if (localMode == 4) {
            cases.push_back(shuffledBalancedPairs(pairs));
        } else {
            cases.push_back(randomBraces(2 * pairs));
        }
    }

    for (const string& s : cases) {
        println(s);
    }
    println(repeated('-', rnd.next(1, 5)));

    return 0;
}

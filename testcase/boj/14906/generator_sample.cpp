#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeSlump(int depth) {
    char head = rnd.next(0, 1) == 0 ? 'D' : 'E';
    int fCount = rnd.next(1, depth > 0 ? 5 : 8);
    string s(1, head);
    s += string(fCount, 'F');

    if (depth > 0 && rnd.next(0, 2) != 0) {
        s += makeSlump(depth - 1);
    } else {
        s += 'G';
    }
    return s;
}

string makeSlimp(int depth) {
    if (depth <= 0 || rnd.next(0, 3) == 0) {
        return "AH";
    }

    if (rnd.next(0, 1) == 0) {
        return "AB" + makeSlimp(depth - 1) + "C";
    }

    return "A" + makeSlump(depth - 1) + "C";
}

string makeSlurpy() {
    for (int attempt = 0; attempt < 100; ++attempt) {
        string s = makeSlimp(rnd.next(1, 5)) + makeSlump(rnd.next(1, 5));
        if ((int)s.size() <= 60) {
            return s;
        }
    }
    return "AHDFG";
}

string randomUppercase(int len) {
    string s;
    for (int i = 0; i < len; ++i) {
        s += char('A' + rnd.next(0, 25));
    }
    return s;
}

string makeNonSlurpy() {
    vector<string> templates = {
        "A", "Z", "AH", "DFG", "ABABCC", "SLURPY", "DG", "ADGC", "EFAHG",
    };

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        return rnd.any(templates);
    }
    if (mode == 1) {
        return makeSlurpy() + char('A' + rnd.next(0, 25));
    }
    if (mode == 2) {
        string s = makeSlurpy();
        s[rnd.next(0, (int)s.size() - 1)] = 'Z';
        return s;
    }
    if (mode == 3) {
        return randomUppercase(rnd.next(1, 60));
    }

    return string(rnd.next(1, 59), 'F') + 'G';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 10);
    vector<string> cases;

    if (n >= 1) {
        cases.push_back(makeSlurpy());
    }
    if (n >= 2) {
        cases.push_back(makeNonSlurpy());
    }
    if (n >= 3 && rnd.next(0, 1) == 0) {
        cases.push_back(randomUppercase(60));
    }

    while ((int)cases.size() < n) {
        if (rnd.next(0, 1) == 0) {
            cases.push_back(makeSlurpy());
        } else {
            cases.push_back(makeNonSlurpy());
        }
    }

    shuffle(cases.begin(), cases.end());

    println(n);
    for (string s : cases) {
        if ((int)s.size() > 60) {
            s.resize(60);
        }
        println(s);
    }

    return 0;
}

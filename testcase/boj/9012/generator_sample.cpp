#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeValid(int pairs) {
    string s;
    int open = 0;
    for (int i = 0; i < pairs; ++i) {
        if (open == 0 || rnd.next(2) == 0) {
            s += '(';
            ++open;
        } else {
            s += ')';
            --open;
            --i;
        }
    }
    s += string(open, ')');
    return s;
}

string makeTooManyClosing(int len) {
    string s = ")";
    int balance = -1;
    for (int i = 1; i < len; ++i) {
        if (balance < -2 || rnd.next(2) == 0) {
            s += '(';
            ++balance;
        } else {
            s += ')';
            --balance;
        }
    }
    return s;
}

string makeTooManyOpening(int len) {
    string s;
    int balance = 0;
    for (int i = 0; i < len - 1; ++i) {
        if (balance == 0 || rnd.next(3) != 0) {
            s += '(';
            ++balance;
        } else {
            s += ')';
            --balance;
        }
    }
    s += '(';
    return s;
}

string makeScrambledBalanced(int pairs) {
    string s(pairs, '(');
    s += string(pairs, ')');
    do {
        shuffle(s.begin(), s.end());
    } while (!s.empty() && s.front() == '(');
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int T = rnd.next(1, 24);
    vector<string> cases;
    cases.reserve(T);

    for (int tc = 0; tc < T; ++tc) {
        int mode = rnd.next(4);
        int len = rnd.next(2, 50);
        if (mode == 0) {
            int pairs = rnd.next(1, 25);
            cases.push_back(makeValid(pairs));
        } else if (mode == 1) {
            cases.push_back(makeTooManyClosing(len));
        } else if (mode == 2) {
            cases.push_back(makeTooManyOpening(len));
        } else {
            int pairs = rnd.next(1, 25);
            cases.push_back(makeScrambledBalanced(pairs));
        }
    }

    println(T);
    for (const string& s : cases) {
        println(s);
    }

    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomBrackets(int n) {
    string s;
    s.reserve(n);
    for (int i = 0; i < n; ++i) {
        s.push_back(rnd.next(0, 1) == 0 ? '(' : ')');
    }
    return s;
}

string balancedPairs(int pairs) {
    string s;
    s.reserve(2 * pairs);
    int open = 0;
    int close = 0;
    while (open < pairs || close < pairs) {
        if (open == pairs) {
            s.push_back(')');
            ++close;
        } else if (open == close || rnd.next(0, 2) > 0) {
            s.push_back('(');
            ++open;
        } else {
            s.push_back(')');
            ++close;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        int n = rnd.next(1, 30);
        s = randomBrackets(n);
    } else if (mode == 1) {
        int pairs = rnd.next(1, 12);
        s = balancedPairs(pairs);
        int prefix = rnd.next(0, 8);
        int suffix = rnd.next(0, 8);
        s = string(prefix, ')') + s + string(suffix, '(');
    } else if (mode == 2) {
        int n = rnd.next(1, 35);
        char c = rnd.next(0, 1) == 0 ? '(' : ')';
        s.assign(n, c);
    } else if (mode == 3) {
        int blocks = rnd.next(2, 10);
        for (int i = 0; i < blocks; ++i) {
            char c = (i % 2 == rnd.next(0, 1)) ? '(' : ')';
            s += string(rnd.next(1, 6), c);
        }
    } else if (mode == 4) {
        int pairs = rnd.next(2, 15);
        s = balancedPairs(pairs);
        if (!s.empty()) {
            int edits = rnd.next(1, min(5, (int)s.size()));
            for (int i = 0; i < edits; ++i) {
                int pos = rnd.next(0, (int)s.size() - 1);
                s[pos] = s[pos] == '(' ? ')' : '(';
            }
        }
    } else {
        int repeats = rnd.next(10, 60);
        for (int i = 0; i < repeats; ++i) {
            string chunk = rnd.any(vector<string>{"()", "(())", ")(", "(()", "())", "((()))"});
            s += chunk;
        }
    }

    println((int)s.size());
    println(s);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string makeBalanced(int pairs) {
    string s;
    int open = 0;
    int usedOpen = 0;
    for (int i = 0; i < 2 * pairs; ++i) {
        int remaining = 2 * pairs - i;
        if (usedOpen == pairs) {
            s += ')';
            --open;
        } else if (open == 0) {
            s += '(';
            ++open;
            ++usedOpen;
        } else if (pairs - usedOpen == open || rnd.next(remaining) < open) {
            s += ')';
            --open;
        } else {
            s += '(';
            ++open;
            ++usedOpen;
        }
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n;
    if (rnd.next(100) < 85) {
        n = 2 * rnd.next(1, 20);
    } else {
        n = 2 * rnd.next(21, 120);
    }

    int mode = rnd.next(6);
    string s;

    if (mode == 0) {
        s = makeBalanced(n / 2);
    } else if (mode == 1) {
        s = makeBalanced(n / 2);
        reverse(s.begin(), s.end());
    } else if (mode == 2) {
        int leftCount = rnd.next(0, n);
        s = string(leftCount, '(') + string(n - leftCount, ')');
    } else if (mode == 3) {
        int rightCount = rnd.next(0, n);
        s = string(rightCount, ')') + string(n - rightCount, '(');
    } else if (mode == 4) {
        string pattern = rnd.any(vector<string>{"()", ")(", "((", "))", "())(", ")(()"});
        while (int(s.size()) < n) s += pattern;
        s.resize(n);
    } else {
        for (int i = 0; i < n; ++i) {
            s += rnd.next(100) < rnd.next(20, 81) ? '(' : ')';
        }
    }

    println(s);
    return 0;
}

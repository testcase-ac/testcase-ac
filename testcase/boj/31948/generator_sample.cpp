#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomRuns(int maxLength) {
    int n = rnd.next(1, maxLength);
    string s;
    char c = rnd.next(0, 1) ? '1' : '0';
    while ((int)s.size() < n) {
        int remaining = n - (int)s.size();
        int runLength = rnd.next(1, min(remaining, rnd.next(1, 8)));
        s.append(runLength, c);
        c = (c == '0' ? '1' : '0');
    }
    return s;
}

void maybeInsertQuestion(string& s, bool forceQuestion) {
    if (!forceQuestion && rnd.next(0, 1) == 0) return;

    vector<int> positions;
    positions.push_back(0);
    if ((int)s.size() > 1) positions.push_back((int)s.size() - 1);
    for (int i = 1; i < (int)s.size(); ++i) {
        if (s[i] != s[i - 1]) positions.push_back(i);
    }
    positions.push_back(rnd.next(0, (int)s.size() - 1));

    s[rnd.any(positions)] = '?';
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s.assign(rnd.next(1, 30), rnd.next(0, 1) ? '1' : '0');
        maybeInsertQuestion(s, rnd.next(0, 2) == 0);
    } else if (mode == 1) {
        int n = rnd.next(1, 30);
        char c = rnd.next(0, 1) ? '1' : '0';
        for (int i = 0; i < n; ++i) s.push_back((i % 2 == 0) ? c : (c == '0' ? '1' : '0'));
        maybeInsertQuestion(s, true);
    } else if (mode == 2) {
        s = randomRuns(30);
        maybeInsertQuestion(s, false);
    } else if (mode == 3) {
        s = randomRuns(80);
        maybeInsertQuestion(s, true);
    } else if (mode == 4) {
        int left = rnd.next(1, 12);
        int middle = rnd.next(0, 12);
        int right = rnd.next(1, 12);
        char edge = rnd.next(0, 1) ? '1' : '0';
        char other = (edge == '0' ? '1' : '0');
        s.assign(left, edge);
        s.append(middle, other);
        s.append(right, edge);
        maybeInsertQuestion(s, rnd.next(0, 1) == 0);
    } else {
        int n = rnd.next(1, 120);
        for (int i = 0; i < n; ++i) s.push_back(rnd.next(0, 1) ? '1' : '0');
        maybeInsertQuestion(s, rnd.next(0, 3) != 0);
    }

    println(s);
    return 0;
}

#include "testlib.h"

#include <algorithm>
#include <string>

using namespace std;

string makeAlpsoo() {
    for (int attempts = 0; attempts < 1000; ++attempts) {
        int peak = rnd.next(1, 9);
        int upStep = rnd.next(1, 4);
        int downStep = rnd.next(1, 4);
        int maxLeftLen = min(4, peak / upStep);
        int maxRightLen = min(4, peak / downStep);
        if (maxLeftLen == 0 || maxRightLen == 0) continue;
        int leftLen = rnd.next(1, maxLeftLen);
        int rightLen = rnd.next(1, maxRightLen);
        int start = peak - leftLen * upStep;
        int finish = peak - rightLen * downStep;
        if (start <= 0 || finish < 0) continue;

        string s;
        for (int d = start; d < peak; d += upStep) s += char('0' + d);
        s += char('0' + peak);
        for (int d = peak - downStep; d >= finish; d -= downStep) s += char('0' + d);
        if ((int)s.size() >= 3) return s;
    }
    return "121";
}

string makeRandomDigits(int n, int lo, int hi) {
    string s;
    s += char('0' + rnd.next(max(1, lo), hi));
    for (int i = 1; i < n; ++i) s += char('0' + rnd.next(lo, hi));
    return s;
}

string makeSlopeChange() {
    string candidates[] = {"12420", "136520", "135420", "642135", "13531", "24631"};
    string s = candidates[rnd.next(0, 5)];
    if (rnd.next(0, 1)) reverse(s.begin(), s.end());
    if (s[0] == '0') s[0] = char('1' + rnd.next(0, 8));
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 7);
    string x;

    if (mode == 0) {
        x = makeAlpsoo();
    } else if (mode == 1) {
        x = makeRandomDigits(rnd.next(3, 24), 0, 9);
    } else if (mode == 2) {
        x = makeRandomDigits(rnd.next(3, 18), 0, 2);
    } else if (mode == 3) {
        x = makeRandomDigits(rnd.next(3, 18), 1, 2);
    } else if (mode == 4) {
        x = makeRandomDigits(rnd.next(3, 20), 0, 9);
        int pos = rnd.next(1, (int)x.size() - 1);
        x[pos] = x[pos - 1];
    } else if (mode == 5) {
        x = makeSlopeChange();
    } else if (mode == 6) {
        int n = rnd.next(3, 30);
        int first = rnd.next(2, 9);
        x += char('0' + first);
        x += char('0' + rnd.next(0, first - 1));
        while ((int)x.size() < n) x += char('0' + rnd.next(0, 9));
    } else {
        int n = rnd.next(50, 200);
        x = makeRandomDigits(n, 0, 9);
    }

    println(x);
    return 0;
}

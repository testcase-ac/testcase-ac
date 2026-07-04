#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

const long long LIMIT = 1000000000000LL;

void addLucky(long long value, vector<long long>& out) {
    if (value > LIMIT) return;
    if (value > 0) out.push_back(value);
    addLucky(value * 10 + 4, out);
    addLucky(value * 10 + 7, out);
}

long long clampValue(long long value) {
    return max(1LL, min(LIMIT, value));
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<long long> anchors;
    addLucky(0, anchors);

    vector<long long> smallLucky = {4, 7, 44, 47, 74, 77, 444, 447, 474, 477};
    for (long long x : smallLucky) {
        long long product = x;
        for (int k = 0; k < 5 && product <= LIMIT / x; ++k) {
            product *= x;
            anchors.push_back(product);
        }
    }

    anchors.push_back(1);
    anchors.push_back(2);
    anchors.push_back(3);
    anchors.push_back(16);
    anchors.push_back(28);
    anchors.push_back(49);
    anchors.push_back(112);
    anchors.push_back(999999999999LL);
    anchors.push_back(LIMIT);

    sort(anchors.begin(), anchors.end());
    anchors.erase(unique(anchors.begin(), anchors.end()), anchors.end());

    int mode = rnd.next(0, 6);
    int T;
    if (mode == 6) {
        T = rnd.next(100, 350);
    } else {
        T = rnd.next(1, 45);
    }

    println(T);
    for (int tc = 0; tc < T; ++tc) {
        int caseMode = rnd.next(0, 7);
        long long A, B;

        if (caseMode == 0) {
            long long center = rnd.any(anchors);
            long long radius = rnd.next(0LL, 30LL);
            A = clampValue(center - radius);
            B = clampValue(center + radius);
        } else if (caseMode == 1) {
            A = B = rnd.any(anchors);
        } else if (caseMode == 2) {
            A = rnd.next(1LL, 200LL);
            B = rnd.next(A, min(LIMIT, A + rnd.next(0LL, 300LL)));
        } else if (caseMode == 3) {
            A = rnd.next(1LL, LIMIT);
            long long width = rnd.next(0LL, 1000000LL);
            B = rnd.next(A, min(LIMIT, A + width));
        } else if (caseMode == 4) {
            B = LIMIT - rnd.next(0LL, 1000LL);
            A = rnd.next(max(1LL, B - rnd.next(0LL, 1000LL)), B);
        } else if (caseMode == 5) {
            long long len = rnd.next(0LL, 5000LL);
            A = rnd.next(1LL, LIMIT - len);
            B = A + len;
        } else if (caseMode == 6) {
            long long lowPower = rnd.next(0, 11);
            long long base = 1;
            for (int i = 0; i < lowPower; ++i) base *= 10;
            A = max(1LL, base - rnd.next(0LL, min(999LL, base - 1)));
            B = min(LIMIT, base + rnd.next(0LL, 999LL));
        } else {
            A = rnd.next(1LL, LIMIT);
            B = A;
        }

        if (A > B) swap(A, B);
        println(A, B);
    }

    return 0;
}

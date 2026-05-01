#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    auto toMin = [](int H, int M) {
        return H * 60 + M;
    };
    auto fromMin = [](int T) {
        return make_pair(T / 60, T % 60);
    };

    int H1, M1, H2, M2;
    int N;

    // Choose a scenario for diversity
    int scenario = rnd.next(1, 7);

    // Digit selection biased to expose edge cases (0 and small digits)
    auto pickDigit = [&]() -> int {
        int r = rnd.next(0, 9);
        if (r < 3) return 0;           // 30%: digit 0 (leading zero issues)
        if (r < 6) return rnd.next(1, 3); // 30%: digits 1-3
        return rnd.next(0, 9);         // 40%: any digit
    };

    if (scenario == 1) {
        // Same start and end time
        H1 = rnd.next(0, 23);
        M1 = rnd.next(0, 59);
        H2 = H1;
        M2 = M1;
        N = pickDigit();
    } else if (scenario == 2) {
        // Very small interval (0~5 minutes)
        int t1 = rnd.next(0, 24 * 60 - 1 - 5);
        int len = rnd.next(0, 5);
        int t2 = t1 + len;
        auto s = fromMin(t1);
        auto e = fromMin(t2);
        H1 = s.first; M1 = s.second;
        H2 = e.first; M2 = e.second;
        N = pickDigit();
    } else if (scenario == 3) {
        // Around midnight early times: 00:xx to 0y:zz
        int startMin = rnd.next(0, 59);           // 00:00 ~ 00:59
        int endMin = rnd.next(startMin, min(startMin + 120, 23 * 60 + 59)); // up to +2h
        auto s = fromMin(startMin);
        auto e = fromMin(endMin);
        H1 = s.first; M1 = s.second;
        H2 = e.first; M2 = e.second;
        N = pickDigit();
    } else if (scenario == 4) {
        // Near the end of day: late evening
        int startMin = rnd.next(22 * 60, 23 * 60 + 59); // 22:00 ~ 23:59
        int endMin = rnd.next(startMin, 23 * 60 + 59);  // until 23:59
        auto s = fromMin(startMin);
        auto e = fromMin(endMin);
        H1 = s.first; M1 = s.second;
        H2 = e.first; M2 = e.second;
        N = pickDigit();
    } else if (scenario == 5) {
        // Crossing an hour boundary tightly, e.g. 12:58 ~ 13:02
        int h = rnd.next(0, 22); // ensure h+1 exists
        int m1 = rnd.next(50, 59);
        int m2 = rnd.next(0, 10);
        int t1 = toMin(h, m1);
        int t2 = toMin(h + 1, m2);
        if (t2 < t1) t2 = t1; // just in case
        auto s = fromMin(t1);
        auto e = fromMin(t2);
        H1 = s.first; M1 = s.second;
        H2 = e.first; M2 = e.second;
        N = pickDigit();
    } else if (scenario == 6) {
        // Entire day
        H1 = 0; M1 = 0;
        H2 = 23; M2 = 59;
        N = pickDigit();
    } else {
        // General random interval of medium/long length
        int t1 = rnd.next(0, 24 * 60 - 1);
        int t2 = rnd.next(0, 24 * 60 - 1);
        if (t1 > t2) swap(t1, t2);
        auto s = fromMin(t1);
        auto e = fromMin(t2);
        H1 = s.first; M1 = s.second;
        H2 = e.first; M2 = e.second;
        N = pickDigit();
    }

    println(H1, M1);
    println(H2, M2);
    println(N);

    return 0;
}

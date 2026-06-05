#include "testlib.h"

#include <numeric>
#include <set>
#include <tuple>
#include <vector>

using namespace std;

using Line = tuple<long long, long long, long long>;

Line normalizeLine(long long a, long long b, long long c) {
    long long g = gcd(gcd(llabs(a), llabs(b)), llabs(c));
    a /= g;
    b /= g;
    c /= g;

    if (a < 0 || (a == 0 && b < 0) || (a == 0 && b == 0 && c < 0)) {
        a = -a;
        b = -b;
        c = -c;
    }

    return {a, b, c};
}

void addLine(vector<Line>& lines, set<Line>& seen, long long a, long long b, long long c) {
    if (a == 0 && b == 0) return;

    Line normalized = normalizeLine(a, b, c);
    if (seen.insert(normalized).second) lines.push_back({a, b, c});
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 4);
    int n = rnd.next(1, 30);
    vector<Line> lines;
    set<Line> seen;

    if (mode == 0) {
        n = rnd.next(1, 8);
    } else if (mode == 1) {
        n = rnd.next(8, 25);
    } else {
        n = rnd.next(12, 30);
    }

    if (mode == 0 || mode == 3) {
        addLine(lines, seen, 0, 1, rnd.next(-20, 20));
        addLine(lines, seen, 1, 0, rnd.next(-20, 20));
    }

    if (mode == 1 || mode == 3) {
        int familyCount = rnd.next(2, 5);
        for (int family = 0; family < familyCount && (int)lines.size() < n; ++family) {
            long long a = rnd.next(-8, 8);
            long long b = rnd.next(-8, 8);
            if (a == 0 && b == 0) b = 1;

            int perFamily = rnd.next(2, 8);
            for (int i = 0; i < perFamily && (int)lines.size() < n; ++i) {
                addLine(lines, seen, a, b, rnd.next(-50, 50));
            }
        }
    }

    while ((int)lines.size() < n) {
        long long a, b, c;
        if (mode == 2 && rnd.next(0, 4) == 0) {
            a = rnd.next(-1000000000LL, 1000000000LL);
            b = rnd.next(-1000000000LL, 1000000000LL);
            c = rnd.next(-1000000000LL, 1000000000LL);
        } else {
            a = rnd.next(-30, 30);
            b = rnd.next(-30, 30);
            c = rnd.next(-100, 100);
        }

        if (a == 0 && b == 0) a = 1;
        addLine(lines, seen, a, b, c);
    }

    shuffle(lines.begin(), lines.end());

    println((int)lines.size());
    for (auto [a, b, c] : lines) {
        println(a, b, c);
    }

    return 0;
}

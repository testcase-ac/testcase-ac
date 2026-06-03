#include "testlib.h"

#include <algorithm>
#include <tuple>

using namespace std;

tuple<int, int, int> splitSum(int total) {
    int loA = max(1, total - 2 * 738);
    int hiA = min(738, total - 2);
    int a = rnd.next(loA, hiA);

    int rest = total - a;
    int loB = max(1, rest - 738);
    int hiB = min(738, rest - 1);
    int b = rnd.next(loB, hiB);
    int c = rest - b;

    return {a, b, c};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int s;
    int flightTotal;
    int mode = rnd.next(0, 5);

    if (mode == 0) {
        s = rnd.next(1, 240);
        flightTotal = rnd.next(3, 2214);
    } else if (mode == 1) {
        s = rnd.next(241, 738);
        flightTotal = rnd.next(s, 2214);
    } else if (mode == 2) {
        s = rnd.next(241, 738);
        flightTotal = rnd.next(3, s - 1);
    } else if (mode == 3) {
        s = rnd.next(3, 738);
        flightTotal = s;
    } else if (mode == 4) {
        s = rnd.any(vector<int>{1, 240, 241, 738});
        flightTotal = rnd.any(vector<int>{3, 240, 241, 738, 2214});
    } else {
        s = rnd.next(1, 738);
        flightTotal = rnd.next(3, 2214);
    }

    auto [ma, f, mb] = splitSum(flightTotal);

    println(s);
    println(ma, f, mb);

    return 0;
}

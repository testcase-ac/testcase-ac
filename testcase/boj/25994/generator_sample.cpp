#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string formatProbability(long long scaled, int digits) {
    string fraction = to_string(scaled);
    while ((int)fraction.size() < digits) {
        fraction = "0" + fraction;
    }
    return "0." + fraction;
}

string randomProbability() {
    int mode = rnd.next(0, 5);
    if (mode == 0) return "0.001";
    if (mode == 1) return "0.999";
    if (mode == 2) return "0.5";

    int digits = rnd.next(3, 10);
    long long scale = 1;
    for (int i = 0; i < digits; ++i) {
        scale *= 10;
    }

    long long low = (scale + 999) / 1000;
    long long high = scale * 999 / 1000;
    long long scaled = rnd.next(low, high);
    return formatProbability(scaled, digits);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    int c;
    long long t;
    long long r;

    if (mode == 0) {
        c = rnd.next(1, 8);
        t = rnd.next(0, 20);
        r = rnd.next(0, 20);
    } else if (mode == 1) {
        c = rnd.next(1000, 2000);
        t = rnd.next(0, 1000000000);
        r = rnd.next(0, 1000000000);
    } else if (mode == 2) {
        c = rnd.next(1, 2000);
        t = 0;
        r = rnd.next(0, 1000000000);
    } else if (mode == 3) {
        c = rnd.next(1, 2000);
        t = rnd.next(0, 1000000000);
        r = 0;
    } else if (mode == 4) {
        c = rnd.any(vector<int>{1, 2, 1999, 2000});
        t = rnd.any(vector<long long>{0, 1, 1000000000LL});
        r = rnd.any(vector<long long>{0, 1, 1000000000LL});
    } else {
        c = rnd.next(1, 2000);
        t = rnd.next(0, 1000000000);
        r = rnd.next(0, 1000000000);
    }

    println(c, t, r);
    println(randomProbability());

    return 0;
}

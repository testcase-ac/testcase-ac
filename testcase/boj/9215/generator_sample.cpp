#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string whole() {
    if (rnd.next(0, 5) == 0) {
        return "0";
    }
    return to_string(rnd.next(0, 999));
}

string fraction(bool allowImproper) {
    int d = rnd.next(1, 999);
    int n = allowImproper ? rnd.next(0, 999) : rnd.next(0, d - 1);
    return to_string(n) + "/" + to_string(d);
}

string scaledFraction() {
    int baseD = rnd.next(1, 99);
    int baseN = rnd.next(0, baseD);
    int limit = 999 / max(baseD, max(1, baseN));
    int scale = rnd.next(1, max(1, limit));
    return to_string(baseN * scale) + "/" + to_string(baseD * scale);
}

string mixed() {
    int w = rnd.next(0, 999);
    int d = rnd.next(1, 999);
    int n = rnd.next(0, 999);
    return to_string(w) + "," + to_string(n) + "/" + to_string(d);
}

string boundaryValue() {
    const vector<string> values = {
        "0",
        "999",
        "0/1",
        "1/999",
        "999/1",
        "999/999",
        "0,0/1",
        "0,999/999",
        "999,0/1",
        "999,999/999",
    };
    return rnd.any(values);
}

string randomRational(int mode) {
    if (mode == 0) {
        return whole();
    }
    if (mode == 1) {
        return fraction(false);
    }
    if (mode == 2) {
        return fraction(true);
    }
    if (mode == 3) {
        return scaledFraction();
    }
    if (mode == 4) {
        return mixed();
    }
    return boundaryValue();
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int tests = rnd.next(3, 8);
    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 5);
        int n = rnd.next(1, mode == 5 ? 8 : 25);
        println(n);

        for (int i = 0; i < n; ++i) {
            int valueMode = mode;
            if (rnd.next(0, 3) == 0) {
                valueMode = rnd.next(0, 5);
            }
            println(randomRational(valueMode));
        }
    }

    println(0);
    return 0;
}

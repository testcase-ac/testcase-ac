#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string formatProbability(int cents) {
    if (cents == 0) return "0";
    if (cents == 100) return "1";

    int tenths = cents / 10;
    int hundredths = cents % 10;
    if (hundredths == 0 && rnd.next(2) == 0) {
        return "0." + to_string(tenths);
    }
    return "0." + to_string(tenths) + to_string(hundredths);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> probs(3, 0);
    int mode = rnd.next(6);

    if (mode == 0) {
        probs[rnd.next(3)] = 100;
    } else if (mode == 1) {
        int zero = rnd.next(3);
        int first = (zero + 1 + rnd.next(2)) % 3;
        probs[first] = rnd.next(1, 99);
        probs[3 - zero - first] = 100 - probs[first];
    } else if (mode == 2) {
        probs = {33, 33, 34};
        shuffle(probs.begin(), probs.end());
    } else if (mode == 3) {
        int heavy = rnd.next(3);
        probs[heavy] = rnd.next(80, 99);
        int rest = 100 - probs[heavy];
        int second = (heavy + 1 + rnd.next(2)) % 3;
        probs[second] = rnd.next(0, rest);
        probs[3 - heavy - second] = rest - probs[second];
    } else if (mode == 4) {
        int a = rnd.next(20, 45);
        int b = rnd.next(20, 45);
        int c = 100 - a - b;
        probs = {a, b, c};
        shuffle(probs.begin(), probs.end());
    } else {
        int a = rnd.next(0, 100);
        int b = rnd.next(0, 100 - a);
        probs = {a, b, 100 - a - b};
        shuffle(probs.begin(), probs.end());
    }

    println(formatProbability(probs[0]), formatProbability(probs[1]), formatProbability(probs[2]));
    return 0;
}

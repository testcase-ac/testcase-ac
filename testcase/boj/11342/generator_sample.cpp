#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

vector<string> makeOpenFrame() {
    int first = rnd.next(0, 9);
    int second = rnd.next(0, 9 - first);
    if (first + second == 10) --second;
    return {to_string(first), to_string(second)};
}

vector<string> makeSpareFrame() {
    return {to_string(rnd.next(0, 9)), "/"};
}

vector<string> makeRegularFrame() {
    int mode = rnd.next(0, 99);
    if (mode < 30) return {"X"};
    if (mode < 60) return makeSpareFrame();
    return makeOpenFrame();
}

vector<string> makeTenthFrame() {
    int mode = rnd.next(0, 6);
    if (mode == 0) {
        return {"X", "X", rnd.next(0, 1) == 0 ? string("X") : to_string(rnd.next(0, 9))};
    }
    if (mode == 1) {
        int second = rnd.next(0, 9);
        if (rnd.next(0, 1) == 0) return {"X", to_string(second), "/"};
        int third = rnd.next(0, 9 - second);
        if (second + third == 10) --third;
        return {"X", to_string(second), to_string(third)};
    }
    if (mode == 2) {
        return {to_string(rnd.next(0, 9)), "/", rnd.next(0, 1) == 0 ? string("X") : to_string(rnd.next(0, 9))};
    }
    return makeOpenFrame();
}

vector<string> makeGame() {
    vector<string> tokens;
    int profile = rnd.next(0, 4);
    for (int frame = 1; frame <= 9; ++frame) {
        vector<string> part;
        if (profile == 0 && rnd.next(0, 99) < 75) {
            part = {"X"};
        } else if (profile == 1 && rnd.next(0, 99) < 75) {
            part = makeSpareFrame();
        } else if (profile == 2 && rnd.next(0, 99) < 75) {
            part = makeOpenFrame();
        } else if (profile == 3) {
            if (frame % 3 == 1) part = {"X"};
            else if (frame % 3 == 2) part = makeSpareFrame();
            else part = makeOpenFrame();
        } else {
            part = makeRegularFrame();
        }
        tokens.insert(tokens.end(), part.begin(), part.end());
    }

    vector<string> tenth = makeTenthFrame();
    tokens.insert(tokens.end(), tenth.begin(), tenth.end());
    return tokens;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(1, 8);
    println(t);
    for (int caseIndex = 0; caseIndex < t; ++caseIndex) {
        vector<string> game = makeGame();
        println(game);
    }

    return 0;
}

#include "testlib.h"
#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string repeated(char c, int count) {
    return string(count, c);
}

string rectangleLoop(int width, int height, int rounds) {
    string commands;
    for (int i = 0; i < rounds; ++i) {
        commands += repeated('E', width);
        commands += repeated('S', height);
        commands += repeated('W', width);
        commands += repeated('N', height);
    }
    return commands;
}

string immediateBacktracks(int pairs) {
    string commands;
    const vector<string> options = {"EW", "WE", "NS", "SN"};
    for (int i = 0; i < pairs; ++i) commands += rnd.any(options);
    return commands;
}

string biasedWalk(int length) {
    string commands;
    string alphabet = rnd.any(vector<string>{"EEEW", "WWWE", "NNNS", "SSSN"});
    for (int i = 0; i < length; ++i) commands += rnd.any(alphabet);
    return commands;
}

string randomWalk(int length) {
    string commands;
    const string alphabet = "EWSN";
    for (int i = 0; i < length; ++i) commands += rnd.any(alphabet);
    return commands;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    string commands;

    if (mode == 0) {
        commands = repeated(rnd.any(string("EWSN")), rnd.next(1, 80));
    } else if (mode == 1) {
        commands = immediateBacktracks(rnd.next(1, 50));
    } else if (mode == 2) {
        int width = rnd.next(1, 12);
        int height = rnd.next(1, 12);
        int rounds = rnd.next(1, max(1, 120 / (2 * (width + height))));
        commands = rectangleLoop(width, height, rounds);
    } else if (mode == 3) {
        commands = biasedWalk(rnd.next(1, 160));
    } else if (mode == 4) {
        commands = rectangleLoop(rnd.next(1, 8), rnd.next(1, 8), rnd.next(1, 4));
        commands += immediateBacktracks(rnd.next(1, 20));
        commands += biasedWalk(rnd.next(1, 60));
        shuffle(commands.begin(), commands.end());
    } else {
        commands = randomWalk(rnd.next(1, 200));
    }

    if ((int)commands.size() > 1000) commands.resize(1000);

    println((int)commands.size());
    println(commands);
    return 0;
}

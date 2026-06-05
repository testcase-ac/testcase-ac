#include "testlib.h"

#include <string>

using namespace std;

int rollValue(char c) {
    if (c == '-') return 0;
    if ('1' <= c && c <= '9') return c - '0';
    return -1;
}

void requireRoll(char c, int index) {
    ensuref(c == '-' || ('1' <= c && c <= '9'),
            "roll %d must be '-' or a digit from 1 to 9, found '%c'", index + 1, c);
}

void requireOpenPair(char first, char second, int frame) {
    requireRoll(first, 2 * frame - 2);
    if (second == 'P') return;

    requireRoll(second, 2 * frame - 1);
    ensuref(rollValue(first) + rollValue(second) < 10,
            "frame %d open rolls must knock down fewer than 10 pins", frame);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string score = inf.readLine("[SP1-9\\-]{11,21}", "score");

    int pos = 0;
    for (int frame = 1; frame <= 9; ++frame) {
        ensuref(pos < int(score.size()), "missing frame %d", frame);
        if (score[pos] == 'S') {
            ++pos;
            continue;
        }

        ensuref(pos + 1 < int(score.size()), "missing second roll in frame %d", frame);
        requireOpenPair(score[pos], score[pos + 1], frame);
        pos += 2;
    }

    ensuref(pos < int(score.size()), "missing frame 10");
    char first = score[pos++];
    if (first == 'S') {
        ensuref(pos + 1 < int(score.size()), "frame 10 strike requires two bonus rolls");
        char bonus1 = score[pos++];
        char bonus2 = score[pos++];

        if (bonus1 == 'S') {
            ensuref(bonus2 != 'P', "second bonus after consecutive strikes cannot be spare");
            if (bonus2 != 'S') requireRoll(bonus2, pos - 1);
        } else {
            requireOpenPair(bonus1, bonus2, 10);
        }
    } else {
        ensuref(pos < int(score.size()), "missing second roll in frame 10");
        char second = score[pos++];
        requireOpenPair(first, second, 10);

        if (second == 'P') {
            ensuref(pos < int(score.size()), "frame 10 spare requires one bonus roll");
            char bonus = score[pos++];
            ensuref(bonus != 'P', "bonus roll after frame 10 spare cannot be spare");
            if (bonus != 'S') requireRoll(bonus, pos - 1);
        }
    }

    ensuref(pos == int(score.size()), "extra rolls after complete game");
    inf.readEof();
}

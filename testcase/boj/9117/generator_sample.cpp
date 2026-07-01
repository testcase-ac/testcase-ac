#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

const string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

char randomColor(const string& palette) {
    return palette[rnd.next(int(palette.size()))];
}

string randomColors(int length, const string& palette) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) result += randomColor(palette);
    return result;
}

char differentColor(char c, const string& palette) {
    char result = c;
    while (result == c) result = randomColor(palette);
    return result;
}

struct CaseData {
    string target;
    string visible;
    string hidden;
};

CaseData makeGuaranteedWin(const string& palette) {
    int targetLength = rnd.next(1, 14);
    int rowLength = rnd.next(targetLength, min(28, targetLength + 12));
    string target = randomColors(targetLength, palette);
    string visible = randomColors(rowLength, palette);
    string hidden = randomColors(rowLength, palette);

    vector<int> positions(rowLength);
    for (int i = 0; i < rowLength; ++i) positions[i] = i;
    shuffle(positions.begin(), positions.end());
    positions.resize(targetLength);
    sort(positions.begin(), positions.end());

    for (int i = 0; i < targetLength; ++i) {
        int pos = positions[i];
        int mode = rnd.next(0, 2);
        if (mode == 0) {
            visible[pos] = target[i];
        } else if (mode == 1) {
            hidden[pos] = target[i];
        } else {
            visible[pos] = hidden[pos] = '*';
        }
    }

    return {target, visible, hidden};
}

CaseData makeForcedLoss(const string& palette) {
    int targetLength = rnd.next(4, 18);
    int rowLength = rnd.next(1, targetLength - 1);
    string target = randomColors(targetLength, palette);
    string visible = randomColors(rowLength, palette);
    string hidden = randomColors(rowLength, palette);

    for (int i = 0; i < rowLength; ++i) {
        if (rnd.next(0, 5) == 0) {
            visible[i] = hidden[i] = '*';
        } else {
            visible[i] = randomColor(palette);
            hidden[i] = randomColor(palette);
        }
    }

    return {target, visible, hidden};
}

CaseData makeSingleCardEdge(const string& palette) {
    string target(1, randomColor(palette));
    string visible(1, randomColor(palette));
    string hidden(1, randomColor(palette));

    int mode = rnd.next(0, 4);
    if (mode == 0) {
        visible[0] = target[0];
    } else if (mode == 1) {
        hidden[0] = target[0];
    } else if (mode == 2) {
        visible[0] = hidden[0] = '*';
    } else {
        visible[0] = differentColor(target[0], palette);
        hidden[0] = differentColor(target[0], palette);
    }

    return {target, visible, hidden};
}

CaseData makeJokerPattern(const string& palette) {
    int targetLength = rnd.next(3, 16);
    int rowLength = rnd.next(targetLength, 28);
    string target = randomColors(targetLength, palette);
    string visible;
    string hidden;
    visible.reserve(rowLength);
    hidden.reserve(rowLength);

    for (int i = 0; i < rowLength; ++i) {
        if (rnd.next(0, 2) == 0) {
            visible += '*';
            hidden += '*';
        } else {
            visible += randomColor(palette);
            hidden += randomColor(palette);
        }
    }

    return {target, visible, hidden};
}

CaseData makeNearMiss(const string& palette) {
    int targetLength = rnd.next(5, 18);
    int rowLength = rnd.next(targetLength - 1, targetLength + 8);
    string target = randomColors(targetLength, palette);
    string visible(rowLength, target[0]);
    string hidden(rowLength, target[0]);
    char missing = target[targetLength / 2];

    for (int i = 0; i < rowLength; ++i) {
        visible[i] = differentColor(missing, palette);
        hidden[i] = differentColor(missing, palette);
        if (rnd.next(0, 8) == 0) visible[i] = randomColor(palette);
        if (rnd.next(0, 8) == 0) hidden[i] = randomColor(palette);
    }

    return {target, visible, hidden};
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int paletteSize = rnd.next(2, 8);
    string palette = ALPHABET.substr(0, paletteSize);
    int tests = rnd.next(8, 18);
    println(tests);

    for (int tc = 0; tc < tests; ++tc) {
        int mode = rnd.next(0, 4);
        CaseData data;
        if (mode == 0) {
            data = makeGuaranteedWin(palette);
        } else if (mode == 1) {
            data = makeForcedLoss(palette);
        } else if (mode == 2) {
            data = makeSingleCardEdge(palette);
        } else if (mode == 3) {
            data = makeJokerPattern(palette);
        } else {
            data = makeNearMiss(palette);
        }

        println(data.target);
        println(data.visible);
        println(data.hidden);
    }
}

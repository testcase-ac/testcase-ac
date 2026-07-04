#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

string makeName(int index, int style) {
    if (style == 0) {
        return string(1, char('A' + index));
    }
    if (style == 1) {
        return "P" + to_string(index + 1);
    }
    return "Player_" + to_string(index + 1);
}

string alternatingScores(int length) {
    string scores;
    char current = rnd.next(0, 1) == 0 ? 'W' : 'B';
    for (int i = 0; i < length; ++i) {
        scores += current;
        current = current == 'W' ? 'B' : 'W';
    }
    return scores;
}

string runBasedScores(int targetLength, int maxRun) {
    string scores;
    char current = rnd.next(0, 1) == 0 ? 'W' : 'B';
    while (int(scores.size()) < targetLength) {
        int runLength = rnd.next(1, maxRun);
        for (int i = 0; i < runLength && int(scores.size()) < targetLength; ++i) {
            scores += current;
        }
        current = current == 'W' ? 'B' : 'W';
    }
    return scores;
}

string biasedScores(int length) {
    string scores;
    char favored = rnd.next(0, 1) == 0 ? 'W' : 'B';
    int favoredPercent = rnd.next(60, 85);
    for (int i = 0; i < length; ++i) {
        bool useFavored = rnd.next(1, 100) <= favoredPercent;
        scores += useFavored ? favored : (favored == 'W' ? 'B' : 'W');
    }
    return scores;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(5, 10);
    int nameStyle = rnd.next(0, 2);
    vector<string> names;
    for (int i = 0; i < n; ++i) {
        names.push_back(makeName(i, nameStyle));
    }
    shuffle(names.begin(), names.end());

    int length = rnd.next(1, 40);
    int mode = rnd.next(0, 4);
    string scores;
    if (mode == 0) {
        scores = string(length, rnd.next(0, 1) == 0 ? 'W' : 'B');
    } else if (mode == 1) {
        scores = alternatingScores(length);
    } else if (mode == 2) {
        scores = runBasedScores(length, rnd.next(2, 8));
    } else if (mode == 3) {
        scores = biasedScores(length);
    } else {
        scores = runBasedScores(length, rnd.next(1, 4));
    }

    println(n);
    println(names);
    println(scores);

    return 0;
}

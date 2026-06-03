#include "testlib.h"

#include <array>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readSpace();
    int m = inf.readInt(1, n, "m");
    inf.readEoln();

    vector<int> correct = inf.readInts(n, 1, 5, "correct_i");
    inf.readEoln();

    vector<bool> guessedCorrect(n, false);
    for (int i = 0; i < m; ++i) {
        if (i > 0) {
            inf.readSpace();
        }
        int index = inf.readInt(1, n, "guessed_correct_i");
        ensuref(!guessedCorrect[index - 1],
                "duplicate correctly guessed problem index: %d", index);
        guessedCorrect[index - 1] = true;
    }
    inf.readEoln();

    array<bool, 6> possible{};
    for (int answer = 1; answer <= 5; ++answer) {
        possible[answer] = guessedCorrect[0] ? answer == correct[0] : answer != correct[0];
    }

    for (int i = 1; i < n; ++i) {
        array<bool, 6> next{};
        for (int answer = 1; answer <= 5; ++answer) {
            if (guessedCorrect[i] && answer != correct[i]) {
                continue;
            }
            if (!guessedCorrect[i] && answer == correct[i]) {
                continue;
            }
            for (int previous = 1; previous <= 5; ++previous) {
                if (previous != answer && possible[previous]) {
                    next[answer] = true;
                    break;
                }
            }
        }
        possible = next;
    }

    bool hasSolution = false;
    for (int answer = 1; answer <= 5; ++answer) {
        hasSolution = hasSolution || possible[answer];
    }
    ensuref(hasSolution, "no answer sequence satisfies correctness and adjacent-difference constraints");

    inf.readEof();
}

#include "testlib.h"

#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    vector<int> scores;
    scores.reserve(50);
    for (int i = 0; i < 50; ++i) {
        int score = inf.readInt(0, 300, "score");
        if (i + 1 < 50) {
            inf.readSpace();
        } else {
            inf.readEoln();
        }

        if (i > 0) {
            ensuref(scores.back() > score,
                    "scores must be strictly descending: score[%d]=%d, score[%d]=%d",
                    i, scores.back(), i + 1, score);
        }
        scores.push_back(score);
    }

    int hongik = inf.readInt(0, 300, "hongik");
    inf.readEoln();

    bool found = false;
    for (int score : scores) {
        if (score == hongik) {
            found = true;
            break;
        }
    }
    ensuref(found, "Hongik's score %d must be one of the 50 listed scores", hongik);

    inf.readEof();
}

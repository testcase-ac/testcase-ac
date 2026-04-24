#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Number of classes
    int K = inf.readInt(1, 100, "K");
    inf.readEoln();

    // For each class, read student count and scores
    for (int i = 1; i <= K; i++) {
        int N = inf.readInt(2, 50, "N");
        // There must be exactly N scores after N, separated by single spaces
        for (int j = 0; j < N; j++) {
            inf.readSpace();
            inf.readInt(0, 100, "score");
        }
        inf.readEoln();
    }

    inf.readEof();
    return 0;
}

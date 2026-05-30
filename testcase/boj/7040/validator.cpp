#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(2, 1000, "N");
    inf.readSpace();
    int ML = inf.readInt(1, 10000, "ML");
    inf.readSpace();
    int MD = inf.readInt(1, 10000, "MD");
    inf.readEoln();

    for (int i = 0; i < ML; i++) {
        int A = inf.readInt(1, N - 1, "like_A");
        inf.readSpace();
        int B = inf.readInt(1, N, "like_B");
        inf.readSpace();
        int D = inf.readInt(1, 1000000, "like_D");
        inf.readEoln();

        ensuref(A < B,
                "In like-constraint #%d: require A < B, but got A=%d, B=%d",
                i + 1, A, B);
    }

    for (int i = 0; i < MD; i++) {
        int A = inf.readInt(1, N - 1, "dislike_A");
        inf.readSpace();
        int B = inf.readInt(1, N, "dislike_B");
        inf.readSpace();
        int D = inf.readInt(1, 1000000, "dislike_D");
        inf.readEoln();

        ensuref(A < B,
                "In dislike-constraint #%d: require A < B, but got A=%d, B=%d",
                i + 1, A, B);
    }

    inf.readEof();
    return 0;
}

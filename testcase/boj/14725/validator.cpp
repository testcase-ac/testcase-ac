#include "testlib.h"

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int N = inf.readInt(1, 1000, "N");
    inf.readEoln();

    for (int i = 0; i < N; i++) {
        int K = inf.readInt(1, 15, "K");
        for (int j = 0; j < K; j++) {
            inf.readSpace();
            inf.readToken("[A-Z]{1,15}", "food");
        }
        inf.readEoln();
    }

    inf.readEof();
}

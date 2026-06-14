#include "testlib.h"

namespace {

constexpr int kMaxDatasets = 100;
constexpr int kMaxCards = 500;
constexpr int kMinValue = 2;
constexpr int kMaxValue = 9999999;

void readSpaceOrEoln() {
    char separator = inf.readChar();
    ensuref(separator == ' ' || separator == '\n',
            "expected space or newline between card values");
}

}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int datasets = 0;
    while (true) {
        int m = inf.readInt(0, kMaxCards, "m");
        inf.readSpace();
        int n = inf.readInt(0, kMaxCards, "n");
        inf.readEoln();

        if (m == 0 && n == 0) {
            break;
        }

        ++datasets;
        ensuref(datasets <= kMaxDatasets,
                "number of datasets exceeds %d", kMaxDatasets);
        ensuref(m >= 1 && n >= 1,
                "non-terminating dataset has m=%d and n=%d", m, n);

        int total_cards = m + n;
        for (int i = 0; i < total_cards; ++i) {
            inf.readInt(kMinValue, kMaxValue, i < m ? "b_i" : "r_i");
            if (i + 1 == total_cards) {
                inf.readEoln();
            } else {
                readSpaceOrEoln();
            }
        }
    }

    inf.readEof();
}

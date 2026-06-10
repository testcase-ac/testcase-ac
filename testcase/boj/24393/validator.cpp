#include "testlib.h"

#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    const int deckSize = 27;
    const int leftSize = 13;
    const int rightSize = 14;
    const int maxN = 1000000;
    const int maxIntegers = 10000001;

    int n = inf.readInt(1, maxN, "N");
    inf.readEoln();

    int integerCount = 1;
    for (int i = 1; i <= n; ++i) {
        string line = inf.readLine("[0-9\\ ]{1,80}", "A_i");

        ensuref(line.front() != ' ' && line.back() != ' ',
                "shuffle %d has leading or trailing space", i);
        ensuref(line.find("  ") == string::npos, "shuffle %d has repeated spaces", i);

        int oddSum = 0;
        int evenSum = 0;
        int termIndex = 1;
        size_t pos = 0;
        while (pos < line.size()) {
            size_t next = line.find(' ', pos);
            string token = line.substr(pos, next == string::npos ? string::npos : next - pos);

            ensuref(token == "0" || token[0] != '0',
                    "A_%d,%d has a leading zero: %s", i, termIndex, token.c_str());

            int value = 0;
            for (char ch : token) {
                value = value * 10 + (ch - '0');
            }
            ensuref(value >= 1 && value <= deckSize,
                    "A_%d,%d is out of range: %d", i, termIndex, value);

            if (termIndex % 2 == 1) {
                oddSum += value;
                ensuref(oddSum <= rightSize,
                        "odd-indexed sum exceeds %d in shuffle %d", rightSize, i);
            } else {
                evenSum += value;
                ensuref(evenSum <= leftSize,
                        "even-indexed sum exceeds %d in shuffle %d", leftSize, i);
            }

            ++termIndex;
            ++integerCount;
            ensuref(integerCount <= maxIntegers,
                    "total integer count exceeds %d", maxIntegers);

            if (next == string::npos) {
                break;
            }
            pos = next + 1;
        }

        ensuref(oddSum == rightSize,
                "odd-indexed sum must be %d in shuffle %d, got %d", rightSize, i, oddSum);
        ensuref(evenSum == leftSize,
                "even-indexed sum must be %d in shuffle %d, got %d", leftSize, i, evenSum);
    }

    inf.readEof();
    return 0;
}

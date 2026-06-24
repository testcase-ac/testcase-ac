#include "testlib.h"
#include <string>
#include <vector>
using namespace std;

int n;
string input;

int permutationSizeFromInputLength(int length) {
    if (length <= 9) {
        return length;
    }
    if ((length + 9) % 2 != 0) {
        quitf(_fail, "input length %d cannot represent a permutation of 1..N", length);
    }
    int result = (length + 9) / 2;
    if (result < 10 || result > 50) {
        quitf(_fail, "input length %d gives invalid N=%d", length, result);
    }
    return result;
}

void readAnswer(InStream& stream) {
    vector<int> used(n + 1, 0);
    string concatenated;

    for (int i = 0; i < n; ++i) {
        int value = stream.readInt(1, n, format("value[%d]", i + 1).c_str());
        if (used[value]) {
            stream.quitf(_wa, "value %d appears more than once", value);
        }
        used[value] = 1;
        concatenated += to_string(value);
    }

    if (!stream.seekEof()) {
        stream.quitf(_wa, "extra output after %d values", n);
    }

    if (concatenated != input) {
        stream.quitf(_wa, "concatenated output is '%s', expected '%s'",
                     concatenated.c_str(), input.c_str());
    }
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    input = inf.readToken("[0-9]+", "input");
    n = permutationSizeFromInputLength(int(input.size()));

    readAnswer(ans);
    readAnswer(ouf);

    quitf(_ok, "valid permutation of 1..%d", n);
}

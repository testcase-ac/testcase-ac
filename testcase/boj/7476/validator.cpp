#include "testlib.h"

#include <vector>

using namespace std;

namespace {
constexpr int kMaxLength = 500;
constexpr long long kMinValue = -(1LL << 31);
constexpr long long kMaxValue = (1LL << 31) - 1;

void readSequence(const char* lengthName, const char* valueName) {
    int n = inf.readInt(1, kMaxLength, lengthName);
    inf.readEoln();

    vector<long long> values = inf.readLongs(n, kMinValue, kMaxValue, valueName);
    (void)values;
    inf.readEoln();
}
}  // namespace

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    readSequence("m1", "a_i");
    readSequence("m2", "b_i");

    inf.readEof();
}

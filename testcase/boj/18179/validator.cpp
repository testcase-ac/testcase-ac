#include "testlib.h"

#include <array>
#include <string>

using namespace std;

array<int, 4> countBases(const string& s) {
    array<int, 4> counts{};
    for (char c : s) {
        if (c == 'A') {
            ++counts[0];
        } else if (c == 'C') {
            ++counts[1];
        } else if (c == 'G') {
            ++counts[2];
        } else {
            ++counts[3];
        }
    }
    return counts;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    string before = inf.readLine("[ACGT]{1,1000000}", "before");
    string after = inf.readLine("[ACGT]{1,1000000}", "after");
    inf.readEof();

    ensuref(before.size() == after.size(),
            "gene lengths differ: before=%zu after=%zu",
            before.size(), after.size());
    ensuref(countBases(before) == countBases(after),
            "nucleobase occurrence counts differ between strings");
}

#include "testlib.h"

#include <string>
#include <vector>
using namespace std;

namespace {

const string kInitials = "rsefaqtdwczxvg";
const string kMedials = "koijpuhynbml";
const string kFinals = "rsefaqtdwczxvg";

string randomSyllable(bool hasFinal) {
    string result;
    result += rnd.any(kInitials);
    result += rnd.any(kMedials);
    if (hasFinal) {
        result += rnd.any(kFinals);
    }
    return result;
}

}  // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 5);
    bool lastHasFinal = rnd.next(0, 1);
    int targetLength;

    if (mode == 0) {
        targetLength = lastHasFinal ? 3 : 2;
    } else if (mode == 1) {
        targetLength = rnd.next(2, 8);
    } else if (mode == 2) {
        targetLength = rnd.next(9, 18);
    } else if (mode == 3) {
        targetLength = rnd.next(19, 30);
    } else if (mode == 4) {
        targetLength = lastHasFinal ? 30 : 29;
    } else {
        targetLength = rnd.next(2, 30);
    }

    if (targetLength - (lastHasFinal ? 3 : 2) == 1) {
        targetLength += targetLength < 30 ? 1 : -1;
    }

    vector<bool> hasFinals;
    int remaining = targetLength - (lastHasFinal ? 3 : 2);
    while (remaining > 0) {
        bool hasFinal = remaining >= 3 && remaining != 4 && (remaining == 3 || rnd.next(0, 1));
        if (remaining == 2) {
            hasFinal = false;
        }
        hasFinals.push_back(hasFinal);
        remaining -= hasFinal ? 3 : 2;
    }
    hasFinals.push_back(lastHasFinal);

    string s;
    for (bool hasFinal : hasFinals) {
        s += randomSyllable(hasFinal);
    }

    println(int(s.size()));
    println(s);

    return 0;
}

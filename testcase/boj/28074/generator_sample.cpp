#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

string randomString(int length, const string& alphabet) {
    string result;
    result.reserve(length);
    for (int i = 0; i < length; ++i) {
        result += rnd.any(alphabet);
    }
    return result;
}

void addNoise(string& s, int targetLength, const string& alphabet) {
    while ((int)s.size() < targetLength) {
        s += rnd.any(alphabet);
    }
    shuffle(s.begin(), s.end());
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string required = "MOBIS";
    const string allLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    const string distractors = "ACDEFGHJKLNPQRTUVWXYZ";

    int mode = rnd.next(0, 5);
    string s;

    if (mode == 0) {
        s = required;
        addNoise(s, rnd.next(5, 25), allLetters);
    } else if (mode == 1) {
        s = required;
        addNoise(s, rnd.next(5, 100), distractors);
    } else if (mode == 2) {
        string missing = required;
        missing.erase(rnd.next(0, (int)missing.size() - 1), 1);
        s = missing;
        addNoise(s, rnd.next((int)s.size(), 25), distractors);
    } else if (mode == 3) {
        char repeated = rnd.any(required);
        s = string(rnd.next(1, 30), repeated);
        addNoise(s, rnd.next((int)s.size(), 40), distractors);
    } else if (mode == 4) {
        s = randomString(rnd.next(1, 30), allLetters);
    } else {
        s = required;
        addNoise(s, 100, allLetters);
    }

    println(s);
    return 0;
}

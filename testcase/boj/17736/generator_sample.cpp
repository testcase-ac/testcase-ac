#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>

using namespace std;

string randomJOI(int n) {
    string s;
    s.reserve(n);
    const string alphabet = "JOI";
    for (int i = 0; i < n; ++i) s.push_back(rnd.any(alphabet));
    return s;
}

string repeatChar(int n) {
    return string(n, rnd.any(string("JOI")));
}

string shuffledBalancedBlock(int copies) {
    string block;
    block.reserve(3 * copies);
    for (int i = 0; i < copies; ++i) {
        block += "JOI";
    }
    shuffle(block.begin(), block.end());
    return block;
}

string repeatedPattern() {
    vector<string> patterns = {
        "JOI",
        "JIO",
        "OOJIIJ",
        "JJOIOI",
        "JOIIJOJOOI",
    };
    string pattern = rnd.any(patterns);
    int repeats = rnd.next(1, 6);
    string s;
    for (int i = 0; i < repeats; ++i) s += pattern;
    return s;
}

string noisyBalancedSubstring() {
    int leftLen = rnd.next(0, 7);
    int rightLen = rnd.next(0, 7);
    int copies = rnd.next(1, 8);

    string s = repeatChar(leftLen);
    s += shuffledBalancedBlock(copies);
    s += repeatChar(rightLen);
    return s;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    string s;
    int mode = rnd.next(0, 5);
    if (mode == 0) {
        s = repeatChar(rnd.next(1, 20));
    } else if (mode == 1) {
        s = shuffledBalancedBlock(rnd.next(1, 10));
    } else if (mode == 2) {
        s = repeatedPattern();
    } else if (mode == 3) {
        s = noisyBalancedSubstring();
    } else {
        s = randomJOI(rnd.next(1, 30));
    }

    println(static_cast<int>(s.size()));
    println(s);

    return 0;
}

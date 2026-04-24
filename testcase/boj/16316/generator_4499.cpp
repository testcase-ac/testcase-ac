#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // small n for hand-checkability
    int n = rnd.next(1, 10);
    // probability of mumble at each position
    double p_mumble = rnd.next();
    // decide whether to inject a counting error
    bool hasError = rnd.next() < 0.5;
    int errorPos = hasError ? rnd.next(1, n) : -1;
    int wrongVal = -1;
    if (hasError) {
        // choose a wrong value in [0, n+5] that's != errorPos
        do {
            wrongVal = rnd.next(0, n + 5);
        } while (wrongVal == errorPos);
    }
    // build the words
    vector<string> words;
    words.reserve(n);
    for (int i = 1; i <= n; ++i) {
        if (i == errorPos) {
            words.push_back(to_string(wrongVal));
        } else if (rnd.next() < p_mumble) {
            words.push_back("mumble");
        } else {
            words.push_back(to_string(i));
        }
    }
    // output
    println(n);
    println(words);
    return 0;
}

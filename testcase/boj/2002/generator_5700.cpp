#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 1 and 10, biased towards smaller for manual checking
    int N = rnd.wnext(10, -1) + 1;

    // Generate N unique vehicle IDs (6-8 chars of A-Z0-9)
    const string alpha = "ABCDEF";
    set<string> used;
    vector<string> entrance;
    while ((int)entrance.size() < N) {
        int L = rnd.next(6, 8);
        string s;
        for (int i = 0; i < L; i++) {
            s += rnd.any(alpha);
        }
        if (!used.count(s)) {
            used.insert(s);
            entrance.push_back(s);
        }
    }

    // Decide exit ordering scenario
    int scenario = rnd.next(1, 4);
    vector<string> exitList = entrance;
    if (scenario == 1) {
        // No overtakes: same order
    } else if (scenario == 2) {
        // Full overtakes: reverse
        reverse(exitList.begin(), exitList.end());
    } else if (scenario == 3) {
        // Completely random shuffle
        shuffle(exitList.begin(), exitList.end());
    } else {
        // Few random swaps -> few overtakes
        int swaps = rnd.next(1, max(1, N));
        for (int i = 0; i < swaps; i++) {
            int a = rnd.next(0, N-1);
            int b = rnd.next(0, N-1);
            swap(exitList[a], exitList[b]);
        }
    }

    // Output
    println(N);
    for (auto &s : entrance) println(s);
    for (auto &s : exitList) println(s);

    return 0;
}

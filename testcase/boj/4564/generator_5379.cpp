#include "testlib.h"
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases (excluding the terminating 0)
    int T = rnd.next(1, 10);
    vector<int> sv;

    // 1) Possibly include a single-digit case (1–9)
    if (T >= 1 && rnd.next(0, 1) == 0) {
        sv.push_back(rnd.next(1, 9));
    }
    // 2) Possibly include a number containing '0'
    if (T >= 2 && rnd.next(0, 1) == 0) {
        int x;
        do {
            x = rnd.next(1, 100000);
        } while (to_string(x).find('0') == string::npos);
        sv.push_back(x);
    }
    // 3) Possibly include the maximum bound
    if (T >= 3 && rnd.next(0, 1) == 0) {
        sv.push_back(100000);
    }
    // 4) Possibly include a repeated-digit number like 2222 (max 5 digits to stay ≤100000)
    if (T >= 4 && rnd.next(0, 1) == 0) {
        int d = rnd.next(1, 9);
        int len = rnd.next(2, 5);
        string s(len, char('0' + d));
        sv.push_back(stoi(s));
    }
    // Fill remaining cases with random values in [1,100000]
    while ((int)sv.size() < T) {
        sv.push_back(rnd.next(1, 100000));
    }
    // Shuffle to mix different types of cases
    shuffle(sv.begin(), sv.end());

    // Output each test case, then the terminating zero
    for (int x : sv) println(x);
    println(0);

    return 0;
}

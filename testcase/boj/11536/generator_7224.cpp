#include "testlib.h"
#include <set>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose N between 2 and 20, with slight bias to small and large
    int N = rnd.wnext(19, rnd.next(2) < 1 ? -1 : 1) + 2; // bias towards extremes

    // Decide sequence type: 0 = INCREASING, 1 = DECREASING, 2 = NEITHER
    int type;
    if (N == 2) {
        type = rnd.next(0, 1);
    } else {
        type = rnd.next(0, 2);
    }

    // Generate N distinct random uppercase names
    set<string> names;
    while ((int)names.size() < N) {
        int len = rnd.next(2, 12);
        string s;
        s.reserve(len);
        for (int i = 0; i < len; i++) {
            char c = char('A' + rnd.next(0, 25));
            s.push_back(c);
        }
        names.insert(s);
    }
    vector<string> v(names.begin(), names.end());

    // Arrange according to type
    sort(v.begin(), v.end());
    if (type == 1) {
        reverse(v.begin(), v.end());
    } else if (type == 2) {
        // introduce a single inversion to break monotonicity
        int i = rnd.next(0, N - 2);
        swap(v[i], v[i + 1]);
    }

    // Output
    println(N);
    for (auto &s : v) println(s);

    return 0;
}

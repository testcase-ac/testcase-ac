#include "testlib.h"
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases between 3 and 8
    int T = rnd.next(3, 8);

    // Always include edge cases N=1 and N=30
    set<int> cases;
    cases.insert(1);
    cases.insert(30);

    // Ranges for diverse picks
    vector<pair<int,int>> ranges = {{2,5}, {6,15}, {16,29}};
    while ((int)cases.size() < T) {
        auto r = rnd.any(ranges);
        int x = rnd.next(r.first, r.second);
        cases.insert(x);
    }

    // Shuffle order
    vector<int> vc(cases.begin(), cases.end());
    shuffle(vc.begin(), vc.end());

    // Output each N then a final 0
    for (int x : vc) println(x);
    println(0);

    return 0;
}

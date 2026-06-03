#include "testlib.h"
#include <algorithm>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int mode = rnd.next(0, 6);
    int n;
    int abstain;
    int approve;
    int reject;

    if (mode == 0) {
        n = rnd.next(1, 8);
        abstain = rnd.next((n + 1) / 2, n);
        approve = rnd.next(0, n - abstain);
        reject = n - abstain - approve;
    } else if (mode == 1) {
        n = rnd.next(2, 20);
        abstain = rnd.next(0, max(0, (n - 1) / 2));
        int active = n - abstain;
        approve = rnd.next(active / 2 + 1, active);
        reject = active - approve;
    } else if (mode == 2) {
        n = rnd.next(2, 20);
        abstain = rnd.next(0, max(0, (n - 1) / 2));
        int active = n - abstain;
        reject = rnd.next((active + 1) / 2, active);
        approve = active - reject;
    } else if (mode == 3) {
        int half = rnd.next(1, 10);
        n = 2 * half + 1;
        abstain = rnd.next(0, half);
        int active = n - abstain;
        approve = active / 2;
        reject = active - approve;
    } else if (mode == 4) {
        n = rnd.next(90, 100);
        abstain = rnd.next(0, (n - 1) / 2);
        int active = n - abstain;
        approve = rnd.next(0, active);
        reject = active - approve;
    } else {
        n = rnd.next(1, 100);
        approve = rnd.next(0, n);
        reject = rnd.next(0, n - approve);
        abstain = n - approve - reject;
    }

    vector<int> votes;
    votes.insert(votes.end(), approve, 1);
    votes.insert(votes.end(), reject, -1);
    votes.insert(votes.end(), abstain, 0);
    shuffle(votes.begin(), votes.end());

    println(n);
    println(votes);
    return 0;
}

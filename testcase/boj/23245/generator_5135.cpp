#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Sequence length
    int n = rnd.next(1, 10);

    // Value ranges
    int maxP = rnd.next(0, 10);
    int maxQ = rnd.next(0, 10);

    // Modes: 0=random,1=sorted inc,2=sorted dec,3=constant
    int modeP = rnd.next(0, 3);
    int modeQ = rnd.next(0, 3);

    vector<int> p(n), q(n);

    // Generate p
    if (modeP == 0) {
        for (int i = 0; i < n; i++)
            p[i] = rnd.next(0, maxP);
    } else if (modeP == 1) {
        for (int i = 0; i < n; i++)
            p[i] = rnd.next(0, maxP);
        sort(p.begin(), p.end());
    } else if (modeP == 2) {
        for (int i = 0; i < n; i++)
            p[i] = rnd.next(0, maxP);
        sort(p.begin(), p.end(), greater<int>());
    } else {
        int v = rnd.next(0, maxP);
        for (int i = 0; i < n; i++)
            p[i] = v;
    }

    // Generate q
    if (modeQ == 0) {
        for (int i = 0; i < n; i++)
            q[i] = rnd.next(0, maxQ);
    } else if (modeQ == 1) {
        for (int i = 0; i < n; i++)
            q[i] = rnd.next(0, maxQ);
        sort(q.begin(), q.end());
    } else if (modeQ == 2) {
        for (int i = 0; i < n; i++)
            q[i] = rnd.next(0, maxQ);
        sort(q.begin(), q.end(), greater<int>());
    } else {
        int v = rnd.next(0, maxQ);
        for (int i = 0; i < n; i++)
            q[i] = v;
    }

    // Output
    println(n);
    println(p);
    println(q);

    return 0;
}

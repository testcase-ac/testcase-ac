#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameter for number of sons
    int sizeCat = rnd.next(0, 2);
    int N;
    if (sizeCat == 0) N = rnd.next(1, 3);
    else if (sizeCat == 1) N = rnd.next(4, 10);
    else N = rnd.next(11, 20);

    // Hyper-parameter for interval length L = B - A
    int lenCat = rnd.next(0, 2);
    int L;
    if (lenCat == 0) L = rnd.next(1, 5);
    else if (lenCat == 1) L = rnd.next(6, 100);
    else L = rnd.next(101, 10000);

    // Choose A and B = A + L
    int maxA = int(1000000000ll - L);
    int A = rnd.next(1, maxA);
    int B = A + L;

    // Collect even numbers inside [A, B]
    vector<int> evIn;
    int feIn = (A % 2 == 0 ? A : A + 1);
    for (int x = feIn; x <= B; x += 2) {
        evIn.push_back(x);
    }

    // Decide how many sons named inside interval
    int wantIn = rnd.next(0, N);
    if (wantIn > (int)evIn.size()) wantIn = evIn.size();
    int wantOut = N - wantIn;

    // Collect even numbers outside [A, B]
    vector<int> evOut;
    int curLo = (A % 2 == 0 ? A - 2 : A - 1);
    int curHi = (B % 2 == 0 ? B + 2 : B + 1);
    while ((int)evOut.size() < wantOut) {
        if (curLo >= 2) {
            evOut.push_back(curLo);
            curLo -= 2;
        }
        if ((int)evOut.size() < wantOut && curHi <= 1000000000) {
            evOut.push_back(curHi);
            curHi += 2;
        }
        // In case no more candidates, but this won't happen if wantOut>0 only when there is space
    }

    // Pick random unique names
    shuffle(evIn.begin(), evIn.end());
    shuffle(evOut.begin(), evOut.end());
    vector<int> P;
    for (int i = 0; i < wantIn; i++) P.push_back(evIn[i]);
    for (int i = 0; i < wantOut; i++) P.push_back(evOut[i]);
    shuffle(P.begin(), P.end());

    // Output
    println(N);
    println(P);
    println(A, B);
    return 0;
}

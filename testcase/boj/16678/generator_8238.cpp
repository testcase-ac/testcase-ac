#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int caseType = rnd.next(0, 5);
    vector<int> a;
    int N;

    switch (caseType) {
        case 0: {
            // Single element
            N = 1;
            a.push_back(rnd.next(1, 10));
            break;
        }
        case 1: {
            // Small random
            N = rnd.next(2, 5);
            for (int i = 0; i < N; i++)
                a.push_back(rnd.next(1, 10));
            break;
        }
        case 2: {
            // Medium random
            N = rnd.next(6, 15);
            for (int i = 0; i < N; i++)
                a.push_back(rnd.next(1, 20));
            break;
        }
        case 3: {
            // Sorted ascending with small gaps
            N = rnd.next(5, 10);
            int cur = rnd.next(1, 3);
            a.push_back(cur);
            for (int i = 1; i < N; i++) {
                cur += rnd.next(1, 3);
                a.push_back(cur);
            }
            break;
        }
        case 4: {
            // Sorted descending with small gaps
            N = rnd.next(5, 10);
            vector<int> tmp;
            int cur = rnd.next(1, 3);
            tmp.push_back(cur);
            for (int i = 1; i < N; i++) {
                cur += rnd.next(1, 3);
                tmp.push_back(cur);
            }
            a = tmp;
            reverse(a.begin(), a.end());
            break;
        }
        case 5: {
            // Many duplicates
            N = rnd.next(5, 15);
            int k = rnd.next(1, 4);
            vector<int> roots;
            for (int i = 0; i < k; i++)
                roots.push_back(rnd.next(1, 20));
            for (int i = 0; i < N; i++)
                a.push_back(rnd.any(roots));
            break;
        }
    }

    // Random shuffle for variability
    if (rnd.next(0, 1) == 0)
        shuffle(a.begin(), a.end());

    // Output
    println(N);
    for (int x : a)
        println(x);

    return 0;
}

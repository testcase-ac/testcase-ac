#include "testlib.h"
#include <vector>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of test cases
    int T = rnd.next(1, 10);
    vector<pair<int,int>> cases;

    for (int i = 0; i < T; i++) {
        int type = rnd.next(0, 4);
        int a, b;
        switch (type) {
            // equal numbers
            case 0:
                a = rnd.next(1, 1000);
                b = a;
                break;
            // one is 1
            case 1:
                a = 1;
                b = rnd.next(1, 1000);
                if (rnd.next(0, 1)) swap(a, b);
                break;
            // random coprime
            case 2:
                do {
                    a = rnd.next(1, 1000);
                    b = rnd.next(1, 1000);
                } while (std::gcd(a, b) != 1);
                break;
            // random multiples of a common factor
            case 3: {
                int x = rnd.next(1, 1000);
                int maxk = 1000 / x;
                if (maxk >= 2) {
                    int k = rnd.next(1, maxk);
                    int l = rnd.next(1, maxk);
                    a = x * k;
                    b = x * l;
                } else {
                    a = rnd.next(1, 1000);
                    b = rnd.next(1, 1000);
                }
                break;
            }
            // fully random
            default:
                a = rnd.next(1, 1000);
                b = rnd.next(1, 1000);
        }
        cases.emplace_back(a, b);
    }

    // Shuffle to mix scenarios
    shuffle(cases.begin(), cases.end());

    // Output
    println((int)cases.size());
    for (auto &p : cases) {
        println(p.first, p.second);
    }
    return 0;
}

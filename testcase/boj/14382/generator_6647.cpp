#include "testlib.h"
#include <vector>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of cases
    int T = rnd.next(5, 10);

    // Prepare special edge-case numbers
    vector<int> specials = {1, 2, 10, 11, 19, 123, 1692, 999, 123456, 999999, 1000000};
    shuffle(specials.begin(), specials.end());

    vector<int> Ns;
    // Always include zero to test INSOMNIA
    Ns.push_back(0);

    // Fill with distinct specials
    int need = T - 1;
    for (int i = 0; i < (int)specials.size() && need > 0; i++, need--) {
        Ns.push_back(specials[i]);
    }
    // If more cases needed, fill with random N
    while (need-- > 0) {
        Ns.push_back(rnd.next(0, 1000000));
    }

    // Shuffle order of cases
    shuffle(Ns.begin(), Ns.end());

    // Output
    println(T);
    for (int x : Ns) {
        println(x);
    }

    return 0;
}

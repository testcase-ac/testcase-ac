#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Hyper-parameters for diversity
    int N1 = rnd.next(1, 10);
    int N2 = rnd.next(1, 10);
    int alph = rnd.next(1, 5); // use small alphabet size for hand-check
    int Lcommon = rnd.next(0, min(N1, N2)); // number of common letters

    // Build common part (with possible repeats)
    vector<char> common;
    for (int i = 0; i < Lcommon; i++) {
        char c = char('a' + rnd.next(0, alph - 1));
        common.push_back(c);
    }

    // Build string1
    vector<char> svec = common;
    for (int i = Lcommon; i < N1; i++) {
        char c = char('a' + rnd.next(0, alph - 1));
        svec.push_back(c);
    }
    shuffle(svec.begin(), svec.end());

    // Build string2
    vector<char> tvec = common;
    for (int i = Lcommon; i < N2; i++) {
        char c = char('a' + rnd.next(0, alph - 1));
        tvec.push_back(c);
    }
    shuffle(tvec.begin(), tvec.end());

    // Convert to strings
    string s(svec.begin(), svec.end());
    string t(tvec.begin(), tvec.end());

    // Output
    println(s);
    println(t);
    return 0;
}

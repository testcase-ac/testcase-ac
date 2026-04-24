#include "testlib.h"
#include <vector>
#include <string>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Digit patterns: 0-9
    vector<vector<string>> patterns = {
        {"###","#.#","#.#","#.#","###"}, //0
        {"#","#","#","#","#"},           //1
        {"###","..#","###","#..","###"},  //2
        {"###","..#","###","..#","###"},  //3
        {"#.#","#.#","###","..#","..#"},  //4
        {"###","#..","###","..#","###"},  //5
        {"###","#..","###","#.#","###"},  //6
        {"###","..#","..#","..#","..#"},  //7
        {"###","#.#","###","#.#","###"},  //8
        {"###","#.#","###","..#","###"}   //9
    };

    // Hyper-parameters for diversity
    int D = rnd.next(1, 5); // number of digits
    vector<int> digits(D);
    for (int i = 0; i < D; i++) {
        digits[i] = rnd.next(0, 9);
    }
    vector<int> spacing(D, 0);
    for (int i = 1; i < D; i++) {
        spacing[i] = rnd.next(1, 3); // at least one blank column
    }

    // Build the 5-row signal
    vector<string> rows(5, "");
    for (int i = 0; i < D; i++) {
        // add spacing before this digit
        for (int s = 0; s < spacing[i]; s++) {
            for (int r = 0; r < 5; r++) {
                rows[r] += '.';
            }
        }
        int d = digits[i];
        auto &p = patterns[d];
        // append digit pattern
        for (int r = 0; r < 5; r++) {
            rows[r] += p[r];
        }
    }

    // Flatten into single string
    int width = rows[0].size();
    int N = width * 5;
    string full;
    full.reserve(N);
    for (int r = 0; r < 5; r++) full += rows[r];

    // Output
    println(N);
    println(full);

    return 0;
}

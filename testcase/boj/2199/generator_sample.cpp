#include "testlib.h"

#include <string>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const string bases = "AGCT";
    int mode = rnd.next(0, 5);
    int n = 1;
    string sequence;

    if (mode == 0) {
        n = rnd.next(1, 4);
        sequence.assign(n, rnd.any(bases));
    } else if (mode == 1) {
        n = rnd.next(2, 30);
        char first = rnd.any(bases);
        char second = rnd.any(bases);
        for (int i = 0; i < n; ++i) {
            sequence.push_back(i % 2 == 0 ? first : second);
        }
    } else if (mode == 2) {
        n = rnd.next(3, 40);
        int alphabetSize = rnd.next(2, 4);
        string alphabet = bases.substr(0, alphabetSize);
        shuffle(alphabet.begin(), alphabet.end());
        alphabet.resize(alphabetSize);
        for (int i = 0; i < n; ++i) {
            sequence.push_back(rnd.any(alphabet));
        }
    } else if (mode == 3) {
        int blocks = rnd.next(2, 8);
        vector<pair<char, int>> parts;
        n = 0;
        for (int i = 0; i < blocks; ++i) {
            int len = rnd.next(1, 6);
            parts.push_back({rnd.any(bases), len});
            n += len;
        }
        for (auto [base, len] : parts) {
            sequence.append(len, base);
        }
    } else if (mode == 4) {
        n = rnd.next(20, 80);
        for (int i = 0; i < n; ++i) {
            sequence.push_back(rnd.any(bases));
        }
    } else {
        n = rnd.next(4, 36);
        string motif;
        int motifLength = rnd.next(2, 6);
        for (int i = 0; i < motifLength; ++i) {
            motif.push_back(rnd.any(bases));
        }
        for (int i = 0; i < n; ++i) {
            sequence.push_back(motif[i % motifLength]);
        }
    }

    println(n);
    println(sequence);
    return 0;
}

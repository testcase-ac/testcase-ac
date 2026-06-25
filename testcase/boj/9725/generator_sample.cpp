#include "testlib.h"

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

vector<int> valuesWithResidue(int n, int residue) {
    vector<int> values;
    for (int value = residue; value < n; value += 3) {
        values.push_back(value);
    }
    return values;
}

int nextMultipleOfThree(int lo, int hi) {
    int first = lo + (3 - lo % 3) % 3;
    int count = (hi - first) / 3 + 1;
    return first + 3 * rnd.next(count);
}

vector<int> makePermutationCase(int n, int mode) {
    array<vector<int>, 3> byResidue;
    for (int residue = 0; residue < 3; ++residue) {
        byResidue[residue] = valuesWithResidue(n, residue);
        shuffle(byResidue[residue].begin(), byResidue[residue].end());
    }

    vector<int> result(n);
    for (int index = 0; index < n; ++index) {
        int sourceResidue = index % 3;
        if (mode == 1) {
            sourceResidue = (index + 1) % 3;
        } else if (mode == 2) {
            sourceResidue = (index + 2) % 3;
        } else if (mode == 3 && rnd.next(2) == 0) {
            sourceResidue = (index % 3 == 0 ? 1 : index % 3 == 1 ? 0 : 2);
        } else if (mode == 4) {
            sourceResidue = rnd.next(3);
        }

        if (byResidue[sourceResidue].empty()) {
            for (int residue = 0; residue < 3; ++residue) {
                if (!byResidue[residue].empty()) {
                    sourceResidue = residue;
                    break;
                }
            }
        }

        result[index] = byResidue[sourceResidue].back();
        byResidue[sourceResidue].pop_back();
    }

    return result;
}

vector<int> makeRepeatedValueCase(int n) {
    array<vector<int>, 3> byResidue;
    for (int residue = 0; residue < 3; ++residue) {
        byResidue[residue] = valuesWithResidue(n, residue);
    }

    vector<int> residues;
    for (int residue = 0; residue < 3; ++residue) {
        for (int count = 0; count < n / 3; ++count) {
            residues.push_back(residue);
        }
    }
    shuffle(residues.begin(), residues.end());

    vector<int> result;
    for (int residue : residues) {
        if (rnd.next(4) == 0) {
            result.push_back(byResidue[residue].front());
        } else {
            result.push_back(rnd.any(byResidue[residue]));
        }
    }
    return result;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int t = rnd.next(6, 12);
    println(t);

    for (int tc = 0; tc < t; ++tc) {
        int n;
        if (tc == t - 1 && rnd.next(5) == 0) {
            n = 501;
        } else {
            n = nextMultipleOfThree(3, 30);
        }

        int mode = rnd.next(6);
        vector<int> p;
        if (mode == 5) {
            p = makeRepeatedValueCase(n);
        } else {
            p = makePermutationCase(n, mode);
        }

        println(n);
        println(p);
    }

    return 0;
}

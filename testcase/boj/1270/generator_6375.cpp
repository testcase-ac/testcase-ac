#include "testlib.h"
#include <climits>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of territories
    int n = rnd.next(1, 10);
    println(n);
    for (int i = 0; i < n; i++) {
        // Number of soldiers in this territory
        int Ti = rnd.next(1, 20);
        // Decide if there is a controlling army (> half)
        bool ctrl = (Ti == 1) || (rnd.next(0, 1) == 0);
        vector<long long> soldiers;
        if (ctrl) {
            // Choose a controlling army ID (sometimes extreme)
            long long ctrlID;
            if (rnd.next(0, 9) == 0) {
                ctrlID = rnd.next(0,1) ? INT_MIN : INT_MAX;
            } else {
                ctrlID = rnd.next(-5, 5);
            }
            // Ensure ctrlCount > Ti/2
            int minC = Ti / 2 + 1;
            int ctrlCount = rnd.next(minC, Ti);
            for (int j = 0; j < ctrlCount; j++)
                soldiers.push_back(ctrlID);
            int rem = Ti - ctrlCount;
            // Fill remaining with non-ctrl IDs
            for (int j = 0; j < rem; j++) {
                long long x;
                do {
                    x = rnd.next(-5, 5);
                } while (x == ctrlID);
                soldiers.push_back(x);
            }
        } else {
            // No army controls (> half). Build two main IDs
            long long idA = rnd.next(-5, 5);
            long long idB;
            do {
                idB = rnd.next(-5, 5);
            } while (idB == idA);
            int na = Ti / 2;
            int nb = Ti / 2;
            for (int j = 0; j < na; j++)
                soldiers.push_back(idA);
            for (int j = 0; j < nb; j++)
                soldiers.push_back(idB);
            // If odd, one extra different ID
            if (Ti % 2 == 1) {
                long long idC;
                do {
                    idC = rnd.next(-5, 5);
                } while (idC == idA || idC == idB);
                soldiers.push_back(idC);
            }
        }
        // Shuffle the soldiers to randomize order
        shuffle(soldiers.begin(), soldiers.end());
        // Output the line: Ti followed by the soldier IDs
        vector<long long> line;
        line.push_back(Ti);
        for (auto &x : soldiers)
            line.push_back(x);
        println(line);
    }
    return 0;
}

#include "testlib.h"
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> dwarfs, impostors, all;
    while (true) {
        dwarfs.clear();
        // Hyper-parameter for dwarf ranges
        int dm = rnd.next(0, 2);
        int dlo = (dm == 1 ? 30 : 1);
        int dhi = (dm == 0 ? 50 : 99);
        // pick 6 distinct dwarfs
        while (dwarfs.size() < 6) {
            int x = rnd.next(dlo, dhi);
            if (find(dwarfs.begin(), dwarfs.end(), x) == dwarfs.end())
                dwarfs.push_back(x);
        }
        int sum6 = accumulate(dwarfs.begin(), dwarfs.end(), 0);
        int a7 = 100 - sum6;
        // ensure valid 7th dwarf
        if (a7 < 1 || a7 > 99) continue;
        if (find(dwarfs.begin(), dwarfs.end(), a7) != dwarfs.end()) continue;
        dwarfs.push_back(a7);

        // pick 2 impostors with their own hyper-parameter
        impostors.clear();
        int im = rnd.next(0, 2);
        int ilo = (im == 1 ? 50 : 1);
        int ihi = (im == 0 ? 50 : 99);
        while (impostors.size() < 2) {
            int x = rnd.next(ilo, ihi);
            if (find(dwarfs.begin(), dwarfs.end(), x) == dwarfs.end() &&
                find(impostors.begin(), impostors.end(), x) == impostors.end())
                impostors.push_back(x);
        }

        // check unique removal pair condition
        all = dwarfs;
        all.insert(all.end(), impostors.begin(), impostors.end());
        int target = impostors[0] + impostors[1];
        int cnt = 0;
        for (int i = 0; i < 9; i++)
            for (int j = i + 1; j < 9; j++)
                if (all[i] + all[j] == target)
                    cnt++;
        if (cnt == 1) break;  // only the impostor pair sums to S-100
    }

    // output in random order
    shuffle(all.begin(), all.end());
    for (int x : all) println(x);

    return 0;
}

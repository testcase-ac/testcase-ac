#include "testlib.h"

#include <algorithm>
#include <set>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<vector<string>> pools = {
        {"big", "small", "large", "tiny", "round", "swift"},
        {"red", "blue", "green", "white", "brown", "black"},
        {"noisy", "silent", "calm", "wild", "happy"},
        {"spotted", "striped", "plain", "fuzzy"},
        {"young", "old", "fresh"}
    };

    while (true) {
        int adjectiveCount = rnd.next(2, 5);
        vector<int> sizes(adjectiveCount);
        long long fullProduct = 1;
        for (int i = 0; i < adjectiveCount; ++i) {
            int maxSize = int(pools[i].size());
            sizes[i] = rnd.next(2, maxSize);
            fullProduct *= sizes[i];
        }

        vector<vector<int>> allCombos;
        vector<int> current(adjectiveCount, 0);
        while (true) {
            allCombos.push_back(current);
            int pos = adjectiveCount - 1;
            while (pos >= 0) {
                ++current[pos];
                if (current[pos] < sizes[pos]) {
                    break;
                }
                current[pos] = 0;
                --pos;
            }
            if (pos < 0) {
                break;
            }
        }

        shuffle(allCombos.begin(), allCombos.end());
        int upperN = int(min(100LL, fullProduct - 1));
        int n = rnd.next(1, upperN);
        vector<vector<int>> missing(allCombos.begin(), allCombos.begin() + n);

        vector<set<int>> used(adjectiveCount);
        for (const vector<int>& cow : missing) {
            for (int i = 0; i < adjectiveCount; ++i) {
                used[i].insert(cow[i]);
            }
        }

        long long validatorProduct = 1;
        for (int i = 0; i < adjectiveCount; ++i) {
            validatorProduct *= int(used[i].size());
        }

        long long ownedCows = validatorProduct - n;
        if (ownedCows <= 0) {
            continue;
        }

        long long k = rnd.next(1LL, ownedCows);
        println(n, k);
        for (const vector<int>& cow : missing) {
            printf("Farmer John has no");
            for (int i = 0; i < adjectiveCount; ++i) {
                printf(" %s", pools[i][cow[i]].c_str());
            }
            printf(" cow.\n");
        }
        return 0;
    }
}

#include "testlib.h"

#include <algorithm>
#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int n = rnd.next(1, 9);
    int mode = rnd.next(0, 4);
    println(n);

    for (int theorem = 0; theorem < n; ++theorem) {
        int proofCount = rnd.next(1, min(5, n + 1));
        if (mode == 0 && theorem == 0) proofCount = rnd.next(3, min(6, n + 2));
        println(proofCount);

        for (int proof = 0; proof < proofCount; ++proof) {
            vector<int> candidates;
            for (int dependency = 0; dependency < n; ++dependency) {
                if (dependency != theorem) candidates.push_back(dependency);
            }
            shuffle(candidates.begin(), candidates.end());

            int maxDependencies = min<int>(candidates.size(), mode == 1 ? 1 : 4);
            int dependencyCount = rnd.next(0, maxDependencies);

            if (mode == 2 && theorem + 1 < n && proof == 0) {
                candidates.erase(find(candidates.begin(), candidates.end(), theorem + 1));
                candidates.insert(candidates.begin(), theorem + 1);
                dependencyCount = max(dependencyCount, 1);
            }
            if (mode == 3 && theorem > 0 && proof == 0) {
                candidates.erase(find(candidates.begin(), candidates.end(), theorem - 1));
                candidates.insert(candidates.begin(), theorem - 1);
                dependencyCount = max(dependencyCount, 1);
            }

            int length;
            if (mode == 4 && proof == 0) {
                length = rnd.next(0, 3);
            } else if (mode == 0) {
                length = rnd.next(0, 40);
            } else {
                length = rnd.next(0, 200);
            }

            vector<int> line;
            line.push_back(length);
            line.push_back(dependencyCount);
            for (int i = 0; i < dependencyCount; ++i) {
                line.push_back(candidates[i]);
            }
            println(line);
        }
    }

    return 0;
}

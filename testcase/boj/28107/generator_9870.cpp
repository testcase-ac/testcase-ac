#include "testlib.h"
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6);

    int N = 0, M = 0, T = 0;
    vector<vector<int>> prefs;
    vector<int> B;

    if (scenario == 0) {
        // Single customer, some wanted and unwanted types
        T = rnd.next(1, 7);
        N = 1;
        M = rnd.next(1, 10);
        prefs.assign(N, vector<int>());

        vector<int> pool(T);
        for (int i = 0; i < T; ++i) pool[i] = i + 1;
        shuffle(pool.begin(), pool.end());
        int k = rnd.next(0, T);
        for (int i = 0; i < k; ++i)
            prefs[0].push_back(pool[i]);

        vector<bool> mark(T + 1, false);
        for (int x : prefs[0]) mark[x] = true;

        vector<int> wantedList, unwantList;
        for (int t = 1; t <= T; ++t) {
            if (mark[t]) wantedList.push_back(t);
            else unwantList.push_back(t);
        }

        B.resize(M);
        for (int i = 0; i < M; ++i) {
            bool chooseWanted;
            if (!wantedList.empty() && !unwantList.empty())
                chooseWanted = (rnd.next(0, 99) < 60);
            else if (!wantedList.empty())
                chooseWanted = true;
            else
                chooseWanted = false;

            if (chooseWanted)
                B[i] = rnd.any(wantedList);
            else
                B[i] = rnd.any(unwantList);
        }
    } else if (scenario == 1) {
        // Many customers all want a popular type
        T = rnd.next(2, 8);
        N = rnd.next(2, 6);
        M = rnd.next(3, 12);
        prefs.assign(N, vector<int>());

        int special = rnd.next(1, T);
        for (int i = 0; i < N; ++i) {
            int k = (rnd.next(0, 99) < 70 ? 1 : 2);
            prefs[i].push_back(special);
            if (k == 2) {
                int other;
                do {
                    other = rnd.next(1, T);
                } while (other == special);
                prefs[i].push_back(other);
                if (rnd.next(0, 1))
                    swap(prefs[i][0], prefs[i][1]);
            }
        }

        B.resize(M);
        for (int i = 0; i < M; ++i) {
            if (rnd.next(0, 99) < 70)
                B[i] = special;
            else
                B[i] = rnd.next(1, T);
        }
    } else if (scenario == 2) {
        // Early customers want many common types and steal from later ones
        T = rnd.next(3, 10);
        N = rnd.next(3, 7);
        M = rnd.next(N, min(20, 3 * N + 5));
        prefs.assign(N, vector<int>());

        // Customer 1 wants many kinds
        vector<int> pool(T);
        for (int i = 0; i < T; ++i) pool[i] = i + 1;
        shuffle(pool.begin(), pool.end());
        int k1 = rnd.next(max(2, T / 2), T);
        for (int i = 0; i < k1; ++i)
            prefs[0].push_back(pool[i]);

        // Other customers want small subsets, often overlapping with customer 1
        for (int i = 1; i < N; ++i) {
            bool chooseFromFirst = (rnd.next(0, 1) == 0);
            if (chooseFromFirst) {
                int maxK = min(3, (int)prefs[0].size());
                int k = rnd.next(0, maxK);
                vector<int> pf = prefs[0];
                shuffle(pf.begin(), pf.end());
                for (int j = 0; j < k; ++j)
                    prefs[i].push_back(pf[j]);
            } else {
                int maxK = min(3, T);
                int k = rnd.next(0, maxK);
                vector<int> pool2(T);
                for (int j = 0; j < T; ++j) pool2[j] = j + 1;
                shuffle(pool2.begin(), pool2.end());
                for (int j = 0; j < k; ++j)
                    prefs[i].push_back(pool2[j]);
            }
        }

        vector<int> typesFirst = prefs[0];
        B.resize(M);
        for (int i = 0; i < M; ++i) {
            if (rnd.next(0, 99) < 75)
                B[i] = rnd.any(typesFirst);
            else
                B[i] = rnd.next(1, T);
        }
    } else if (scenario == 3) {
        // Balanced random preferences, mix of wanted and unwanted types produced
        N = rnd.next(2, 8);
        T = rnd.next(max(3, N), 12);
        M = rnd.next(N, 20);
        prefs.assign(N, vector<int>());

        for (int i = 0; i < N; ++i) {
            int maxK = min(4, T);
            int k = rnd.next(0, maxK);
            vector<int> pool(T);
            for (int j = 0; j < T; ++j) pool[j] = j + 1;
            shuffle(pool.begin(), pool.end());
            for (int j = 0; j < k; ++j)
                prefs[i].push_back(pool[j]);
        }

        vector<bool> mark(T + 1, false);
        for (int i = 0; i < N; ++i)
            for (int x : prefs[i])
                mark[x] = true;

        vector<int> wantedTypes, unwantedTypes;
        for (int t = 1; t <= T; ++t) {
            if (mark[t]) wantedTypes.push_back(t);
            else unwantedTypes.push_back(t);
        }

        B.resize(M);
        for (int i = 0; i < M; ++i) {
            bool chooseWanted;
            if (!wantedTypes.empty() && !unwantedTypes.empty())
                chooseWanted = (rnd.next(0, 99) < 70);
            else if (!wantedTypes.empty())
                chooseWanted = true;
            else
                chooseWanted = false;

            if (chooseWanted)
                B[i] = rnd.any(wantedTypes);
            else
                B[i] = rnd.any(unwantedTypes);
        }
    } else if (scenario == 4) {
        // Many produced types are never wanted
        N = rnd.next(2, 7);
        T = rnd.next(4, 15);
        int W = rnd.next(1, T - 1); // only first W types are potentially wanted
        M = rnd.next(5, 25);
        prefs.assign(N, vector<int>());

        for (int i = 0; i < N; ++i) {
            int maxK = min(3, W);
            int k = rnd.next(0, maxK);
            vector<int> pool(W);
            for (int j = 0; j < W; ++j) pool[j] = j + 1;
            shuffle(pool.begin(), pool.end());
            for (int j = 0; j < k; ++j)
                prefs[i].push_back(pool[j]);
        }

        vector<bool> mark(T + 1, false);
        for (int i = 0; i < N; ++i)
            for (int x : prefs[i])
                mark[x] = true;

        vector<int> wantedTypes, unwantedTypes;
        for (int t = 1; t <= T; ++t) {
            if (mark[t]) wantedTypes.push_back(t);
            else unwantedTypes.push_back(t);
        }

        B.resize(M);
        for (int i = 0; i < M; ++i) {
            bool chooseWanted = (!wantedTypes.empty() && rnd.next(0, 99) < 25);
            if (chooseWanted)
                B[i] = rnd.any(wantedTypes);
            else
                B[i] = rnd.any(unwantedTypes);
        }
    } else if (scenario == 5) {
        // Each customer wants unique (non-overlapping) types
        N = rnd.next(2, 6);
        int Tmax = min(20, 3 * N);
        T = rnd.next(N, Tmax);
        prefs.assign(N, vector<int>());

        int currentType = 1;
        for (int i = 0; i < N; ++i) {
            int remainingPeople = N - i;
            int remainingTypes = T - currentType + 1;
            int maxForThis = remainingTypes - (remainingPeople - 1);
            if (maxForThis > 3) maxForThis = 3;
            int k = rnd.next(1, maxForThis);
            for (int j = 0; j < k; ++j)
                prefs[i].push_back(currentType++);
        }

        int usedTypes = currentType - 1;
        M = rnd.next(usedTypes, min(25, usedTypes * 2 + 3));

        vector<int> allTypes;
        for (int t = 1; t <= usedTypes; ++t) allTypes.push_back(t);

        B.clear();
        for (int t = 1; t <= usedTypes; ++t)
            B.push_back(t);
        while ((int)B.size() < M)
            B.push_back(rnd.next(1, usedTypes));
        shuffle(B.begin(), B.end());
    } else {
        // scenario == 6 : Many customers, some with empty lists
        N = rnd.next(5, 10);
        T = rnd.next(3, 15);
        M = rnd.next(10, 30);
        prefs.assign(N, vector<int>());

        for (int i = 0; i < N; ++i) {
            bool makeEmpty = (rnd.next(0, 99) < 40);
            int k = 0;
            if (!makeEmpty)
                k = rnd.next(1, min(4, T));

            vector<int> pool(T);
            for (int j = 0; j < T; ++j) pool[j] = j + 1;
            shuffle(pool.begin(), pool.end());
            for (int j = 0; j < k; ++j)
                prefs[i].push_back(pool[j]);
        }

        vector<bool> mark(T + 1, false);
        for (int i = 0; i < N; ++i)
            for (int x : prefs[i])
                mark[x] = true;

        vector<int> wantedTypes;
        for (int t = 1; t <= T; ++t)
            if (mark[t]) wantedTypes.push_back(t);

        B.resize(M);
        for (int i = 0; i < M; ++i) {
            if (wantedTypes.empty()) {
                B[i] = rnd.next(1, T);
            } else {
                if (rnd.next(0, 99) < 50)
                    B[i] = rnd.any(wantedTypes);
                else
                    B[i] = rnd.next(1, T);
            }
        }
    }

    // Output the generated test
    println(N, M);
    for (int i = 0; i < N; ++i) {
        vector<int> line;
        line.push_back((int)prefs[i].size());
        for (int x : prefs[i]) line.push_back(x);
        println(line);
    }
    println(B);

    return 0;
}

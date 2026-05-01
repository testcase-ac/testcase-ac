#include "testlib.h"
using namespace std;

struct Log {
    int a, b;
};

vector<Log> generateValidSequence(int N0, int P) {
    vector<Log> res;
    vector<int> outside, inside;
    for (int i = 1; i <= P; ++i)
        outside.push_back(i);

    for (int i = 0; i < N0; ++i) {
        int remaining = N0 - i;
        int type; // 1 = enter, 0 = exit

        if (inside.empty()) {
            type = 1;
        } else if (outside.empty()) {
            type = 0;
        } else if (remaining == (int)inside.size()) {
            // must exit all remaining inside
            type = 0;
        } else {
            type = rnd.next(0, 1);
        }

        if (type == 1) {
            // enter from outside
            int idx = rnd.next(0, (int)outside.size() - 1);
            int p = outside[idx];
            res.push_back({p, 1});
            outside[idx] = outside.back();
            outside.pop_back();
            inside.push_back(p);
        } else {
            // exit from inside
            int idx = rnd.next(0, (int)inside.size() - 1);
            int p = inside[idx];
            res.push_back({p, 0});
            inside[idx] = inside.back();
            inside.pop_back();
            outside.push_back(p);
        }
    }

    return res;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Log> logs;
    int pattern = rnd.next(0, 5); // 0..5 => 6 patterns

    if (pattern == 0) {
        // Fully consistent sequence, answer = 0
        int N0 = 2 * rnd.next(1, 15); // 2..30
        int P = rnd.next(1, min(5, N0 / 2));
        logs = generateValidSequence(N0, P);
    } else if (pattern == 1) {
        // Valid sequence with some missing exits at the end
        int N0 = 2 * rnd.next(1, 15); // 2..30
        int P = rnd.next(1, min(5, N0 / 2));
        vector<Log> base = generateValidSequence(N0, P);

        // Collect last exit index per person
        map<int, int> lastExit;
        for (int i = 0; i < N0; ++i) {
            if (base[i].b == 0) {
                lastExit[base[i].a] = i;
            }
        }

        vector<int> indices;
        for (auto &kv : lastExit) indices.push_back(kv.second);

        int maxDeletable = min((int)indices.size(), N0 - 1);
        if (maxDeletable <= 0) {
            logs = base; // fallback, though practically should not happen
        } else {
            int K = rnd.next(1, maxDeletable);
            shuffle(indices.begin(), indices.end());
            vector<char> del(N0, false);
            for (int i = 0; i < K; ++i)
                del[indices[i]] = true;

            logs.clear();
            for (int i = 0; i < N0; ++i)
                if (!del[i])
                    logs.push_back(base[i]);
        }
    } else if (pattern == 2) {
        // Valid sequence with some missing entries at the beginning
        int N0 = 2 * rnd.next(1, 15); // 2..30
        int P = rnd.next(1, min(5, N0 / 2));
        vector<Log> base = generateValidSequence(N0, P);

        // Collect first entry index per person
        map<int, int> firstEntry;
        for (int i = 0; i < N0; ++i) {
            if (base[i].b == 1 && !firstEntry.count(base[i].a)) {
                firstEntry[base[i].a] = i;
            }
        }

        vector<int> indices;
        for (auto &kv : firstEntry) indices.push_back(kv.second);

        int maxDeletable = min((int)indices.size(), N0 - 1);
        if (maxDeletable <= 0) {
            logs = base; // fallback
        } else {
            int K = rnd.next(1, maxDeletable);
            shuffle(indices.begin(), indices.end());
            vector<char> del(N0, false);
            for (int i = 0; i < K; ++i)
                del[indices[i]] = true;

            logs.clear();
            for (int i = 0; i < N0; ++i)
                if (!del[i])
                    logs.push_back(base[i]);
        }
    } else if (pattern == 3) {
        // Valid base sequence, then delete some first entries and last exits (both kinds of anomalies)
        int N0 = 2 * rnd.next(1, 15); // 2..30
        int P = rnd.next(1, min(5, N0 / 2));
        vector<Log> base = generateValidSequence(N0, P);

        map<int, int> firstEntry, lastExit;
        for (int i = 0; i < N0; ++i) {
            int a = base[i].a;
            if (base[i].b == 1) {
                if (!firstEntry.count(a)) firstEntry[a] = i;
            } else {
                lastExit[a] = i;
            }
        }

        set<int> delIdx;
        // Randomly choose some first entries to delete
        for (auto &kv : firstEntry) {
            if (rnd.next(0, 1) == 1) {
                delIdx.insert(kv.second);
            }
        }
        // Randomly choose some last exits to delete
        for (auto &kv : lastExit) {
            if (rnd.next(0, 1) == 1) {
                delIdx.insert(kv.second);
            }
        }

        // Ensure we delete at least one and not all
        if (delIdx.empty()) {
            vector<int> unionIdx;
            for (auto &kv : firstEntry) unionIdx.push_back(kv.second);
            for (auto &kv : lastExit) unionIdx.push_back(kv.second);
            if (!unionIdx.empty()) {
                sort(unionIdx.begin(), unionIdx.end());
                unionIdx.erase(unique(unionIdx.begin(), unionIdx.end()), unionIdx.end());
                int pick = rnd.next(0, (int)unionIdx.size() - 1);
                delIdx.insert(unionIdx[pick]);
            }
        }
        if ((int)delIdx.size() == N0 && N0 > 0) {
            // un-delete one random index
            vector<int> all(delIdx.begin(), delIdx.end());
            int pick = rnd.next(0, N0 - 1);
            delIdx.erase(all[pick]);
        }

        vector<char> del(N0, false);
        for (int x : delIdx) if (0 <= x && x < N0) del[x] = true;

        logs.clear();
        for (int i = 0; i < N0; ++i)
            if (!del[i])
                logs.push_back(base[i]);
    } else if (pattern == 4) {
        // Completely random sequence
        int N = rnd.next(1, 30);
        int P = rnd.next(1, min(7, N));
        logs.clear();
        for (int i = 0; i < N; ++i) {
            int a = rnd.next(1, P);
            int b = rnd.next(0, 1);
            logs.push_back({a, b});
        }
    } else { // pattern == 5
        // Single person with runs of same operation
        int N = rnd.next(1, 30);
        logs.clear();
        int lastType = -1;
        while ((int)logs.size() < N) {
            int remaining = N - (int)logs.size();
            int maxRun = min(5, remaining);
            int len = rnd.next(1, maxRun);
            int type;
            if (lastType == -1) {
                type = rnd.next(0, 1);
            } else {
                // 70% keep same, 30% flip
                if (rnd.next(0, 9) < 7) type = lastType;
                else type = 1 - lastType;
            }
            for (int j = 0; j < len && (int)logs.size() < N; ++j)
                logs.push_back({1, type});
            lastType = type;
        }
    }

    // Optional remap of IDs to large numbers, ensuring distinct IDs and using boundary 200000
    if (!logs.empty() && rnd.next(0, 4) == 0) { // 1/5 chance
        vector<int> ids;
        for (auto &lg : logs) ids.push_back(lg.a);
        sort(ids.begin(), ids.end());
        ids.erase(unique(ids.begin(), ids.end()), ids.end());

        map<int, int> mp;
        set<int> used;
        if (!ids.empty()) {
            // First ID gets 200000 to test upper bound
            mp[ids[0]] = 200000;
            used.insert(200000);
            for (int i = 1; i < (int)ids.size(); ++i) {
                int x;
                do {
                    x = rnd.next(1, 199999);
                } while (used.count(x));
                used.insert(x);
                mp[ids[i]] = x;
            }
            for (auto &lg : logs) {
                lg.a = mp[lg.a];
            }
        }
    }

    int Nout = (int)logs.size();
    if (Nout == 0) {
        // Very unlikely fallback: ensure at least one record
        logs.push_back({1, 1});
        Nout = 1;
    }

    println(Nout);
    for (auto &lg : logs)
        println(lg.a, lg.b);

    return 0;
}

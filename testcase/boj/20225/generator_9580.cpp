#include "testlib.h"
using namespace std;

struct Dataset {
    int m, n, p;
    vector<pair<int,int>> ev;
};

Dataset makeIsolated() {
    Dataset ds;
    ds.m = rnd.next(1, 6);
    ds.p = rnd.next(1, ds.m);
    ds.ev.clear();

    int maxEvents = 3;
    if (ds.m <= 2) {
        ds.n = 0;
        return ds;
    }

    int n = rnd.next(0, maxEvents);
    for (int i = 0; i < n; ++i) {
        int a, b;
        while (true) {
            a = rnd.next(1, ds.m);
            b = rnd.next(1, ds.m);
            if (a != b && a != ds.p && b != ds.p) break;
        }
        ds.ev.emplace_back(a, b);
    }
    ds.n = (int)ds.ev.size();
    return ds;
}

Dataset makeRandomDynamic() {
    Dataset ds;
    ds.m = rnd.next(3, 10);
    ds.p = rnd.next(1, ds.m);
    ds.ev.clear();

    int T = rnd.next(3, min(12, ds.m * 3));

    vector<int> infected(ds.m + 1, 0);
    infected[ds.p] = 1;

    for (int step = 0; step < T; ++step) {
        vector<int> inf, uninf;
        for (int i = 1; i <= ds.m; ++i) {
            if (infected[i]) inf.push_back(i);
            else uninf.push_back(i);
        }

        int a = 1, b = 2;
        bool doInfecting = rnd.next(0, 2) != 0; // about 2/3

        if (doInfecting && !inf.empty()) {
            a = rnd.any(inf);
            // prefer to hit uninfected if possible
            if (!uninf.empty() && rnd.next(0, 1) == 0) {
                b = rnd.any(uninf);
                if (b == a) {
                    // fall back
                    vector<int> cand;
                    for (int i = 1; i <= ds.m; ++i)
                        if (i != a) cand.push_back(i);
                    b = rnd.any(cand);
                }
            } else {
                vector<int> cand;
                for (int i = 1; i <= ds.m; ++i)
                    if (i != a) cand.push_back(i);
                b = rnd.any(cand);
            }
        } else {
            // noise: try both uninfected if possible
            if ((int)uninf.size() >= 2) {
                a = rnd.any(uninf);
                do {
                    b = rnd.any(uninf);
                } while (b == a);
            } else {
                // pick any distinct pair
                a = rnd.next(1, ds.m);
                do {
                    b = rnd.next(1, ds.m);
                } while (b == a);
            }
        }

        ds.ev.emplace_back(a, b);
        if (infected[a] || infected[b]) {
            infected[a] = infected[b] = 1;
        }
    }

    ds.n = (int)ds.ev.size();
    return ds;
}

Dataset makeTimeTrap() {
    Dataset ds;
    ds.m = rnd.next(3, 8);
    ds.p = rnd.next(1, ds.m);
    ds.ev.clear();

    vector<int> others;
    for (int i = 1; i <= ds.m; ++i)
        if (i != ds.p) others.push_back(i);
    shuffle(others.begin(), others.end());

    int a = others[0];
    int b = others[1 % others.size()];

    // Track "assumed infected" to design events
    vector<int> infectedFlag(ds.m + 1, 0);
    infectedFlag[ds.p] = 1;

    // 1) Early crucial event a-b (both uninfected)
    ds.ev.emplace_back(a, b);

    // Early noise among uninfected (excluding p)
    int earlyNoise = rnd.next(0, 2);
    for (int i = 0; i < earlyNoise; ++i) {
        int x, y;
        while (true) {
            x = rnd.any(others);
            y = rnd.any(others);
            if (x != y) break;
        }
        ds.ev.emplace_back(x, y);
    }

    // 2) Infection event p-a
    ds.ev.emplace_back(ds.p, a);
    infectedFlag[a] = 1;

    // 3) Later events: mix of infection-spreading and noise,
    // but never infect b.
    int laterEvents = rnd.next(1, 4);

    for (int i = 0; i < laterEvents; ++i) {
        // Build current infected / non-infected lists
        vector<int> infected, noninf;
        for (int v = 1; v <= ds.m; ++v) {
            if (infectedFlag[v]) infected.push_back(v);
            else noninf.push_back(v);
        }

        bool doInfect = !infected.empty() && (int)noninf.size() >= 1 && rnd.next(0, 1) == 0;

        if (doInfect) {
            // Infect new node, but never b
            vector<int> cand;
            for (int v : noninf)
                if (v != b) cand.push_back(v);

            if (!cand.empty()) {
                int u = rnd.any(infected);
                int v = rnd.any(cand);
                ds.ev.emplace_back(u, v);
                infectedFlag[v] = 1;
                continue;
            }
        }

        // Noise event: between two non-infected nodes (if possible), none infected
        vector<int> noninfectedNodes;
        for (int v = 1; v <= ds.m; ++v)
            if (!infectedFlag[v]) noninfectedNodes.push_back(v);

        int x, y;
        if ((int)noninfectedNodes.size() >= 2) {
            x = rnd.any(noninfectedNodes);
            do {
                y = rnd.any(noninfectedNodes);
            } while (y == x);
        } else {
            // Fallback: any pair, but avoid mixing infected & b
            while (true) {
                x = rnd.next(1, ds.m);
                y = rnd.next(1, ds.m);
                if (x == y) continue;
                // avoid accidentally infecting b by contact with infected
                if ((x == b && infectedFlag[y]) || (y == b && infectedFlag[x])) continue;
                break;
            }
        }
        ds.ev.emplace_back(x, y);
    }

    ds.n = (int)ds.ev.size();
    return ds;
}

Dataset makeSimpleChain() {
    Dataset ds;
    ds.m = rnd.next(3, 10);
    ds.p = rnd.next(1, ds.m);
    ds.ev.clear();

    // Early noise before p participates
    int earlyNoise = rnd.next(0, 2);
    for (int i = 0; i < earlyNoise; ++i) {
        int a, b;
        while (true) {
            a = rnd.next(1, ds.m);
            b = rnd.next(1, ds.m);
            if (a != b && a != ds.p && b != ds.p) break;
        }
        ds.ev.emplace_back(a, b);
    }

    // Build a permutation with p at start
    vector<int> order;
    order.push_back(ds.p);
    for (int i = 1; i <= ds.m; ++i)
        if (i != ds.p) order.push_back(i);
    shuffle(order.begin() + 1, order.end());

    int L = rnd.next(2, ds.m); // use first L in chain
    for (int i = 0; i < L - 1; ++i) {
        ds.ev.emplace_back(order[i], order[i + 1]);
    }

    // A few extra random events afterwards
    int extra = rnd.next(0, 2);
    for (int i = 0; i < extra; ++i) {
        int a, b;
        do {
            a = rnd.next(1, ds.m);
            b = rnd.next(1, ds.m);
        } while (a == b);
        ds.ev.emplace_back(a, b);
    }

    ds.n = (int)ds.ev.size();
    return ds;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Dataset> all;

    // Always include a purely isolated (or effectively isolated) case
    all.push_back(makeIsolated());

    // Always include a time-order-sensitive trap
    all.push_back(makeTimeTrap());

    // Optionally include a random dynamic case
    if (rnd.next(0, 1) == 0)
        all.push_back(makeRandomDynamic());

    // Optionally include a chain-style case
    if (rnd.next(0, 1) == 0)
        all.push_back(makeSimpleChain());

    // Output datasets
    for (auto &ds : all) {
        println(ds.m, ds.n, ds.p);
        for (auto &e : ds.ev)
            println(e.first, e.second);
    }
    println(0, 0, 0);

    return 0;
}

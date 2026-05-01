#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    // Number of test cases
    int T = rnd.next(1, 5);
    println(T);
    for (int tc = 0; tc < T; tc++) {
        // number of queues
        int m = rnd.next(1, 10);
        println(m);
        // Generate queue IDs in random order
        vector<int> ids(m);
        iota(ids.begin(), ids.end(), 0);
        shuffle(ids.begin(), ids.end());
        // Track sizes for event constraints
        vector<int> qsize(m);
        // For each queue, generate initial customers
        for (int qi = 0; qi < m; qi++) {
            int id = ids[qi];
            // initial customers 1..5
            int ic = rnd.next(1, 5);
            qsize[id] = ic;
            // employee base time 0..10
            int ec = rnd.next(0, 10);
            // print queue header
            println(id, ic, ec);
            // print extra times for each customer 0..15
            vector<int> extras(ic);
            for (int i = 0; i < ic; i++) {
                extras[i] = rnd.next(0, 15);
            }
            println(extras);
        }
        // Number of events 0..10
        int v = rnd.next(0, 10);
        println(v);
        if (v > 0) {
            // generate unique times in [1,20]
            vector<int> times(20);
            iota(times.begin(), times.end(), 1);
            shuffle(times.begin(), times.end());
            times.resize(v);
            sort(times.begin(), times.end());
            for (int i = 0; i < v; i++) {
                int t = times[i];
                // decide event type, weight join 60%
                bool wantJoin = rnd.next() < 0.6;
                int qi = rnd.next(0, m-1);
                if (wantJoin) {
                    // if queue full, fallback to change
                    if (qsize[qi] >= 30) wantJoin = false;
                }
                if (wantJoin) {
                    // join event
                    int extra = rnd.next(0, 15);
                    println("join", t, qi, extra);
                    qsize[qi]++;
                } else {
                    // change event
                    int ne = rnd.next(0, 10);
                    println("change", t, qi, ne);
                }
            }
        }
    }
    return 0;
}

#include "testlib.h"
using namespace std;

struct Op {
    char t;
    int x; // page number for 'A', unused otherwise
};

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Choose number of different pages (small for readability)
    int N = rnd.next(1, 8);

    // Choose number of operations (mix of small and medium)
    int Qtarget;
    if (rnd.next(0, 1) == 0) {
        Qtarget = rnd.next(1, 15);
    } else {
        Qtarget = rnd.next(15, 40);
    }

    vector<Op> ops;
    ops.reserve(Qtarget);

    // Simulated browser state to guide generation
    int cur = 0;              // 0 means "no current page yet"
    vector<int> backStack;    // oldest at index 0, newest at back()
    vector<int> frontStack;
    bool seenA = false;

    for (int step = 0; step < Qtarget; ++step) {
        bool mustAccess = (!seenA && step == Qtarget - 1);
        char t;
        int x = 0;

        if (mustAccess) {
            t = 'A';
        } else {
            int r = rnd.next(1, 100);
            if (cur == 0) {
                // No current page yet: mostly force accesses, but allow some useless ops
                if (r <= 70) t = 'A';
                else if (r <= 85) t = 'B';
                else if (r <= 95) t = 'F';
                else t = 'C';
            } else {
                // Normal state
                if (r <= 50) t = 'A';
                else if (r <= 70) t = 'B';
                else if (r <= 90) t = 'F';
                else t = 'C';
            }

            // If B/F would be ineffective, often turn them into A to get richer histories
            if (t == 'B' && backStack.empty()) {
                if (rnd.next(0, 3) != 0) t = 'A';
            }
            if (t == 'F' && frontStack.empty()) {
                if (rnd.next(0, 3) != 0) t = 'A';
            }
        }

        if (t == 'A') {
            int page;
            if (cur != 0 && rnd.next(0, 3) == 0) {
                // Sometimes access the same page to create duplicates in back history
                page = cur;
            } else {
                page = rnd.next(1, N);
            }
            x = page;

            // Simulate Access
            if (cur != 0) {
                backStack.push_back(cur);
            }
            cur = page;
            frontStack.clear();
            seenA = true;
        } else if (t == 'B') {
            // Simulate Backward
            if (!backStack.empty()) {
                frontStack.push_back(cur);
                cur = backStack.back();
                backStack.pop_back();
            }
        } else if (t == 'F') {
            // Simulate Forward
            if (!frontStack.empty()) {
                backStack.push_back(cur);
                cur = frontStack.back();
                frontStack.pop_back();
            }
        } else if (t == 'C') {
            // Simulate Compress on backStack
            if (backStack.size() >= 2u) {
                vector<int> nb;
                nb.reserve(backStack.size());
                for (size_t i = 0; i < backStack.size();) {
                    int val = backStack[i];
                    size_t j = i;
                    while (j + 1 < backStack.size() && backStack[j + 1] == val) j++;
                    // Keep only the most recent in this run (index j)
                    nb.push_back(backStack[j]);
                    i = j + 1;
                }
                backStack.swap(nb);
            }
        }

        ops.push_back({t, x});
    }

    int Q = (int)ops.size();
    println(N, Q);
    for (const auto &op : ops) {
        if (op.t == 'A') {
            println(op.t, op.x);
        } else if (op.t == 'B') {
            println("B");
        } else if (op.t == 'F') {
            println("F");
        } else { // 'C'
            println("C");
        }
    }

    return 0;
}

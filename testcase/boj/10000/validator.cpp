#include "testlib.h"
#include <vector>
#include <algorithm>
#include <cstdint>
using namespace std;

struct Event {
    int64_t pos;
    int type; // 0 = close, 1 = open
    int id;
    int64_t L, R;
};

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read N
    int N = inf.readInt(1, 300000, "N");
    inf.readEoln();

    // Read circles
    vector<pair<int64_t,int64_t>> circles;
    circles.reserve(N);
    for (int i = 0; i < N; i++) {
        int64_t x = inf.readLong(-1000000000LL, 1000000000LL, "x_i");
        inf.readSpace();
        int64_t r = inf.readLong(1LL, 1000000000LL, "r_i");
        inf.readEoln();
        circles.emplace_back(x, r);
    }

    // Check uniqueness of (x, r)
    {
        auto tmp = circles;
        sort(tmp.begin(), tmp.end());
        for (int i = 1; i < N; i++) {
            if (tmp[i] == tmp[i-1]) {
                ensuref(false,
                        "Duplicate circle found at sorted positions %d and %d: (x=%lld, r=%lld)",
                        i-1, i,
                        (long long)tmp[i].first,
                        (long long)tmp[i].second);
            }
        }
    }

    // Build intervals [L, R]
    vector<pair<int64_t,int64_t>> interval(N);
    for (int i = 0; i < N; i++) {
        int64_t x = circles[i].first;
        int64_t r = circles[i].second;
        int64_t L = x - r;
        int64_t R = x + r;
        interval[i] = {L, R};
    }

    // Build events for bracket matching:
    //   open at L, close at R
    vector<Event> events;
    events.reserve(2*N);
    for (int i = 0; i < N; i++) {
        auto &p = interval[i];
        events.push_back(Event{p.first, 1, i, p.first, p.second});  // open
        events.push_back(Event{p.second, 0, i, p.first, p.second}); // close
    }

    // Sort events:
    // 1) by pos ascending
    // 2) closes (type=0) before opens (type=1) at same pos (allow external tangency)
    // 3) among opens at same pos: larger R first (nesting)
    // 4) among closes at same pos: larger L first (inner closes before outer)
    sort(events.begin(), events.end(), [&](const Event &a, const Event &b) {
        if (a.pos != b.pos) return a.pos < b.pos;
        if (a.type != b.type) return a.type < b.type;
        if (a.type == 1) {
            // both opens: bigger interval first
            return a.R > b.R;
        } else {
            // both closes: inner (larger L) first
            return a.L > b.L;
        }
    });

    // Sweep with stack to ensure no partial overlaps
    vector<int> st;
    st.reserve(N);
    for (auto &e : events) {
        if (e.type == 1) {
            // open
            st.push_back(e.id);
        } else {
            // close
            ensuref(!st.empty(),
                    "Closing interval id %d (%lld,%lld) with empty stack",
                    e.id, (long long)e.L, (long long)e.R);
            int top = st.back();
            ensuref(top == e.id,
                    "Partial overlap detected: closing interval id %d (%lld,%lld), "
                    "but top of stack is id %d (%lld,%lld)",
                    e.id, (long long)e.L, (long long)e.R,
                    top,
                    (long long)interval[top].first,
                    (long long)interval[top].second);
            st.pop_back();
        }
    }
    ensuref(st.empty(), "Unclosed intervals remain on stack");

    inf.readEof();
    return 0;
}

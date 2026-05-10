#include "testlib.h"
#include <vector>
#include <string>
#include <set>
#include <algorithm>
#include <cctype>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read n (number of test cases)
    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int test = 0; test < n; ++test) {
        setTestCase(test + 1);

        // 2. Read m (number of queues)
        int m = inf.readInt(1, 10, "m");
        inf.readEoln();

        // For checking that all queue ids are unique and in [0, m-1]
        vector<bool> queue_id_seen(m, false);

        // For simulating queue sizes (to check at most 30 customers at any time)
        vector<int> queue_size(m, 0);

        for (int q = 0; q < m; ++q) {
            // 3. Read queue info: i, i_c, e_c
            int i = inf.readInt(0, m - 1, "i");
            inf.readSpace();
            int i_c = inf.readInt(1, 30, "i_c");
            inf.readSpace();
            int e_c = inf.readInt(0, 10, "e_c");
            inf.readEoln();

            ensuref(!queue_id_seen[i], "Queue id %d appears more than once in test case %d", i, test + 1);
            queue_id_seen[i] = true;

            // 4. Read i_c positive integers: extra minutes for each customer
            vector<int> customers = inf.readInts(i_c, 0, 15, "customer_extra_minutes");
            inf.readEoln();

            queue_size[i] = i_c;
        }

        // 5. All queue ids must be present exactly once
        for (int i = 0; i < m; ++i) {
            ensuref(queue_id_seen[i], "Queue id %d missing in test case %d", i, test + 1);
        }

        // 6. Read v (number of events)
        int v = inf.readInt(0, 100, "v");
        inf.readEoln();

        // For checking that no two events have the same t_v
        set<int> event_times;

        // For simulating queue sizes
        // (already initialized above)

        for (int ev = 0; ev < v; ++ev) {
            string event_type = inf.readToken("[a-z]+", "event_type");
            ensuref(event_type == "join" || event_type == "change",
                "Unknown event type '%s' at event %d in test case %d", event_type.c_str(), ev + 1, test + 1);

            inf.readSpace();

            if (event_type == "join") {
                // join t_v i_v c_v
                int t_v = inf.readInt(1, 300, "t_v");
                inf.readSpace();
                int i_v = inf.readInt(0, m - 1, "i_v");
                inf.readSpace();
                int c_v = inf.readInt(0, 15, "c_v");
                inf.readEoln();

                // No more than one event at the same minute
                ensuref(event_times.insert(t_v).second,
                    "Multiple events at the same minute %d in test case %d", t_v, test + 1);

                // Simulate: add customer to queue i_v
                queue_size[i_v]++;
                ensuref(queue_size[i_v] <= 30,
                    "Queue %d exceeds 30 customers after join event at minute %d in test case %d (size now %d)",
                    i_v, t_v, test + 1, queue_size[i_v]);
            } else {
                // change t_v i_v e_v
                int t_v = inf.readInt(1, 300, "t_v");
                inf.readSpace();
                int i_v = inf.readInt(0, m - 1, "i_v");
                inf.readSpace();
                int e_v = inf.readInt(0, 10, "e_v");
                inf.readEoln();

                // No more than one event at the same minute
                ensuref(event_times.insert(t_v).second,
                    "Multiple events at the same minute %d in test case %d", t_v, test + 1);

                // No change to queue size
            }
        }
    }

    inf.readEof();
}

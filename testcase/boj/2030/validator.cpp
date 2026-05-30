#include "testlib.h"
#include <algorithm>
#include <deque>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct Event {
    string type;
    int t;
    int queue;
    int value;
};

struct QueueState {
    int baseTime;
    int currentStart;
    deque<int> customers;
};

static void serveUntil(QueueState& queue, int t) {
    while (!queue.customers.empty()) {
        int finish = queue.currentStart + queue.baseTime + queue.customers.front();
        if (finish > t) {
            break;
        }
        queue.customers.pop_front();
        queue.currentStart = finish;
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 10000, "n");
    inf.readEoln();

    for (int test = 0; test < n; ++test) {
        setTestCase(test + 1);

        int m = inf.readInt(1, 10, "m");
        inf.readEoln();

        vector<bool> queue_id_seen(m, false);
        vector<QueueState> queues(m);

        for (int q = 0; q < m; ++q) {
            int i = inf.readInt(0, m - 1, "i");
            inf.readSpace();
            int i_c = inf.readInt(1, 30, "i_c");
            inf.readSpace();
            int e_c = inf.readInt(0, 10, "e_c");
            inf.readEoln();

            ensuref(!queue_id_seen[i], "Queue id %d appears more than once in test case %d", i, test + 1);
            queue_id_seen[i] = true;

            vector<int> customers = inf.readInts(i_c, 0, 15, "customer_extra_minutes");
            inf.readEoln();

            queues[i].baseTime = e_c;
            queues[i].currentStart = 0;
            queues[i].customers.assign(customers.begin(), customers.end());
        }

        for (int i = 0; i < m; ++i) {
            ensuref(queue_id_seen[i], "Queue id %d missing in test case %d", i, test + 1);
        }

        int v = inf.readInt(0, 100, "v");
        inf.readEoln();

        set<int> event_times;
        vector<Event> events;

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

                ensuref(event_times.insert(t_v).second,
                    "Multiple events at the same minute %d in test case %d", t_v, test + 1);
                events.push_back({event_type, t_v, i_v, c_v});
            } else {
                int t_v = inf.readInt(1, 300, "t_v");
                inf.readSpace();
                int i_v = inf.readInt(0, m - 1, "i_v");
                inf.readSpace();
                int e_v = inf.readInt(0, 10, "e_v");
                inf.readEoln();

                ensuref(event_times.insert(t_v).second,
                    "Multiple events at the same minute %d in test case %d", t_v, test + 1);
                events.push_back({event_type, t_v, i_v, e_v});
            }
        }

        sort(events.begin(), events.end(), [](const Event& lhs, const Event& rhs) {
            return lhs.t < rhs.t;
        });

        for (const Event& event : events) {
            QueueState& queue = queues[event.queue];
            serveUntil(queue, event.t);

            if (event.type == "join") {
                bool wasEmpty = queue.customers.empty();
                queue.customers.push_back(event.value);
                if (wasEmpty) {
                    queue.currentStart = event.t;
                }
                ensuref(queue.customers.size() <= 30,
                    "Queue %d exceeds 30 customers after join event at minute %d in test case %d (size now %d)",
                    event.queue, event.t, test + 1, int(queue.customers.size()));
            } else {
                queue.baseTime = event.value;
                if (!queue.customers.empty()) {
                    queue.currentStart = event.t;
                }
            }
        }
    }

    inf.readEof();
}

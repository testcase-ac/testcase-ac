#include "testlib.h"
#include <set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read number of events
    int N = inf.readInt(1, 200000, "N");
    inf.readEoln();

    // Track joined students and ensure uniqueness of (A,B)
    int join_count = 0;
    set<pair<long long, long long>> seen;
    
    for (int event = 1; event <= N; event++) {
        // Read event type: "D" or "P"
        string type = inf.readToken("[DP]", "event_type");
        if (type == "D") {
            // New student joins
            inf.readSpace();
            long long A = inf.readLong(1LL, 2000000000LL, "A");
            inf.readSpace();
            long long B = inf.readLong(1LL, 2000000000LL, "B");
            inf.readEoln();

            // Ensure no duplicate (A,B)
            pair<long long, long long> p = make_pair(A, B);
            ensuref(!seen.count(p),
                    "Duplicate student stats at event %d: (A=%lld, B=%lld) already exists",
                    event, A, B);
            seen.insert(p);

            join_count++;
        } else {
            // Query about i-th joined student
            inf.readSpace();
            // i must be between 1 and join_count
            int i = inf.readInt(1, join_count, "i");
            inf.readEoln();
            // No other validation for query
        }
    }

    inf.readEof();
    return 0;
}

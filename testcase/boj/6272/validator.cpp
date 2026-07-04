#include "testlib.h"

#include <map>
#include <string>
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int totalN = 0;
    int caseIndex = 1;
    while (true) {
        int n = inf.readInt(0, 200, "n");
        inf.readEoln();

        if (n == 0) {
            break;
        }

        setTestCase(caseIndex++);
        totalN += n;
        // CHECK: the statement has no test-case count; cap aggregate input at one
        // largest case because each case has n <= 200 and cases are independent.
        ensuref(totalN <= 200, "sum of n exceeds practical cap: %d", totalN);

        vector<string> names;
        vector<int> parent(n, -1);
        map<string, int> id;

        string root = inf.readToken("[A-Za-z]{1,100}", "big_boss");
        inf.readEoln();
        id[root] = 0;
        names.push_back(root);

        auto getId = [&](const string& name) {
            auto it = id.find(name);
            if (it != id.end()) {
                return it->second;
            }
            int next = static_cast<int>(names.size());
            ensuref(next < n, "more than n distinct employee names");
            id[name] = next;
            names.push_back(name);
            return next;
        };

        for (int i = 1; i < n; ++i) {
            string employee = inf.readToken("[A-Za-z]{1,100}", "employee");
            inf.readSpace();
            string boss = inf.readToken("[A-Za-z]{1,100}", "boss");
            inf.readEoln();

            int employeeId = getId(employee);
            int bossId = getId(boss);
            ensuref(employeeId != bossId, "employee is their own boss: %s", employee.c_str());
            ensuref(parent[employeeId] == -1,
                    "employee has more than one boss: %s", employee.c_str());
            parent[employeeId] = bossId;
        }

        ensuref(static_cast<int>(names.size()) == n,
                "expected exactly %d distinct employee names, found %d",
                n, static_cast<int>(names.size()));
        ensuref(parent[0] == -1, "Big Boss must not have a boss");
        for (int i = 1; i < n; ++i) {
            ensuref(parent[i] != -1, "employee has no boss: %s", names[i].c_str());
        }

        for (int start = 0; start < n; ++start) {
            vector<int> seen(n, 0);
            int current = start;
            while (current != -1) {
                ensuref(!seen[current], "cycle in hierarchy involving %s", names[current].c_str());
                seen[current] = 1;
                current = parent[current];
            }
        }
    }

    inf.readEof();
}

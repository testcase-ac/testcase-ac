#include "testlib.h"

#include <vector>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int e = inf.readInt(1, 100000, "E");
    inf.readEoln();

    vector<int> manager(e + 1);
    int director = -1;
    for (int i = 1; i <= e; ++i) {
        manager[i] = inf.readInt(-1, e, "m_i");
        inf.readSpace();
        inf.readInt(1, 100000, "r_i");
        inf.readSpace();
        inf.readInt(1, 100000, "t_i");
        inf.readEoln();

        if (manager[i] == -1) {
            ensuref(director == -1, "multiple directors: employees %d and %d", director, i);
            director = i;
        } else {
            ensuref(manager[i] >= 1, "manager of employee %d must be -1 or between 1 and E", i);
            ensuref(manager[i] != i, "employee %d cannot be their own manager", i);
        }
    }

    ensuref(director != -1, "there must be exactly one engineering director");

    vector<int> state(e + 1, 0);
    for (int i = 1; i <= e; ++i) {
        int current = i;
        vector<int> path;
        while (current != -1 && state[current] == 0) {
            state[current] = i;
            path.push_back(current);
            current = manager[current];
        }

        ensuref(current == -1 || state[current] != i,
                "manager chain starting at employee %d contains a cycle", i);

        for (int employee : path) {
            state[employee] = -1;
        }
    }

    inf.readEof();
}

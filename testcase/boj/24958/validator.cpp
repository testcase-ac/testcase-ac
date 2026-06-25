#include "testlib.h"

#include <set>
#include <string>

using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 100000, "n");
    inf.readEoln();

    set<string> tickets;
    for (int i = 0; i < n; ++i) {
        string ticket = inf.readToken("[0-9]{6}", "ticket");
        inf.readEoln();

        ensuref(tickets.insert(ticket).second,
                "duplicate ticket at index %d: %s", i + 1, ticket.c_str());
    }

    inf.readEof();
}

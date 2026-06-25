#include "testlib.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

string readIdentifier(const string& name) {
    return inf.readToken("[a-zA-Z0-9]{1,20}::[a-zA-Z0-9]{1,20}", name);
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int n = inf.readInt(1, 400, "N");
    inf.readEoln();

    set<string> defined;
    set<string> mentioned;
    vector<vector<string>> callers(n);

    for (int i = 0; i < n; ++i) {
        string method = readIdentifier("method_id");
        ensuref(defined.insert(method).second,
                "duplicate method identifier at method %d: %s", i + 1, method.c_str());
        mentioned.insert(method);

        inf.readSpace();
        int k = inf.readInt(0, n, "k_i");
        inf.readEoln();

        set<string> callerSet;
        for (int j = 0; j < k; ++j) {
            if (j > 0) {
                inf.readSpace();
            }
            string caller = readIdentifier("caller_id");
            ensuref(callerSet.insert(caller).second,
                    "duplicate caller in method %d list: %s", i + 1, caller.c_str());
            callers[i].push_back(caller);
            mentioned.insert(caller);
        }
        inf.readEoln();
    }

    ensuref((int)mentioned.size() == n,
            "there must be exactly N different method identifiers mentioned, found %d",
            (int)mentioned.size());
    for (const auto& list : callers) {
        for (const string& caller : list) {
            ensuref(defined.count(caller),
                    "caller identifier is not described as a method: %s", caller.c_str());
        }
    }

    inf.readEof();
}

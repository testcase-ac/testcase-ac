#include "testlib.h"
#include <string>
#include <unordered_set>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read C and N
    int C = inf.readInt(1, 4000, "C");
    inf.readSpace();
    int N = inf.readInt(1, 4000, "N");
    inf.readEoln();

    // Read C color names, check lowercase-only, length <=1000, distinct
    unordered_set<string> colors;
    colors.reserve(C * 2);
    for (int i = 0; i < C; i++) {
        // each color: lowercase letters only, length 1..1000
        string col = inf.readLine("[a-z]{1,1000}", "color_name");
        bool inserted = colors.insert(col).second;
        ensuref(inserted, "Duplicate color name: %s", col.c_str());
    }

    // Read N nicknames, check lowercase-only, length <=1000, distinct
    unordered_set<string> names;
    names.reserve(N * 2);
    for (int i = 0; i < N; i++) {
        string nick = inf.readLine("[a-z]{1,1000}", "nickname");
        bool inserted = names.insert(nick).second;
        ensuref(inserted, "Duplicate nickname: %s", nick.c_str());
    }

    // Read Q
    int Q = inf.readInt(1, 20000, "Q");
    inf.readEoln();

    // Read Q team names, check lowercase-only, length <=2000, distinct
    unordered_set<string> teams;
    teams.reserve(Q * 2);
    for (int i = 0; i < Q; i++) {
        string t = inf.readLine("[a-z]{1,2000}", "team_name");
        bool inserted = teams.insert(t).second;
        ensuref(inserted, "Duplicate team name: %s", t.c_str());
    }

    inf.readEof();
    return 0;
}

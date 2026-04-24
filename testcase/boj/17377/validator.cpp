#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

static vector<string> split_by_space(const string &s) {
    vector<string> res;
    int n = s.size();
    string cur;
    for (int i = 0; i < n; i++) {
        if (s[i] == ' ') {
            res.push_back(cur);
            cur.clear();
        } else {
            cur.push_back(s[i]);
        }
    }
    res.push_back(cur);
    return res;
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // Read A, B, C
    int A = inf.readInt(1, 100, "A");
    inf.readSpace();
    int B = inf.readInt(1, 100, "B");
    inf.readSpace();
    int C = inf.readInt(1, 100, "C");
    inf.readEoln();

    // Read N
    int N = inf.readInt(4, 100, "N");
    inf.readEoln();

    vector<string> names;
    vector<int> xs, ys;
    names.reserve(N);
    xs.reserve(N);
    ys.reserve(N);
    unordered_map<string,int> name_to_idx;
    int taxiGarageIdx = -1;

    for (int i = 0; i < N; i++) {
        string line = inf.readLine("[^]+", "place_line");
        // No leading/trailing spaces
        ensuref(!line.empty(), "Empty place line at index %d", i);
        ensuref(line.front() != ' ' && line.back() != ' ',
                "Leading or trailing space in place line %d: '%s'", i, line.c_str());
        // No consecutive spaces
        ensuref(line.find("  ") == string::npos,
                "Consecutive spaces in place line %d: '%s'", i, line.c_str());
        // Split by spaces
        vector<string> parts = split_by_space(line);
        ensuref(parts.size() >= 3, "Place line %d must have at least name and two numbers: '%s'", i, line.c_str());
        string sx = parts[parts.size()-2];
        string sy = parts[parts.size()-1];
        // parse integers
        for (char c : sx) ensuref(isdigit(c), "Non-digit in x-coordinate at place %d: '%s'", i, sx.c_str());
        for (char c : sy) ensuref(isdigit(c), "Non-digit in y-coordinate at place %d: '%s'", i, sy.c_str());
        int x = stoi(sx);
        int y = stoi(sy);
        ensuref(0 <= x && x <= 100, "x-coordinate out of range at place %d: %d", i, x);
        ensuref(0 <= y && y <= 100, "y-coordinate out of range at place %d: %d", i, y);
        // Reconstruct name
        string name = parts[0];
        for (int j = 1; j + 2 < (int)parts.size(); j++) {
            name.push_back(' ');
            name += parts[j];
        }
        // Name constraints
        ensuref((int)name.size() >= 1 && (int)name.size() <= 30,
                "Place name length invalid at place %d: '%s'", i, name.c_str());
        // Characters allowed
        for (int j = 0; j < (int)name.size(); j++) {
            char c = name[j];
            bool ok = (isalpha(c) || c == '\'' || c == ' ');
            ensuref(ok, "Invalid character in place name at index %d: '%s'", i, name.c_str());
        }
        // Unique names
        ensuref(!name_to_idx.count(name), "Duplicate place name at index %d: '%s'", i, name.c_str());
        name_to_idx[name] = i;
        names.push_back(name);
        xs.push_back(x);
        ys.push_back(y);
        if (name == "Taxi Garage") {
            taxiGarageIdx = i;
        }
    }
    ensuref(taxiGarageIdx != -1, "No place named 'Taxi Garage' found");

    // Read 3 gas stations
    set<string> gas_names;
    for (int i = 0; i < 3; i++) {
        string line = inf.readLine("[^]+", "gas_line");
        ensuref(!line.empty(), "Empty gas station line %d", i);
        ensuref(line.front() != ' ' && line.back() != ' ',
                "Leading or trailing space in gas station line %d: '%s'", i, line.c_str());
        ensuref(line.find("  ") == string::npos,
                "Consecutive spaces in gas station line %d: '%s'", i, line.c_str());
        vector<string> parts = split_by_space(line);
        ensuref(parts.size() >= 2, "Gas station line %d must have name and price: '%s'", i, line.c_str());
        string sp = parts.back();
        for (char c : sp) ensuref(isdigit(c),
                "Non-digit in gas station price at line %d: '%s'", i, sp.c_str());
        int P = stoi(sp);
        ensuref(1 <= P && P <= 100,
                "Gas station price out of range at line %d: %d", i, P);
        // reconstruct name
        string gname = parts[0];
        for (int j = 1; j + 1 < (int)parts.size(); j++) {
            gname.push_back(' ');
            gname += parts[j];
        }
        // name must be one of places
        ensuref(name_to_idx.count(gname),
                "Gas station name not a known place at line %d: '%s'", i, gname.c_str());
        ensuref(gname != "Taxi Garage",
                "Gas station cannot be 'Taxi Garage' at line %d", i);
        ensuref(!gas_names.count(gname),
                "Duplicate gas station name at line %d: '%s'", i, gname.c_str());
        gas_names.insert(gname);
    }

    // Read K
    int K = inf.readInt(1, 10000, "K");
    inf.readEoln();

    int current = taxiGarageIdx;
    const string prefix_go = "Go to ";
    const string prefix_pick = "Pickup a passenger going to ";

    for (int i = 0; i < K; i++) {
        string cmd = inf.readLine("[^]+", "command");
        ensuref(!cmd.empty(), "Empty command at line %d", i);
        ensuref(cmd.front() != ' ' && cmd.back() != ' ',
                "Leading or trailing space in command %d: '%s'", i, cmd.c_str());
        ensuref(cmd.find("  ") == string::npos,
                "Consecutive spaces in command %d: '%s'", i, cmd.c_str());
        // Must end with '.'
        ensuref(cmd.back() == '.',
                "Command does not end with '.' at line %d: '%s'", i, cmd.c_str());
        bool matched = false;
        // Try Go to
        if ((int)cmd.size() > (int)prefix_go.size() && 
            cmd.compare(0, prefix_go.size(), prefix_go) == 0) {
            string pname = cmd.substr(prefix_go.size(), cmd.size() - prefix_go.size() - 1);
            ensuref(!pname.empty(),
                    "Empty destination in 'Go to' at line %d", i);
            // pname must be known place
            auto it = name_to_idx.find(pname);
            ensuref(it != name_to_idx.end(),
                    "Unknown place '%s' in 'Go to' at line %d", pname.c_str(), i);
            // update current
            current = it->second;
            matched = true;
        }
        // Try Pickup
        if (!matched && (int)cmd.size() > (int)prefix_pick.size() &&
            cmd.compare(0, prefix_pick.size(), prefix_pick) == 0) {
            string pname = cmd.substr(prefix_pick.size(), cmd.size() - prefix_pick.size() - 1);
            ensuref(!pname.empty(),
                    "Empty destination in 'Pickup' at line %d", i);
            auto it = name_to_idx.find(pname);
            ensuref(it != name_to_idx.end(),
                    "Unknown place '%s' in 'Pickup' at line %d", pname.c_str(), i);
            int dest = it->second;
            ensuref(dest != current,
                    "Pickup destination equals current location at line %d: '%s'", i, pname.c_str());
            ensuref(dest != taxiGarageIdx,
                    "Pickup destination cannot be 'Taxi Garage' at line %d", i);
            matched = true;
        }
        ensuref(matched,
                "Command does not match any valid pattern at line %d: '%s'", i, cmd.c_str());
    }

    inf.readEof();
    return 0;
}

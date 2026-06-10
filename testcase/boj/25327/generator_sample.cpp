#include "testlib.h"

#include <array>
#include <string>
#include <vector>

using namespace std;

namespace {

const vector<string> subjects = {"kor", "eng", "math"};
const vector<string> fruits = {"apple", "pear", "orange"};
const vector<string> colors = {"red", "blue", "green"};

using Triple = array<string, 3>;

Triple randomStudent() {
    return {rnd.any(subjects), rnd.any(fruits), rnd.any(colors)};
}

vector<Triple> allStudents() {
    vector<Triple> triples;
    for (const string& subject : subjects) {
        for (const string& fruit : fruits) {
            for (const string& color : colors) {
                triples.push_back({subject, fruit, color});
            }
        }
    }
    return triples;
}

Triple wildcardQueryFrom(const Triple& base, int wildcardMask) {
    Triple query = base;
    for (int bit = 0; bit < 3; ++bit) {
        if (wildcardMask & (1 << bit)) {
            query[bit] = "-";
        }
    }
    return query;
}

void printTriple(const Triple& triple) {
    println(triple[0], triple[1], triple[2]);
}

} // namespace

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<Triple> students;
    vector<Triple> queries;
    vector<Triple> universe = allStudents();

    int mode = rnd.next(0, 3);
    int n = rnd.next(1, 36);
    int m = rnd.next(1, 36);

    if (mode == 0) {
        Triple repeated = randomStudent();
        students.assign(n, repeated);
    } else if (mode == 1) {
        shuffle(universe.begin(), universe.end());
        n = rnd.next(9, 27);
        for (int i = 0; i < n; ++i) {
            students.push_back(universe[i]);
        }
    } else if (mode == 2) {
        vector<Triple> favored;
        shuffle(universe.begin(), universe.end());
        int favoredCount = rnd.next(2, 5);
        for (int i = 0; i < favoredCount; ++i) {
            favored.push_back(universe[i]);
        }
        for (int i = 0; i < n; ++i) {
            if (rnd.next(0, 99) < 75) {
                students.push_back(rnd.any(favored));
            } else {
                students.push_back(randomStudent());
            }
        }
    } else {
        n = rnd.next(1, 12);
        for (int i = 0; i < n; ++i) {
            students.push_back(randomStudent());
        }
    }

    m = rnd.next(1, 36);
    for (int i = 0; i < m; ++i) {
        Triple base = rnd.next(0, 99) < 70 ? rnd.any(students) : rnd.any(universe);
        int wildcardMask;
        if (mode == 3 && i < 8) {
            wildcardMask = i;
        } else {
            wildcardMask = rnd.next(0, 7);
        }
        queries.push_back(wildcardQueryFrom(base, wildcardMask));
    }

    println(static_cast<int>(students.size()), static_cast<int>(queries.size()));
    for (const Triple& student : students) {
        printTriple(student);
    }
    for (const Triple& query : queries) {
        printTriple(query);
    }

    return 0;
}

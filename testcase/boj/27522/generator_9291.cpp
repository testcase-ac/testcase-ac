#include "testlib.h"
using namespace std;

struct Racer {
    int ms;
    char team;
};

string formatTime(int total_ms) {
    int M = total_ms / 60000;
    int rem = total_ms % 60000;
    int S = rem / 1000;
    int ms = rem % 1000;
    char buf[20];
    sprintf(buf, "%d:%02d:%03d", M, S, ms);
    return string(buf);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    const int MIN_MS = 1;
    const int MAX_MS = (9 * 60 + 59) * 1000 + 999; // 9:59:999 -> 599999

    // Generate 8 distinct finish times with some variability
    vector<int> times;
    int styleTime = rnd.next(1, 3);

    if (styleTime == 1) {
        // Clustered around a base time, steadily increasing
        int baseM = rnd.next(0, 2);
        int baseS = rnd.next(0, 50);
        int baseMs = rnd.next(0, 999);
        int current = (baseM * 60 + baseS) * 1000 + baseMs;
        if (current < MIN_MS) current = MIN_MS;

        times.push_back(current);
        for (int i = 1; i < 8; i++) {
            int deltaS = rnd.next(0, 3);
            int deltaMs = rnd.next(1, 250);
            current += deltaS * 1000 + deltaMs;
            if (current > MAX_MS) current = MAX_MS - (8 - i); // keep room
            times.push_back(current);
        }
    } else if (styleTime == 2) {
        // Uniform random distinct times in full range
        set<int> st;
        while ((int)st.size() < 8) {
            int x = rnd.next(MIN_MS, MAX_MS);
            st.insert(x);
        }
        for (int x : st) times.push_back(x);
    } else {
        // Very close sequential times (1 ms apart)
        int start = rnd.next(MIN_MS, MAX_MS - 7);
        for (int i = 0; i < 8; i++) times.push_back(start + i);
    }

    sort(times.begin(), times.end());

    // Team patterns in order of finishing positions (1st..8th), each with 4R and 4B
    vector<string> patterns = {
        "RBRBRBRB",
        "BRBRBRBR",
        "RRRRBBBB",
        "BBBBRRRR",
        "RRBBRBBR",
        "BRRBBRRB",
        "RBBRRBRB"
    };

    string pattern = patterns[rnd.next(0, (int)patterns.size() - 1)];

    vector<Racer> racers;
    for (int i = 0; i < 8; i++) {
        racers.push_back({times[i], pattern[i]});
    }

    // Shuffle input order so it's not sorted by time
    shuffle(racers.begin(), racers.end());

    // Output 8 lines: M:SS:sss <team>
    for (const auto &r : racers) {
        string t = formatTime(r.ms);
        printf("%s %c\n", t.c_str(), r.team);
    }

    return 0;
}

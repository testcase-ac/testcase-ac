#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    vector<int> commands;
    int mode = rnd.next(1, 4);

    if (mode == 1) {
        int preferred = rnd.next(1, 3);
        for (int i = 0; i < 10; ++i) {
            if (rnd.next(1, 100) <= 70)
                commands.push_back(preferred);
            else
                commands.push_back(rnd.next(1, 3));
        }
    } else if (mode == 2) {
        commands.assign(10, rnd.next(1, 3));
        int changes = rnd.next(0, 3);
        for (int i = 0; i < changes; ++i)
            commands[rnd.next(0, 9)] = rnd.next(1, 3);
    } else if (mode == 3) {
        commands = {1, 1, 2, 2, 3, 3, rnd.next(1, 3), rnd.next(1, 3), rnd.next(1, 3), rnd.next(1, 3)};
        shuffle(commands.begin(), commands.end());
    } else {
        int target = rnd.next(0, 3);
        int sum = 0;
        for (int i = 0; i < 9; ++i) {
            int command = rnd.next(1, 3);
            commands.push_back(command);
            sum = (sum + command) % 4;
        }

        vector<int> candidates;
        for (int command = 1; command <= 3; ++command) {
            if ((sum + command) % 4 == target)
                candidates.push_back(command);
        }
        commands.push_back(candidates.empty() ? rnd.next(1, 3) : rnd.any(candidates));
    }

    for (int command : commands)
        println(command);

    return 0;
}

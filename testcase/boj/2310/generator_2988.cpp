#include "testlib.h"
#include <vector>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of mazes
    int mazes = rnd.next(2, 5);
    for (int m = 0; m < mazes; m++) {
        // Number of rooms
        int n = rnd.next(1, 10);
        println(n);

        // Hyper-parameter for edge density
        double edgeProb = rnd.next();
        // Build directed edges
        vector<vector<int>> adj(n + 1);
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (i != j && rnd.next() < edgeProb) {
                    adj[i].push_back(j);
                }
            }
            shuffle(adj[i].begin(), adj[i].end());
        }

        // Generate room types and amounts
        for (int i = 1; i <= n; i++) {
            // Decide room type
            double p = rnd.next();
            char type;
            int amount = 0;
            if (p < 0.3) {
                type = 'E';
                amount = 0;
            } else if (p < 0.65) {
                type = 'L';
                // Leprechaun refill: sometimes small, sometimes large
                if (rnd.next() < 0.5) amount = rnd.wnext(500, -1);
                else amount = rnd.wnext(500, 1);
                if (amount == 0) amount = 1;
            } else {
                type = 'T';
                // Troll toll: sometimes small, sometimes large
                if (rnd.next() < 0.5) amount = rnd.wnext(500, -1);
                else amount = rnd.wnext(500, 1);
                if (amount == 0) amount = 1;
            }
            // Print the room line
            printf("%c %d", type, amount);
            for (int v : adj[i]) {
                printf(" %d", v);
            }
            printf(" 0\n");
        }
    }
    // Terminate input
    println(0);
    return 0;
}

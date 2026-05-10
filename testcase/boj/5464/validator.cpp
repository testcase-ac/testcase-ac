#include "testlib.h"
#include <vector>
#include <queue>
#include <set>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    // 1. Read N and M
    int N = inf.readInt(1, 100, "N");
    inf.readSpace();
    int M = inf.readInt(1, 2000, "M");
    inf.readEoln();

    // 2. Read Rs (parking spot rates)
    vector<int> Rs(N+1); // 1-based
    for (int i = 1; i <= N; ++i) {
        Rs[i] = inf.readInt(1, 100, "Rs");
        inf.readEoln();
    }

    // 3. Read Wk (car weights)
    vector<int> Wk(M+1); // 1-based
    for (int k = 1; k <= M; ++k) {
        Wk[k] = inf.readInt(1, 10000, "Wk");
        inf.readEoln();
    }

    // 4. Read 2*M events
    vector<int> events(2*M);
    set<int> entered, exited;
    vector<int> enter_count(M+1, 0), exit_count(M+1, 0);
    for (int i = 0; i < 2*M; ++i) {
        events[i] = inf.readInt(-M, M, "event");
        inf.readEoln();

        int v = events[i];
        if (v == 0) {
            ensuref(false, "Event at line %d is zero, which is invalid", N+M+i+1);
        }
        int abs_v = abs(v);
        ensuref(1 <= abs_v && abs_v <= M, "Event at line %d refers to car %d, which is out of range 1..M", N+M+i+1, abs_v);

        if (v > 0) {
            enter_count[abs_v]++;
            ensuref(enter_count[abs_v] <= 1, "Car %d enters more than once (at event index %d)", abs_v, i+1);
        } else {
            exit_count[abs_v]++;
            ensuref(exit_count[abs_v] <= 1, "Car %d exits more than once (at event index %d)", abs_v, i+1);
        }
    }
    // Each car must enter and exit exactly once
    for (int k = 1; k <= M; ++k) {
        ensuref(enter_count[k] == 1, "Car %d does not enter exactly once (entered %d times)", k, enter_count[k]);
        ensuref(exit_count[k] == 1, "Car %d does not exit exactly once (exited %d times)", k, exit_count[k]);
    }

    // 5. Simulate the process to check global constraints
    // - No car exits before entering
    // - No car leaves from waiting queue (i.e., all cars that exit must have entered and parked)
    // - No car is left waiting at the end
    // - No spot is double-occupied
    // - No car parks twice

    // parking_spots[s] = car number occupying spot s (1-based), 0 if empty
    vector<int> parking_spots(N+1, 0);
    // car_in_spot[car] = spot number where car is parked, 0 if not parked
    vector<int> car_in_spot(M+1, 0);
    // waiting queue: car numbers waiting to park
    queue<int> waiting;

    // For checking that no car parks twice
    vector<bool> has_parked(M+1, false);

    for (int i = 0; i < 2*M; ++i) {
        int v = events[i];
        if (v > 0) {
            int car = v;
            // Try to park immediately if possible
            int spot = 0;
            for (int s = 1; s <= N; ++s) {
                if (parking_spots[s] == 0) {
                    spot = s;
                    break;
                }
            }
            if (spot != 0) {
                // Park at spot
                parking_spots[spot] = car;
                car_in_spot[car] = spot;
                ensuref(!has_parked[car], "Car %d parks more than once (event index %d)", car, i+1);
                has_parked[car] = true;
            } else {
                // Wait in queue
                waiting.push(car);
            }
        } else {
            int car = -v;
            // Car must be parked
            int spot = car_in_spot[car];
            ensuref(spot != 0, "Car %d tries to leave but is not parked (event index %d)", car, i+1);
            // Free the spot
            parking_spots[spot] = 0;
            car_in_spot[car] = 0;
            // After freeing, if someone is waiting, park them
            if (!waiting.empty()) {
                int next_car = waiting.front(); waiting.pop();
                // Find the smallest available spot
                int new_spot = 0;
                for (int s = 1; s <= N; ++s) {
                    if (parking_spots[s] == 0) {
                        new_spot = s;
                        break;
                    }
                }
                ensuref(new_spot != 0, "No available spot for waiting car %d after car %d leaves (event index %d)", next_car, car, i+1);
                parking_spots[new_spot] = next_car;
                car_in_spot[next_car] = new_spot;
                ensuref(!has_parked[next_car], "Car %d parks more than once (from waiting queue, event index %d)", next_car, i+1);
                has_parked[next_car] = true;
            }
        }
    }

    // At the end, all cars should have exited, so all spots must be empty
    for (int s = 1; s <= N; ++s) {
        ensuref(parking_spots[s] == 0, "Spot %d is not empty at the end", s);
    }
    // No car should be left in waiting queue
    ensuref(waiting.empty(), "There are cars left waiting at the end");

    inf.readEof();
}

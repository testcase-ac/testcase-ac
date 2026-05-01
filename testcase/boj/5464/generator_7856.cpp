#include "testlib.h"
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    // Number of parking spaces
    int N = rnd.next(1, 10);
    // Number of cars, bias to have queue situations
    int maxM = min(15, N * 2);
    int M;
    if (rnd.next(0, 9) < 7) {
        M = rnd.next(N, maxM);
    } else {
        M = rnd.next(1, maxM);
    }

    // Generate rates for each parking space
    vector<int> R(N);
    for (int i = 0; i < N; i++) {
        if (rnd.next(0, 1) == 0)
            R[i] = rnd.next(1, 10);
        else
            R[i] = rnd.next(10, 100);
    }

    // Generate weights for each car
    vector<int> W(M);
    for (int i = 0; i < M; i++) {
        if (rnd.next(0, 1) == 0)
            W[i] = rnd.next(1, 1000);
        else
            W[i] = rnd.next(1000, 10000);
    }

    // Prepare structures for event simulation
    vector<int> notArrived(M);
    for (int i = 0; i < M; i++) notArrived[i] = i + 1;
    vector<int> parked;
    queue<int> waiting;
    int freeSpaces = N;

    vector<int> events;
    events.reserve(2 * M);

    while ((int)events.size() < 2 * M) {
        bool canArrive = !notArrived.empty();
        bool canDepart = !parked.empty();
        if (canArrive && (!canDepart || rnd.next(0, 1) == 0)) {
            // Arrival event
            int idx = rnd.next(0, (int)notArrived.size() - 1);
            int car = notArrived[idx];
            notArrived[idx] = notArrived.back();
            notArrived.pop_back();
            // Simulate parking logic
            if (freeSpaces > 0 && waiting.empty()) {
                parked.push_back(car);
                freeSpaces--;
            } else {
                waiting.push(car);
            }
            events.push_back(car);
        } else {
            // Departure event
            int idx = rnd.next(0, (int)parked.size() - 1);
            int car = parked[idx];
            parked[idx] = parked.back();
            parked.pop_back();
            freeSpaces++;
            // After departure, a waiting car may park
            if (!waiting.empty()) {
                int nxt = waiting.front();
                waiting.pop();
                parked.push_back(nxt);
                freeSpaces--;
            }
            events.push_back(-car);
        }
    }

    // Output the generated test case
    println(N, M);
    for (int i = 0; i < N; i++) println(R[i]);
    for (int i = 0; i < M; i++) println(W[i]);
    for (int x : events) println(x);

    return 0;
}

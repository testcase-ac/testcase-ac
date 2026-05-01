#include "testlib.h"
using namespace std;

struct Edge {
    int u, v;
    char c;
};

char randomColor() {
    string s = "RGB";
    return s[rnd.next(0, 2)];
}

void fillCards(vector<char> &cards, int patternType, char allColor = 0) {
    int n = (int)cards.size();
    if (patternType == 0) {
        char c = allColor ? allColor : randomColor();
        for (int i = 0; i < n; ++i) cards[i] = c;
    } else if (patternType == 1) {
        string pattern = "RGB";
        int offset = rnd.next(0, 2);
        for (int i = 0; i < n; ++i)
            cards[i] = pattern[(i + offset) % 3];
    } else {
        for (int i = 0; i < n; ++i)
            cards[i] = randomColor();
    }
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int scenario = rnd.next(0, 6); // 7 scenarios: 0..6

    int N = 0, M = 0;
    vector<char> cards;
    vector<Edge> edges;

    switch (scenario) {
        case 0: {
            // Scenario 0: no edges, starting node isolated (deg(1) = 0)
            M = rnd.next(1, 5);
            N = rnd.next(1, 10);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);
            // edges empty
            break;
        }
        case 1: {
            // Scenario 1: simple chain 1-2-...-M
            M = rnd.next(2, 10);
            N = rnd.next(1, 20);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);

            for (int i = 1; i <= M - 1; ++i) {
                Edge e;
                e.u = i;
                e.v = i + 1;
                e.c = randomColor();
                edges.push_back(e);
            }
            break;
        }
        case 2: {
            // Scenario 2: star centered at 1
            M = rnd.next(3, 10);
            N = rnd.next(1, 20);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);

            for (int v = 2; v <= M; ++v) {
                Edge e;
                e.u = 1;
                e.v = v;
                e.c = randomColor();
                edges.push_back(e);
            }
            break;
        }
        case 3: {
            // Scenario 3: cycle including 1, possibly forces revisits for long N
            M = rnd.next(3, 8);
            N = rnd.next(M, 20);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);

            for (int i = 1; i <= M - 1; ++i) {
                Edge e;
                e.u = i;
                e.v = i + 1;
                e.c = randomColor();
                edges.push_back(e);
            }
            // close the cycle M-1
            Edge e;
            e.u = M;
            e.v = 1;
            e.c = randomColor();
            edges.push_back(e);

            break;
        }
        case 4: {
            // Scenario 4: small complete graph (dense)
            M = rnd.next(3, 6); // edges up to 15
            N = rnd.next(1, 20);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);

            for (int i = 1; i <= M; ++i) {
                for (int j = i + 1; j <= M; ++j) {
                    Edge e;
                    e.u = i;
                    e.v = j;
                    e.c = randomColor();
                    edges.push_back(e);
                }
            }
            break;
        }
        case 5: {
            // Scenario 5: random graph, controlled number of edges
            N = rnd.next(1, 25);
            M = rnd.next(2, 15);
            cards.assign(N, 'R');
            int patternType = rnd.next(0, 2);
            fillCards(cards, patternType);

            vector<pair<int,int>> allPairs;
            for (int i = 1; i <= M; ++i) {
                for (int j = i + 1; j <= M; ++j) {
                    allPairs.emplace_back(i, j);
                }
            }

            int maxEdges = (int)allPairs.size();
            int maxK = min(maxEdges, 25);
            int K = rnd.next(1, maxK);

            shuffle(allPairs.begin(), allPairs.end());
            allPairs.resize(K);

            for (auto &p : allPairs) {
                Edge e;
                e.u = p.first;
                e.v = p.second;
                e.c = randomColor();
                edges.push_back(e);
            }
            break;
        }
        case 6: {
            // Scenario 6: directedness / revisiting trap:
            // Only one edge 1-2, all cards same color as the edge.
            // Correct (undirected, revisits allowed): can go 1-2-1-2-... matching every card.
            // Wrong (directed or no revisits): much smaller score.
            M = 2;
            N = rnd.next(2, 15);

            char c = randomColor();
            cards.assign(N, 'R');
            fillCards(cards, 0, c); // all same color c

            Edge e;
            e.u = 1;
            e.v = 2;
            e.c = c;
            edges.push_back(e);

            break;
        }
    }

    int K = (int)edges.size();

    println(N);
    println(cards);
    println(M, K);
    for (const auto &e : edges) {
        println(e.u, e.v, e.c);
    }

    return 0;
}

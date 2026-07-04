#include "testlib.h"

#include <algorithm>
#include <string>
#include <vector>
using namespace std;

struct ActorState {
    int parent = -1;
    vector<int> children;
};

static void removeChild(vector<int>& children, int child) {
    children.erase(remove(children.begin(), children.end(), child), children.end());
}

static bool isDescendant(const vector<ActorState>& actors, int ancestor, int node) {
    for (int child : actors[ancestor].children) {
        if (child == node || isDescendant(actors, child, node)) {
            return true;
        }
    }
    return false;
}

static int pickActor(int count) {
    return rnd.next(1, count);
}

static int pickTargetActor(int count, bool allowWindow) {
    if (allowWindow && rnd.next(100) < 25) {
        return 0;
    }
    return pickActor(count);
}

static string actorName(int id) {
    if (id == 0) {
        return "Window";
    }
    return "A" + to_string(id);
}

static int smallCoord(int limit) {
    if (rnd.next(100) < 15) {
        return rnd.any(vector<int>{-100000, -50, -1, 0, 1, 50, 100000});
    }
    return rnd.next(-limit, limit);
}

static int smallSize(int limit) {
    if (rnd.next(100) < 15) {
        return rnd.any(vector<int>{0, 1, 2, 50, 100000});
    }
    return rnd.next(0, limit);
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);

    int w = rnd.next(3, 12);
    int h = rnd.next(3, 12);
    if (rnd.next(100) < 10) {
        w = rnd.next(45, 50);
        h = rnd.next(45, 50);
    }

    int actorCount = rnd.next(4, 14);
    vector<string> commands;
    vector<ActorState> actors(actorCount + 1);

    for (int id = 1; id <= actorCount; ++id) {
        commands.push_back("New " + actorName(id));
    }

    for (int id = 1; id <= actorCount; ++id) {
        commands.push_back("SetProperty " + actorName(id) + " SIZE " +
                           to_string(smallSize(w + 4)) + " " + to_string(smallSize(h + 4)));
        commands.push_back("SetProperty " + actorName(id) + " POSITION " +
                           to_string(smallCoord(w + 4)) + " " + to_string(smallCoord(h + 4)));
        if (rnd.next(100) < 70) {
            commands.push_back("SetProperty " + actorName(id) + " COLOR " + to_string(rnd.next(1, 9)));
        }
        if (rnd.next(100) < 55) {
            commands.push_back("SetProperty " + actorName(id) + " PARENT_ORIGIN " +
                               to_string(rnd.next(0, 1)) + " " + to_string(rnd.next(0, 1)));
        }
        if (rnd.next(100) < 55) {
            commands.push_back("SetProperty " + actorName(id) + " ANCHOR_POINT " +
                               to_string(rnd.next(0, 1)) + " " + to_string(rnd.next(0, 1)));
        }
    }

    int operations = rnd.next(18, 55);
    vector<string> properties = {
        "POSITION", "SIZE", "COLOR", "PARENT_ORIGIN", "ANCHOR_POINT", "SCREEN_POSITION",
    };

    for (int step = 0; step < operations; ++step) {
        int mode = rnd.next(100);
        if (mode < 35) {
            int parent = pickTargetActor(actorCount, true);
            vector<int> candidates;
            for (int child = 1; child <= actorCount; ++child) {
                if (child != parent && !isDescendant(actors, child, parent)) {
                    candidates.push_back(child);
                }
            }
            if (candidates.empty()) {
                --step;
                continue;
            }
            int child = rnd.any(candidates);
            if (actors[child].parent != -1) {
                removeChild(actors[actors[child].parent].children, child);
            }
            actors[child].parent = parent;
            actors[parent].children.push_back(child);
            commands.push_back("Add " + actorName(parent) + " " + actorName(child));
        } else if (mode < 50) {
            int parent = pickTargetActor(actorCount, true);
            int child = pickActor(actorCount);
            if (actors[child].parent == parent) {
                removeChild(actors[parent].children, child);
                actors[child].parent = -1;
            }
            commands.push_back("Remove " + actorName(parent) + " " + actorName(child));
        } else if (mode < 62) {
            int actor = pickActor(actorCount);
            if (actors[actor].parent != -1) {
                removeChild(actors[actors[actor].parent].children, actor);
                actors[actor].parent = -1;
            }
            commands.push_back("Unparent " + actorName(actor));
        } else if (mode < 82) {
            int actor = pickActor(actorCount);
            string property = rnd.any(vector<string>{"POSITION", "SIZE", "COLOR", "PARENT_ORIGIN", "ANCHOR_POINT"});
            if (property == "COLOR") {
                commands.push_back("SetProperty " + actorName(actor) + " COLOR " + to_string(rnd.next(1, 9)));
            } else if (property == "POSITION") {
                commands.push_back("SetProperty " + actorName(actor) + " POSITION " +
                                   to_string(smallCoord(w + 8)) + " " + to_string(smallCoord(h + 8)));
            } else if (property == "SIZE") {
                commands.push_back("SetProperty " + actorName(actor) + " SIZE " +
                                   to_string(smallSize(w + 8)) + " " + to_string(smallSize(h + 8)));
            } else {
                commands.push_back("SetProperty " + actorName(actor) + " " + property + " " +
                                   to_string(rnd.next(0, 1)) + " " + to_string(rnd.next(0, 1)));
            }
        } else {
            int actor = pickActor(actorCount);
            commands.push_back("GetProperty " + actorName(actor) + " " + rnd.any(properties));
        }
    }

    commands.push_back("GetProperty " + actorName(pickActor(actorCount)) + " SCREEN_POSITION");

    println(w, h);
    println((int)commands.size());
    for (const string& command : commands) {
        println(command);
    }

    return 0;
}

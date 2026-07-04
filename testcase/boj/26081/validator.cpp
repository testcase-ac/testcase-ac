#include "testlib.h"

#include <map>
#include <set>
#include <string>
#include <vector>
using namespace std;

struct ActorState {
    string parent;
    vector<string> children;
};

static bool isDescendant(const map<string, ActorState>& actors, const string& ancestor, const string& node) {
    const auto& children = actors.at(ancestor).children;
    for (const string& child : children) {
        if (child == node || isDescendant(actors, child, node)) {
            return true;
        }
    }
    return false;
}

static void removeChild(vector<string>& children, const string& child) {
    for (auto it = children.begin(); it != children.end(); ++it) {
        if (*it == child) {
            children.erase(it);
            return;
        }
    }
}

int main(int argc, char* argv[]) {
    registerValidation(argc, argv);

    int w = inf.readInt(3, 50, "W");
    inf.readSpace();
    int h = inf.readInt(3, 50, "H");
    inf.readEoln();

    int q = inf.readInt(3, 5000, "Q");
    inf.readEoln();

    map<string, ActorState> actors;
    actors["Window"] = ActorState{};

    const set<string> vectorProperties = {
        "POSITION", "SIZE", "PARENT_ORIGIN", "ANCHOR_POINT", "SCREEN_POSITION",
    };
    const set<string> settableVectorProperties = {
        "POSITION", "SIZE", "PARENT_ORIGIN", "ANCHOR_POINT",
    };
    const set<string> intProperties = {"COLOR"};

    for (int i = 1; i <= q; ++i) {
        setTestCase(i);

        string command = inf.readToken("New|Add|Remove|Unparent|SetProperty|GetProperty", "command");
        inf.readSpace();
        string actor = inf.readToken("[A-Za-z0-9_]{1,20}", "actor");

        if (command == "New") {
            ensuref(actor != "Window", "command %d: Window cannot be created with New", i);
            ensuref(!actors.count(actor), "command %d: duplicate actor name %s", i, actor.c_str());
            actors[actor] = ActorState{};
            inf.readEoln();
            continue;
        }

        ensuref(actors.count(actor), "command %d: actor %s is not defined", i, actor.c_str());
        ensuref(actor != "Window" || command == "Add" || command == "Remove",
                "command %d: Window is only allowed as the target of Add or Remove", i);

        if (command == "Add" || command == "Remove") {
            inf.readSpace();
            string child = inf.readToken("[A-Za-z0-9_]{1,20}", "child");
            ensuref(child != "Window", "command %d: Window cannot be used as a child actor", i);
            ensuref(actors.count(child), "command %d: child actor %s is not defined", i, child.c_str());

            if (command == "Add") {
                ensuref(!isDescendant(actors, child, actor),
                        "command %d: adding %s under descendant %s would create a cycle",
                        i, child.c_str(), actor.c_str());
                string oldParent = actors[child].parent;
                if (!oldParent.empty()) {
                    removeChild(actors[oldParent].children, child);
                }
                actors[child].parent = actor;
                actors[actor].children.push_back(child);
            } else if (actors[child].parent == actor) {
                removeChild(actors[actor].children, child);
                actors[child].parent.clear();
            }

            inf.readEoln();
            continue;
        }

        if (command == "Unparent") {
            string parent = actors[actor].parent;
            if (!parent.empty()) {
                removeChild(actors[parent].children, actor);
                actors[actor].parent.clear();
            }
            inf.readEoln();
            continue;
        }

        inf.readSpace();
        string property = inf.readToken("POSITION|SIZE|COLOR|PARENT_ORIGIN|ANCHOR_POINT|SCREEN_POSITION", "property");

        if (command == "GetProperty") {
            ensuref(vectorProperties.count(property) || intProperties.count(property),
                    "command %d: invalid property %s", i, property.c_str());
            inf.readEoln();
            continue;
        }

        ensuref(command == "SetProperty", "command %d: unexpected command %s", i, command.c_str());
        ensuref(property != "SCREEN_POSITION", "command %d: SCREEN_POSITION is read-only", i);
        ensuref(settableVectorProperties.count(property) || intProperties.count(property),
                "command %d: invalid settable property %s", i, property.c_str());
        inf.readSpace();

        if (property == "COLOR") {
            inf.readInt(1, 9, "V");
        } else {
            int minValue = 0;
            int maxValue = 1;
            if (property == "POSITION") {
                minValue = -100000;
                maxValue = 100000;
            } else if (property == "SIZE") {
                minValue = 0;
                maxValue = 100000;
            }

            inf.readInt(minValue, maxValue, "X");
            inf.readSpace();
            inf.readInt(minValue, maxValue, "Y");
        }
        inf.readEoln();
    }

    inf.readEof();
}

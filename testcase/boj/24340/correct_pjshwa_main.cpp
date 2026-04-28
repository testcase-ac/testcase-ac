#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using pii = pair<int, int>;

void fast_io() {
  cin.tie(0)->sync_with_stdio(0);
}

vector<string> split(const string &str, string delim) {
  vector<string> tokens;

  string::size_type start = 0;
  string::size_type end = 0;

  while ((end = str.find(delim, start)) != string::npos) {
    tokens.push_back(str.substr(start, end - start));
    start = end + delim.size();
  }

  tokens.push_back(str.substr(start));
  return tokens;
}

bool balloon_removed[1'000'001];

class Route {
  vector<pii> trajectory;
  deque<int> current_balloons, current_visible_balloons;

public:
  Route() {}

  Route(string trajectory_string) {
    vector<string> position_strings = split(trajectory_string, " ");
    for (auto pos_string : position_strings) {
      pos_string = pos_string.substr(1, pos_string.size() - 2);
      vector<string> xy_string = split(pos_string, ",");
      trajectory.push_back({stoi(xy_string[0]), stoi(xy_string[1])});
    }
  }

  void add_balloon(int balloon_id, int balloon_type) {
    current_balloons.push_back(balloon_id);
    if (balloon_type == 1 || balloon_type == 3) current_visible_balloons.push_back(balloon_id);
  }

  int first_balloon_id() {
    while (!current_balloons.empty() && balloon_removed[current_balloons.front()]) {
      current_balloons.pop_front();
    }
    return current_balloons.size() ? current_balloons.front() : -1;
  }

  int first_visible_balloon_id() {
    while (!current_visible_balloons.empty() && balloon_removed[current_visible_balloons.front()]) {
      current_visible_balloons.pop_front();
    }
    return current_visible_balloons.size() ? current_visible_balloons.front() : -1;
  }

  int last_balloon_id() {
    while (!current_balloons.empty() && balloon_removed[current_balloons.back()]) {
      current_balloons.pop_back();
    }
    return current_balloons.size() ? current_balloons.back() : -1;
  }

  int last_visible_balloon_id() {
    while (!current_visible_balloons.empty() && balloon_removed[current_visible_balloons.back()]) {
      current_visible_balloons.pop_back();
    }
    return current_visible_balloons.size() ? current_visible_balloons.back() : -1;
  }

  int size() {
    return trajectory.size();
  }
};

Route routes[11];

class Monkey {
public:
  bool present = false;
  bool skill_L1 = false, skill_R1 = false;
  int target_priority;

  Monkey() {}

  Monkey(string upgrade_status, string target_priority_string) {
    add_skill(upgrade_status);
    change_priority(target_priority_string);
    this->present = true;
  }

  void add_skill(string skill_name) {
    if (skill_name == "L1" || skill_name == "L1R1") skill_L1 = true;
    if (skill_name == "R1" || skill_name == "L1R1") skill_R1 = true;
  }

  void remove() { present = false; }

  void change_priority(string target_priority_string) {
    if (target_priority_string == "FIRST") target_priority = 0;
    if (target_priority_string == "LAST") target_priority = 1;
    if (target_priority_string == "STRONG") target_priority = 2;
  }
};

class Balloon {
public:
  int id, type, route_id, ctime;

  Balloon() {}

  Balloon(int id, int type, int route_id, int ctime) : id(id), type(type), route_id(route_id), ctime(ctime) {}

  int dtime() {
    return ctime + routes[route_id].size() * 100;
  }

  int distance_to_entrance(int t) {
    return (t - ctime) / 100;
  }

  int distance_to_exit(int t) {
    return routes[route_id].size() - (t - ctime) / 100;
  }

  int elapsed_time_on_position(int t) {
    return (t - ctime) % 100;
  }

  bool operator < (const Balloon &b) const {
    return this->type == b.type ? this->id > b.id : this->type < b.type;
  }
};

class Event;

Monkey monkeys[1001];
Balloon balloons[1'000'001];
set<pii> balloons_by_level, visible_balloons_by_level;
priority_queue<Event> events;

int get_strong_balloon_id() {
  return balloons_by_level.size() ? balloons_by_level.begin()->second : -1;
}

int get_strong_visible_balloon_id() {
  return visible_balloons_by_level.size() ? visible_balloons_by_level.begin()->second : -1;
}

class Event {
public:
  int timestamp, monkey_id, balloon_id, route_id, balloon_type;

  // 0: AddMonkeyEvent
  // 1: UpgradeMonkeyEvent
  // 2: RemoveMonkeyEvent
  // 3: ChangePriorityOfMonkeyEvent
  // 4: AddBalloonEvent
  // 5: RemoveBalloonEvent
  int type;
  string skill_name, target_priority_string;

  bool operator < (const Event &e) const {
    return timestamp > e.timestamp;
  }

  Event(int timestamp) : timestamp(timestamp) {}

  void perform() {
    if (type == 0) monkeys[monkey_id] = Monkey("-", "FIRST");
    if (type == 1) monkeys[monkey_id].add_skill(skill_name);
    if (type == 2) monkeys[monkey_id].remove();
    if (type == 3) monkeys[monkey_id].change_priority(target_priority_string);
    if (type == 4) {
      Balloon b = Balloon(balloon_id, balloon_type, route_id, timestamp);
      balloons[balloon_id] = b;
      routes[route_id].add_balloon(b.id, b.type);
      balloons_by_level.insert({-b.type, b.id});
      if (b.type == 1 || b.type == 3) visible_balloons_by_level.insert({-b.type, b.id});

      Event e(b.dtime());
      e.type = 5;
      e.balloon_id = b.id;
      e.route_id = route_id;
      events.push(e);
    }
    if (type == 5) {
      balloon_removed[balloon_id] = true;
      Balloon b = balloons[balloon_id];
      balloons_by_level.erase({-b.type, balloon_id});
      if (b.type == 1 || b.type == 3) visible_balloons_by_level.erase({-b.type, balloon_id});
    }
  }
};

void solve() {
  int R, U, E;
  cin >> R >> U;

  // Discard
  for (int i = 0; i < R; i++) cin >> E;

  cin.ignore();
  for (int i = 1; i <= R; i++) {
    string trajectory_string;
    getline(cin, trajectory_string);
    routes[i] = Route(trajectory_string);
  }
  for (int i = 0; i < U; i++) {
    string monkey_info;
    getline(cin, monkey_info);
    auto args = split(monkey_info, " ");
    monkeys[stoi(args[0])] = Monkey(args[1], args[2]);
  }

  cin >> E;
  cin.ignore();
  for (int i = 1; i <= E; i++) {
    string command;
    getline(cin, command);
    auto args = split(command, " ");

    int timestamp = round(stod(args[0]) * 1000);
    string operation = args[1];

    Event event(timestamp);
    if (operation == "ADD") event.type = 0, event.monkey_id = stoi(args[2]);
    if (operation == "UPGRADE") {
      event.type = 1;
      event.monkey_id = stoi(args[2]);
      event.skill_name = args[3];
    }
    if (operation == "REMOVE") event.type = 2, event.monkey_id = stoi(args[2]);
    if (operation == "CHANGEPRIORITY") {
      event.type = 3;
      event.monkey_id = stoi(args[2]);
      event.target_priority_string = args[3];
    }
    if (operation == "BALLOON") {
      int sz = args.size(), balloon_type = 1;
      if (args[2] == "Camo") {
        if (args[3] == "Lead") balloon_type = 4;
        else balloon_type = 2;
      }
      else if (args[2] == "Lead") balloon_type = 3;

      event.type = 4;
      event.balloon_id = stoi(args[sz - 2]);
      event.balloon_type = balloon_type;
      event.route_id = stoi(args[sz - 1]);
    }
    events.push(event);
  }

  for (int t = 0; t <= 300'000; t++) {
    while (!events.empty() && events.top().timestamp == t) {
      Event e = events.top();
      e.perform();
      events.pop();
    }

    int monkey_id = (t - 1) % 1000 + 1;
    Monkey m = monkeys[monkey_id];
    if (!m.present) continue;

    vector<Balloon> candidate_balloons;
    for (int i = 1; i <= R; i++) {
      int balloon_id;
      if (m.skill_L1) {
        if (m.target_priority == 0) balloon_id = routes[i].first_balloon_id();
        if (m.target_priority == 1) balloon_id = routes[i].last_balloon_id();
        if (m.target_priority == 2) balloon_id = get_strong_balloon_id();
        if (balloon_id != -1) candidate_balloons.push_back(balloons[balloon_id]);
      }
      else {
        if (m.target_priority == 0) balloon_id = routes[i].first_visible_balloon_id();
        if (m.target_priority == 1) balloon_id = routes[i].last_visible_balloon_id();
        if (m.target_priority == 2) balloon_id = get_strong_visible_balloon_id();
        if (balloon_id != -1) candidate_balloons.push_back(balloons[balloon_id]);
      }
    }

    Balloon shot;
    bool found = false;
    if (m.target_priority == 0) {
      sort(candidate_balloons.begin(), candidate_balloons.end(), [&](Balloon& a, Balloon& b) {
        if (a.distance_to_exit(t) != b.distance_to_exit(t)) return a.distance_to_exit(t) < b.distance_to_exit(t);
        if (a.elapsed_time_on_position(t) != b.elapsed_time_on_position(t)) return a.elapsed_time_on_position(t) > b.elapsed_time_on_position(t);
        return a.id < b.id;
      });
      if (candidate_balloons.size()) found = true, shot = candidate_balloons[0];
    }
    if (m.target_priority == 1) {
      sort(candidate_balloons.begin(), candidate_balloons.end(), [&](Balloon& a, Balloon& b) {
        if (a.distance_to_entrance(t) != b.distance_to_entrance(t)) return a.distance_to_entrance(t) < b.distance_to_entrance(t);
        if (a.elapsed_time_on_position(t) != b.elapsed_time_on_position(t)) return a.elapsed_time_on_position(t) < b.elapsed_time_on_position(t);
        return a.id < b.id;
      });
      if (candidate_balloons.size()) found = true, shot = candidate_balloons[0];
    }
    if (m.target_priority == 2) {
      sort(candidate_balloons.begin(), candidate_balloons.end(), [&](Balloon& a, Balloon& b) {
        if (a.type != b.type) return a.type > b.type;
        return a.id < b.id;
      });
      if (candidate_balloons.size()) found = true, shot = candidate_balloons[0];
    }

    if (!found) continue;
    if (!m.skill_R1 && shot.type >= 3) continue;
    cout << shot.id << ' ' << monkey_id << '\n';

    if (shot.type <= 2) {
      balloon_removed[shot.id] = true;
      balloons_by_level.erase({-shot.type, shot.id});
      if (shot.type == 1) visible_balloons_by_level.erase({-shot.type, shot.id});
    }
    else {
      balloons_by_level.erase({-shot.type, shot.id});
      balloons_by_level.insert({-(shot.type - 2), shot.id});
      if (shot.type == 3) {
        visible_balloons_by_level.erase({-shot.type, shot.id});
        visible_balloons_by_level.insert({-(shot.type - 2), shot.id});
      }
      balloons[shot.id].type -= 2;
    }
  }
}

int main() {
  fast_io();

  int t = 1;
  // cin >> t;
  while (t--) solve();
}

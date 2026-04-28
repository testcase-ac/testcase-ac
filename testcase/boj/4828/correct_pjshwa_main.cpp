#include <bits/stdc++.h>
#define fastio ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
using namespace std;
int main() {
	fastio;
	string s;
	while (getline(cin, s)) {
		bool flag = false;
        //<tag>, </tag>
		regex r1(R"(</?[\da-z]+>)");
		stack<string> S;
		for (auto it = sregex_iterator(s.begin(), s.end(), r1); it != sregex_iterator(); it++) {
			if (it->str()[1] == '/') {
				regex r5(R"([<>/])");
				string open = S.top(), close = it->str();
				open = regex_replace(open, r5, "");
				close = regex_replace(close, r5, "");
				if (open != close) {
					cout << "invalid" << '\n';
					flag = true;
					break;
				}
				else {
					S.pop();
				}
			}
			else {
				S.push(it->str());
			}
		}
		if (flag) continue;
		if (!S.empty()) {
			cout << "invalid" << '\n';
			flag = true;
		}
		if (flag) continue;
		s = regex_replace(s, r1, "");
        //<tag/>
		regex r2(R"(<[\da-z]+/>)");
		s = regex_replace(s, r2, "");
        //&lt;, &gt;, &amp;
		regex r3(R"(&(lt|gt|amp);)");
		s = regex_replace(s, r3, "");
        //&xHEX
		regex r4(R"(&x[\dA-F]+)");
		for (auto it = sregex_iterator(s.begin(), s.end(), r4); it != sregex_iterator(); it++) {
			if (it->str().size() % 2 == 1) {
				cout << "invalid" << '\n';
				flag = true;
				break;
			}
		}
		if (flag) continue;
		s = regex_replace(s, r4, "");
        //남은 문자 확인
		for (int i = 0; i < s.size(); i++) {
			if (s[i] == '<' || s[i] == '>' || s[i] == '&' || s[i] < 32 || s[i] > 127) {
				cout << "invalid" << '\n';
				flag = true;
				break;
			}
		}
		if (flag) continue;
		cout << "valid" << '\n';
	}
}

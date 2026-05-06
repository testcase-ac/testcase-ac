#include <bits/stdc++.h>
using namespace std;

static std::mt19937_64 seedRng;

static void initSeed(int argc, char* argv[]) {
    unsigned long long seed = argc > 1
        ? std::strtoull(argv[1], nullptr, 10)
        : static_cast<unsigned long long>(std::chrono::steady_clock::now().time_since_epoch().count());
    seedRng.seed(seed);
    std::srand(static_cast<unsigned>(seed));
}

struct seeded_random_device {
    using result_type = unsigned long long;
    static constexpr result_type min() { return 0; }
    static constexpr result_type max() { return ~0ULL; }
    result_type operator()() { return seedRng(); }
};

#define random_device seeded_random_device

int main(int argc, char* argv[]) {
    initSeed(argc, argv);
	random_device rd;
	mt19937_64 g(rd());
	auto rnd=[&](long long a,long long b){return uniform_int_distribution<long long>(a,b)(rd);};
	int d[11];
	for(int i=0;i<11;i++) d[i]=rnd(1,3);
	for(int i=0;i<11;i++) cout<<d[i]<<(i<10?' ':'\n');
	int total=1;
	for(int i=0;i<11;i++) total*=d[i];
	for(int i=0;i<total;i++) {
		cout<<rnd(1,11111111111LL);
		if(i+1<total) cout<<' ';
	} cout<<'\n';
	int q=rnd(1,100);
	cout<<q<<'\n';
	while(q--) {
		int op=rnd(1,121);
		if(op<67) {
          cout<<op<<' ';
		    for(int i=0;i<11;i++) cout<<rnd(1,d[i])<<' ';
		    for(int i=0;i<11;i++) cout<<rnd(1,d[i])<<(i<10?' ':'\n');
		} else {
            cout<<op<<' ';
		    cout<<'\n';
		    if(op==67)swap(d[0],d[1]);else if(op==68)swap(d[0],d[2]);else if(op==69)swap(d[0],d[3]);else if(op==70)swap(d[0],d[4]);else if(op==71)swap(d[0],d[5]);else if(op==72)swap(d[0],d[6]);else if(op==73)swap(d[0],d[7]);else if(op==74)swap(d[0],d[8]);else if(op==75)swap(d[0],d[9]);else if(op==76)swap(d[0],d[10]);else if(op==77)swap(d[1],d[2]);else if(op==78)swap(d[1],d[3]);else if(op==79)swap(d[1],d[4]);else if(op==80)swap(d[1],d[5]);else if(op==81)swap(d[1],d[6]);else if(op==82)swap(d[1],d[7]);else if(op==83)swap(d[1],d[8]);else if(op==84)swap(d[1],d[9]);else if(op==85)swap(d[1],d[10]);else if(op==86)swap(d[2],d[3]);else if(op==87)swap(d[2],d[4]);else if(op==88)swap(d[2],d[5]);else if(op==89)swap(d[2],d[6]);else if(op==90)swap(d[2],d[7]);else if(op==91)swap(d[2],d[8]);else if(op==92)swap(d[2],d[9]);else if(op==93)swap(d[2],d[10]);else if(op==94)swap(d[3],d[4]);else if(op==95)swap(d[3],d[5]);else if(op==96)swap(d[3],d[6]);else if(op==97)swap(d[3],d[7]);else if(op==98)swap(d[3],d[8]);else if(op==99)swap(d[3],d[9]);else if(op==100)swap(d[3],d[10]);else if(op==101)swap(d[4],d[5]);else if(op==102)swap(d[4],d[6]);else if(op==103)swap(d[4],d[7]);else if(op==104)swap(d[4],d[8]);else if(op==105)swap(d[4],d[9]);else if(op==106)swap(d[4],d[10]);else if(op==107)swap(d[5],d[6]);else if(op==108)swap(d[5],d[7]);else if(op==109)swap(d[5],d[8]);else if(op==110)swap(d[5],d[9]);else if(op==111)swap(d[5],d[10]);else if(op==112)swap(d[6],d[7]);else if(op==113)swap(d[6],d[8]);else if(op==114)swap(d[6],d[9]);else if(op==115)swap(d[6],d[10]);else if(op==116)swap(d[7],d[8]);else if(op==117)swap(d[7],d[9]);else if(op==118)swap(d[7],d[10]);else if(op==119)swap(d[8],d[9]);else if(op==120)swap(d[8],d[10]);else swap(d[9],d[10]);
		}
	}
}

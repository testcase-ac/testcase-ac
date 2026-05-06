#include<iostream>
#include<random>
int main(){
	std::random_device rd;
	std::mt19937_64 gen(rd());
	std::uniform_int_distribution<int> distt(1,1000);
	std::uniform_int_distribution<int> distn(1,1000000000);
	int t=distt(gen);
	std::cout<<t;
	for(int i=0;i<t;i++) {
	    int n=distn(gen),m=distn(gen);
	    std::cout<<'\n'<<n<<' '<<m;
	}
}

#include<iostream>
#include<random>
#include<cstdlib>
using namespace std;
int main(int argc, char** argv)
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  random_device rd;
  unsigned seed = argc > 1 ? static_cast<unsigned>(strtoull(argv[1], nullptr, 10)) : rd();
  mt19937 gen(seed);
  uniform_int_distribution<int> disn(1, 10000);
  uniform_int_distribution<int> dis(0, 2000);
  int n=disn(gen);
  cout<<n<<"\n";
  for(int i=0;i<n;i++)
    {
      cout<<dis(gen)-1000<<" ";
    }
}

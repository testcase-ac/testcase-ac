#include<iostream>
#include<random>
using namespace std;
int main()
{
  ios::sync_with_stdio(false);
  cin.tie(NULL);
  cout.tie(NULL);
  random_device rd;
  mt19937 gen(rd());
  uniform_int_distribution<int> disn(1, 10000);
  uniform_int_distribution<int> dis(0, 2000);
  int n=disn(gen);
  cout<<n<<"\n";
  for(int i=0;i<n;i++)
    {
      cout<<dis(gen)-1000<<" ";
    }
}

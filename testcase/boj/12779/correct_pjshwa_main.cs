using System;

namespace b_12779 {
  class Program {

    static long gcd(long a, long b){
      if (a < b){
        long temp = a;
        a = b;
        b = temp;
      }
      while(a % b != 0){
        long temp = a % b;
        a = b;
        b = temp;
      }
      return b;
    }

    static void Main(string[] args){
      long[] input = Array.ConvertAll(Console.ReadLine().Split(), s => long.Parse(s));
      long a = input[0], b = input[1];
      long ans = (long)(Math.Truncate(Math.Sqrt(b)) - Math.Truncate(Math.Sqrt(a)));
      if (ans == 0) Console.WriteLine(0);
      else{
        long w = b - a;
        long g = gcd(ans, w);
        Console.WriteLine("{0}/{1}", ans / g, w / g);
      }
    }
  }
}

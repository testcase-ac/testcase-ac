using System;
using System.Linq;
using System.Collections.Generic;

namespace b_05425 {
  class Program {

    List<int> Getks(long number, out int digits){
      var answer = new List<int>();
      digits = 0;
      while(number != 0){
        answer.Add((int)(number % 10));
        number /= 10;
        digits++;
      }
      answer.Reverse();
      return answer;
    } // returns digits of number in list

    long SumUpTo10nk(int n, int k){
      return (PowerOf10(n) * (long)(k * (9*n + k - 1))) / 2;
    } // returns digit sum from 0 to 10^n * k exclusive

    long PowerOf10(int power){
      long answer = 1;
      while(power != 0){
        power--;
        answer *= 10;
      }
      return answer;
    } // returns power of 10

    long calculate(long a, long b){
      long sum = 0, sum_b = 0, sum_front = 0;
      int digits;

      var first = Getks(a, out digits);
      for(int i = 0; i < digits; i++){
        sum += SumUpTo10nk(digits - 1 - i, first[i]);
        sum += (sum_front * PowerOf10(digits - 1 - i) * (long)first[i]);
        sum_front += first[i];
      }

      sum_front = 0;

      var second = Getks(1+b, out digits);
      for(int i = 0; i < digits; i++){
        sum_b += SumUpTo10nk(digits - 1 - i, second[i]);
        sum_b += (sum_front * PowerOf10(digits - 1 - i) * (long)second[i]);
        sum_front += second[i];
      }

      return sum_b - sum;
    }

    public void Run(){
      int t = int.Parse(Console.ReadLine());
      foreach(var i in Enumerable.Range(1,t)) {
        long[] arg = Array.ConvertAll(Console.ReadLine().Split(), s => long.Parse(s));
        
        Console.WriteLine(calculate(arg[0], arg[1]));
      }

    }

    static void Main(string[] args){
      (new Program()).Run();
    }
  }
}

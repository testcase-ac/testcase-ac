//Rextester.Program.Main is the entry point for your code. Don't change it.
//Compiler version 4.0.30319.17929 for Microsoft (R) .NET Framework 4.5

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text.RegularExpressions;

namespace Rextester
{
    public class Program
    {
        public static void Main(string[] args){
		int n = int.Parse(Console.ReadLine());
		int player = 0;
		int player_max = 0;
		int player_max_value = 0;
		for(int id = 0; id < n; id++){
			player++;
			int[] cards = Array.ConvertAll(Console.ReadLine().Split(), s => int.Parse(s));
			int ind_max = 0;
			for(int i = 0; i < 3; i++){
				for(int j = i+1; j < 4; j++){
					for(int k = j+1; k < 5; k++){
						int ind = (cards[i] + cards[j] + cards[k]) % 10;
						if(ind > ind_max) ind_max = ind;
					}
				}
			}
			if(ind_max >= player_max_value){
				player_max_value = ind_max;
				player_max = player;
			}
		}
		Console.WriteLine(player_max);
	}
    }
}
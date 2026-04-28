using System;
using System.Collections.Generic;

namespace b_01026 {
	class Program {

		static void Main(string[] args){
			int n = int.Parse(Console.ReadLine());

			var A_list = new List<int>(Array.ConvertAll(Console.ReadLine().Split(), s => int.Parse(s)));
			var B_list = new List<int>(Array.ConvertAll(Console.ReadLine().Split(), s => int.Parse(s)));

			int sum = 0;

			A_list.Sort((a,b) => a.CompareTo(b));
			B_list.Sort((a,b) => -1 * a.CompareTo(b));

			for(int i = 0; i < n; i++){
				sum += (A_list[i] * B_list[i]);
			}
			Console.WriteLine(sum);
			}
		
	}
}
using System;
using System.Linq;

class P {
	static void Main(){
		int[] max_array = new int[9];
		int[] max_index = new int[9];
		for(int i = 0; i < 9; i++){
			var ary = Console.ReadLine().Split().Select(int.Parse).ToArray();
			max_array[i] = ary.Max();
			max_index[i] = Array.IndexOf(ary, max_array[i]);
		}
		int total_max = max_array.Max();
		int total_index = Array.IndexOf(max_array, total_max);
		Console.WriteLine("{0}\n{1} {2}", total_max, total_index+1, max_index[total_index]+1);
	}
}
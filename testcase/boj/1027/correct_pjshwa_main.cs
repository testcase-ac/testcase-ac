using System;

namespace b_01027 {
	class Program {

		static void Main(string[] args){
			int n = int.Parse(Console.ReadLine());
			long[] buildings = Array.ConvertAll(Console.ReadLine().Split(), s => long.Parse(s));
			int see = 0, see_max = 0;

			for(int i = 0; i < n; i++){
				long height = buildings[i];
				for(int j = i + 1; j < n; j++){
					long target_height = buildings[j];
					bool j_seen = true;
					for(int k = i + 1; k < j; k++){
						if(buildings[k] * (j - i) >= height * (j - i) + (target_height - height) * (k - i)){
							j_seen = false;
							break;
						}
					}
					if (j_seen) see++;
				}
				for(int j = 0; j < i; j++){
					long target_height = buildings[j];
					bool j_seen = true;
					for(int k = j + 1; k < i; k++){
						if(buildings[k] * (i - j) >= height * (i - j) + (target_height - height) * (i - k)){
							j_seen = false;
							break;
						}
					}
					if (j_seen) see++;
				}
				if (see > see_max) see_max = see;
				//Console.WriteLine(see);
				see = 0;
			}

			
			Console.WriteLine(see_max);

		}

	}
}

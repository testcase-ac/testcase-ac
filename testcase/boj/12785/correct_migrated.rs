use std::io::*;

const MOD: usize = 1000007;

fn main() {
    let mut input = String::new();
    stdin().read_to_string(&mut input).unwrap();
    let [w, h, x, y] = input.split_whitespace().flat_map(str::parse).collect::<Vec<usize>>().try_into().unwrap();

    let mut map = vec![vec![1; h]; w];
    for i in 1..w {
        for j in 1..h {
            map[i][j] = (map[i - 1][j] + map[i][j - 1]) % MOD;
        }
    }

    print!("{}", (map[x - 1][y - 1] * map[w - x][h - y]) % MOD);
}

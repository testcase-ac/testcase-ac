use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_whitespace().flat_map(str::parse);
    let n = it.next().unwrap();

    let mut map: Vec<Vec<usize>> = (0..n).map(|_| it.by_ref().take(n).collect()).collect();

    print!("{}ossible", if bt(&mut map, n) { "P" } else { "Imp" });
}

macro_rules! enc { ($x: expr, $dx: expr) => { ($x as isize + $dx) as usize } }

fn bt(map: &mut Vec<Vec<usize>>, n: usize) -> bool {
    let mut cnt = 0;
    for i in 0..n {
        for j in 0..n {
            if map[i][j] != 2 { continue; }
            cnt += 1;
            for (di, dj) in [ (-1, 0), (-1, -1), (0, -1), (1, -1), (1, 0), (1, 1), (0, 1), (-1, 1)] {
                let (ai, aj, bi, bj) = (enc!(i, di), enc!(j, dj), enc!(i, di * 2), enc!(j, dj * 2));
                if bi < n && bj < n && map[ai][aj] == 2 && map[bi][bj] == 0 {
                    map[i][j] = 0;
                    map[ai][aj] = 0;
                    map[bi][bj] = 2;
                    if bt(map, n) { return true; }
                    map[i][j] = 2;
                    map[ai][aj] = 2;
                    map[bi][bj] = 0;
                }
            }
        }
    }
    cnt == 1
}

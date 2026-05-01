use std::io::*;

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_ascii_whitespace();

    let [r, c] = std::array::from_fn(|_| it.next().unwrap().parse().unwrap());
    let mut map: Vec<Vec<_>> = it.by_ref().take(r).map(|s| s.chars().collect()).collect();

    for (flag, h) in it.skip(1).enumerate().map(|(i, s)| (i % 2 == 0, r - s.parse::<usize>().unwrap())) {
        let mut hit = usize::MAX;

        macro_rules! shoot {
            ($it:expr) => {
                for k in $it {
                    if map[h][k] == 'x' {
                        map[h][k] = '.';
                        hit = k;
                        break;
                    }
                }
            };
        }

        if flag { shoot!(0..c); } else { shoot!((0..c).rev()); }
        if hit == usize::MAX { continue; }

        let mut visited = vec![vec![false; c]; r];
        let mut clusters_to_fall: Vec<Vec<_>> = vec![];

        macro_rules! for_vaild_dir {
            ($i:expr, $j:expr, |$ni:ident, $nj:ident| $body:block) => {
                for ($ni, $nj) in [($i + 1, $j), ($i.wrapping_sub(1), $j), ($i, $j + 1), ($i, $j.wrapping_sub(1))] {
                    if $ni < r && $nj < c && map[$ni][$nj] == 'x' && !visited[$ni][$nj] { $body }
                }
            };
        }

        for_vaild_dir!(h, hit, |i, j| {
            visited[i][j] = true;
            let mut q = vec![(i, j)];
            let mut cluster = vec![(i, j)];
            let mut floated = i < r - 1;

            while let Some((i, j)) = q.pop() {
                for_vaild_dir!(i, j, |ni, nj| {
                    visited[ni][nj] = true;
                    floated &= ni < r - 1;
                    q.push((ni, nj));
                    cluster.push((ni, nj));
                });
            }

            if floated { clusters_to_fall.push(cluster); }
        });

        for cluster in &clusters_to_fall {
            for &(i, j) in cluster { map[i][j] = '.'; }
        }

        let drops: Vec<_> = clusters_to_fall.iter().map(|cluster| {
            let mut floor = vec![None::<usize>; c];
            for &(i, j) in cluster {
                floor[j] = floor[j].max(Some(i));
            }
            floor.iter().enumerate()
                .filter_map(|(j, i)|
                    i.map(|i| (i + 1..r).find(|&k| map[k][j] == 'x').unwrap_or(r) - i - 1)
                )
                .min().unwrap()
        }).collect();

        for (cluster, drop) in clusters_to_fall.into_iter().zip(drops) {
            for (i, j) in cluster { map[i + drop][j] = 'x'; }
        }
    }

    print!("{}", map.iter().map(|s| s.iter().collect::<String>() + "\n").collect::<String>());
}

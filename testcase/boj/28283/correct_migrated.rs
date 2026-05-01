use std::{io::*, collections::VecDeque};

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_whitespace().flat_map(str::parse);
    let mut next = || it.next().unwrap();

    let [n, m, x, y] = [next(), next(), next(), next()];
    let a: Vec<_> = (0..n).map(|_| next()).collect();

    let mut graph = vec![vec![]; n];

    for _ in 0..m {
        let [u, v] = [next() - 1, next() - 1];
        graph[u].push(v);
        graph[v].push(u);
    }

    let mut q: VecDeque<_> = (0..y).map(|_| next() - 1).collect();

    let mut cnt = vec![usize::MAX; n];

    for &i in &q {
        cnt[i] = 0;
    }
    
    while let Some(u) = q.pop_front() {
        for &v in &graph[u] {
            if cnt[v] > cnt[u] + 1 {
                cnt[v] = cnt[u] + 1;
                q.push_back(v);
            }
        }
    }

    for i in 0..n {
        if cnt[i] == usize::MAX && a[i] > 0 {
            print!("-1");
            return;
        }
        cnt[i] *= a[i];
    }

    cnt.sort();

    print!("{}", &cnt[n - x..].into_iter().sum::<usize>());
}

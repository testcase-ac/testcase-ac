use std::{cmp::Reverse, collections::BinaryHeap, io::*};

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_whitespace().flat_map(str::parse);
    let mut next = || it.next().unwrap();
    
    let [n, m] = [(); 2].map(|_| next());
    let mut map: Vec<_> = (0..n).map(|_| if next() == 0 { usize::MAX } else { 0 }).collect();
    (map[0], map[n - 1]) = (0, usize::MAX);

    let mut graph = vec![vec![]; n];
    for _ in 0..m {
        let [u, v, t] = [(); 3].map(|_| next());
        graph[u].push((v, t));
        graph[v].push((u, t));
    }

    let mut pq = BinaryHeap::from([Reverse((0, 0))]);
    
    while let Some(Reverse((t, i))) = pq.pop() {
        if map[i] < t { continue; }
        for &(j, c) in &graph[i] {
            if map[j] > t + c {
                map[j] = t + c;
                pq.push(Reverse((map[j], j)));
            }
        }
    }

    if map[n - 1] == usize::MAX { print!("-1") }
    else { print!("{}", map[n - 1]) }
}

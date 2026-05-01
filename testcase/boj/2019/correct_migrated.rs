use std::{collections::*, io::*};

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_ascii_whitespace().flat_map(str::parse::<u16>);
    let mut n = || it.next().unwrap();

    let mut graph = HashMap::new();

    for _ in 0..n() {
        let [u, v] = [(n(), n()), (n(), n())];
        graph.entry(u).or_insert(vec![]).push(v);
        graph.entry(v).or_insert(vec![]).push(u);
    }

    let mut cnt = 0;
    let mut visited = HashSet::new();

    for (&xy, linked) in &graph {
        if !(visited.insert(xy) && linked.len() == 2) { continue; }

        let mut component = vec![];
        let mut q = VecDeque::new();
        
        q.push_back(xy);
        visited.insert(xy);

        while let Some(curr) = q.pop_front() {
            component.push(curr);
            for &next in graph.get(&curr).unwrap() {
                if visited.insert(next) { q.push_back(next); }
            }
        }

        if component.len() > 2 && component.iter().filter_map(|v| graph.get(v)).all(|v| v.len() == 2) { cnt += 1; }
    }

    print!("{cnt}");
}

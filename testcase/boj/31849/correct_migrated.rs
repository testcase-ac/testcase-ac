use std::{collections::*, io::*};

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut it = input.split_whitespace().flat_map(str::parse);
    let mut x = || it.next().unwrap();

    let [n, m, r, c] = [x(), x(), x(), x()];

    let rooms: HashMap<_, _> = (0..r).map(|_| ((x() - 1, x() - 1), x())).collect();

    let mut min = usize::MAX;

    let mut q: VecDeque<_> = (0..c).map(|_| (x() - 1, x() - 1, 0)).collect();
    let mut visited = vec![vec![false; m]; n];
    for &(x, y, _) in &q { visited[x][y] = true; }

    while let Some((x, y, d)) = q.pop_front() {
        if let Some(p) = rooms.get(&(x, y)) {
            min = min.min(d * p);
        }

        for (dx, dy) in [(1, 0), (0, 1), (-1, 0), (0, -1)] {
            let (nx, ny) = ((x as isize + dx) as usize, (y as isize + dy) as usize);
            if nx < n && ny < m && !visited[nx][ny] {
                visited[nx][ny] = true;
                q.push_back((nx, ny, d + 1));
            }
        }
    }

    print!("{min}");
}

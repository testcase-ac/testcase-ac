use io::Write;
use std::{io, str};

pub struct UnsafeScanner<R> {
  reader: R,
  buf_str: Vec<u8>,
  buf_iter: str::SplitAsciiWhitespace<'static>,
}

impl<R: io::BufRead> UnsafeScanner<R> {
  pub fn new(reader: R) -> Self {
    Self {
      reader,
      buf_str: vec![],
      buf_iter: "".split_ascii_whitespace(),
    }
  }
  
  pub fn token<T: str::FromStr>(&mut self) -> T {
    loop {
      if let Some(token) = self.buf_iter.next() {
        return token.parse().ok().expect("Failed parse");
      }
      self.buf_str.clear();
      self.reader
          .read_until(b'\n', &mut self.buf_str)
          .expect("Failed read");
      self.buf_iter = unsafe {
        let slice = str::from_utf8_unchecked(&self.buf_str);
        std::mem::transmute(slice.split_ascii_whitespace())
      }
    }
  }
}

fn dfs(
  graph: &Vec<Vec<usize>>,
  vis: &mut Vec<bool>,
  v: usize,
) {
  vis[v] = true;
  for &u in &graph[v] {
    if !vis[u] { dfs(graph, vis, u); }
  }
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let mut a = (0..n).map(|_| scan.token::<usize>()).collect::<Vec<_>>();
  a.sort();

  let mut graph = vec![Vec::new(); n];
  let mut indegree = vec![0; n];
  let mut vis = vec![false; n];

  for i in 0..n {
    if i == 0 { graph[i].push(i + 1); indegree[i + 1] += 1; }
    else if i == n - 1 { graph[i].push(i - 1); indegree[i - 1] += 1; }
    else {
      if a[i] - a[i - 1] <= a[i + 1] - a[i] {
        graph[i].push(i - 1); indegree[i - 1] += 1;
      }
      else {
        graph[i].push(i + 1); indegree[i + 1] += 1;
      }
    }
  }

  let mut ans = 0;
  for i in 0..n {
    if indegree[i] == 0 {
      dfs(&graph, &mut vis, i);
      ans += 1;
    }
  }
  for i in 0..n {
    if !vis[i] {
      dfs(&graph, &mut vis, i);
      ans += 1;
    }
  }

  writeln!(out, "{}", ans).ok();
}

fn main() {
  let (stdin, stdout) = (io::stdin(), io::stdout());
  let mut scan = UnsafeScanner::new(stdin.lock());
  let mut out = io::BufWriter::new(stdout.lock());

  let t = 1;
  // let t = scan.token::<usize>();
  for _ in 0..t {
    solve(&mut scan, &mut out);
  }
}

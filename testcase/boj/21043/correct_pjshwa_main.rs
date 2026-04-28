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
) -> usize {
  vis[v] = true;
  let mut ret = graph[v].len() & 1;

  for &u in &graph[v] {
    if !vis[u] { ret += dfs(graph, vis, u); }
  }
  ret
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let mut graph = vec![Vec::new(); 50_001];
  let mut vis = vec![false; 50_001];

  for _ in 0..n {
    let (u, v) = (scan.token::<usize>(), scan.token::<usize>());
    graph[u].push(v);
    graph[v].push(u);
  }

  let mut ans = 0;
  for i in 1..=50_000 {
    if !vis[i] && !graph[i].is_empty() {
      let cur = dfs(&graph, &mut vis, i);
      ans += 1.max(cur / 2);
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

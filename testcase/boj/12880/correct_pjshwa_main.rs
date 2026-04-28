use io::Write;
use std::{io, str, collections::VecDeque};

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

struct SCC {
  n: usize,
  scc_cnt: usize,
  dfs_cnt: usize,
  scc: Vec<usize>,
  dfs_order: Vec<usize>,
  stack: VecDeque<usize>,
}

impl SCC {
  fn new(n: usize) -> Self {
    SCC {
      n,
      scc_cnt: 0,
      dfs_cnt: 0,
      scc: vec![0; n + 1],
      dfs_order: vec![0; n + 1],
      stack: VecDeque::new(),
    }
  }

  fn dfs(&mut self, cur: usize, adj: &Vec<Vec<usize>>) -> usize {
    self.dfs_order[cur] = self.dfs_cnt;
    self.dfs_cnt += 1;
    self.stack.push_back(cur);

    let mut ret = self.dfs_order[cur];
    for &nxt in &adj[cur] {
      if self.dfs_order[nxt] == 0 { ret = ret.min(self.dfs(nxt, adj)); }
      else if self.scc[nxt] == 0 { ret = ret.min(self.dfs_order[nxt]); }
    }

    if ret == self.dfs_order[cur] {
      self.scc_cnt += 1;
      loop {
        if let Some(t) = self.stack.pop_back() {
          self.scc[t] = self.scc_cnt;
          if t == cur { break; }
        }
      }
    }
    ret
  }

  fn perform(&mut self, adj: &Vec<Vec<usize>>) {
    for i in 1..=self.n {
      if self.dfs_order[i] == 0 { self.dfs(i, adj); }
    }
  }
}

fn check(mn: usize, mx: usize, a: &Vec<Vec<usize>>) -> bool {
  let n = a.len();
  let mut adj = vec![vec![]; n + 1];

  for i in 0..n {
    for j in 0..n {
      if a[i][j] >= mn && a[i][j] <= mx { adj[i + 1].push(j + 1); }
    }
  }

  let mut scc = SCC::new(n);
  scc.perform(&adj);
  scc.scc_cnt == 1
}

fn solve(scan: &mut UnsafeScanner<io::StdinLock>, out: &mut io::BufWriter<io::StdoutLock>) {
  let n = scan.token::<usize>();
  let a = (0..n).map(|_| (0..n).map(|_| scan.token::<usize>()).collect::<Vec<_>>()).collect::<Vec<_>>();

  let mut values = vec![];
  for i in 0..n {
    for j in 0..n { values.push(a[i][j]); }
  }
  values.sort(); values.dedup();

  let z = values.len();
  let (mut r, mut ans) = (0, usize::MAX);
  for l in 0..z {
    while r < z && !check(values[l], values[r], &a) { r += 1; }
    if r < z { ans = ans.min(values[r] - values[l]); }
  }
  writeln!(out, "{}", ans).unwrap();
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

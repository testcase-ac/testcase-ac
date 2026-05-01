use std::io::*;

#[derive(Clone)]
struct Node {
    children: Vec<(char, usize)>,
    end_cnt: usize
}

impl Node {
    fn new() -> Self {
        Self {
            children: vec![],
            end_cnt: 0
        }
    }
}

struct Trie {
    nodes: Vec<Node>
}

impl Trie {
    fn insert(&mut self, s: &str) -> String {
        let mut cur = 0;
        let mut nickname = String::new();

        for (i, b) in s.chars().enumerate() {
            if let Some(&(_, next)) = self.nodes[cur].children.iter().find(|(c, _)| *c == b) {
                cur = next;
            } else {
                let next = self.nodes.len();
                self.nodes[cur].children.push((b, next));
                self.nodes.push(Node::new());
                cur = next;
                if nickname.is_empty() { nickname = s[..=i].to_string(); }
            }
        }

        let cnt = &mut self.nodes[cur].end_cnt;
        *cnt += 1;
        if *cnt > 1 { format!("{s}{cnt}") } else if nickname.is_empty() { s.to_string() } else { nickname }
    }
}

fn main() {
    let input = read_to_string(stdin()).unwrap();
    let mut out = BufWriter::new(stdout());

    let mut trie = Trie { nodes: vec![Node::new()] };

    for x in input.lines().skip(1) {
        writeln!(out, "{}", trie.insert(x)).ok();
    }
}

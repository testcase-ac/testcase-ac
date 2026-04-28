use std::alloc::System;
use std::io;

#[global_allocator]
static GLOBAL: System = System;

fn main() {
    let mut line = String::new();
    io::stdin().read_line(&mut line).unwrap();
    let price = line.trim().parse::<u32>().unwrap();
    let mut change = 1000 - price;

    let mut n_coins = 0;
    let coins = [500, 100, 50, 10, 5, 1];
    for coin in &coins {
        n_coins += change / coin;
        change %= coin;
    }
    println!("{}", n_coins);
}

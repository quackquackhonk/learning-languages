use std::env;

fn main() {
    let args: Vec<String> = env::args().collect();
    let top = args.get(1).expect("Usage ./fizzbuzz <num>");
    let top: u32 = top.parse().expect("Not a number!");

    for ii in 1..top {
        let mut acc : String = "".to_string();
        if ii % 3 == 0 {
            acc.push_str("fizz");
        }

        if ii % 5 == 0 {
            acc.push_str("buzz");
        }

        if acc == "" {
            println!("{}", ii);
        }
        else {
            println!("{}", acc);
        }
    }
    println!("{}", top);
}

extern crate gcc;

use std::env;

fn main() {
    let mut cc = gcc::Config::new();

    if env::var("PROFILE").map(|p|p != "debug").unwrap_or(true) {
        cc.define("NDEBUG", Some("1"));
    }

    if cfg!(target_arch="x86_64") || cfg!(feature = "sse") {
        cc.define("USE_SSE", Some("1"));
    }

    cc.file("libimagequant.c")
        .file("nearest.c")
        .file("kmeans.c")
        .file("mediancut.c")
        .file("mempool.c")
        .file("pam.c")
        .file("blur.c")
        .compile("libimagequant.a");
}

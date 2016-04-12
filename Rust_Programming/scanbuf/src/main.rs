extern crate scanbuf;

use scanbuf::task;
use scanbuf::task::Handler;
struct Tv;

impl Handler for Tv {
	fn call(&self){
		println!("hello,tv....")
	}
}

fn main() {
	// test task data structs.
	let tv = Tv;
	let t = task::Task::new("test",tv,"dex");
	t.method.call();
	println!("==={}",t.name.as_str());	
	
	//test trait handler call.
	let tv1 = Tv;
	tv1.call();
}

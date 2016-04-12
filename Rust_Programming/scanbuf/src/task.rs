
pub struct Task<H> {
	pub name: String,
	pub method: H,
	pub description: String
}

pub trait Handler{
	fn call(&self);		
}

impl<H: Handler> Task<H> {
	pub fn new(n:&str,handler: H, des: &str) -> Task<H>{
		Task{name:n.to_string(),method:handler,description: des.to_string()}
	}
	pub fn get_name(self) -> String{
		self.name
	}

	pub fn get_description(self) -> String {
		self.description
	}
}

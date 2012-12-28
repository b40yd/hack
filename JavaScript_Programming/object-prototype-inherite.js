console.log(Object);
// if not Object,define Object.create 
if(typeof Object.create != "function")
  Object.create = function(o){
		function F(){};
		F.prototype = o;
		return new F();
	};
var Model = {
	inherited:function(){},
	created:function(){},
	prototype:{
		init:function(){}
	},
	create:function(){
		var object = Object.create(this);
		object.parent = this;
		object.prototype = object.fn = Object.create(this.prototype);
		object.created();
		this.inherited(object);
		return object;
	},
	init:function(){
		var instance = Object.create(this.prototype);
		instance.parent = this;
		instance.init.apply(instance,arguments);
		return instance;
	}
};

var User = Model.create();
console.log(User);
var Asset = Model.create();
console.log(Asset.create());
var user = User.init();
console.log(user);

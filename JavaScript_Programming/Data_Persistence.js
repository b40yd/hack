//console.log(Object);
if(typeof Object.create != "function")
	Object.create = function(o){
		function F(){};
		F.prototype = o;
		return new F();
	};
var Model = {
	inherited:function(){},
	created:function(){
		this.records = {};
	},
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
	},
	
	extend:function(o){
		var extended = o.extended;
		jQuery.extend(this,o);
		if(extended) extended(this);
	},
	include:function(o){
		var included = o.included;
		jQuery.extend(this.prototype,o);
		if(included)included(this);
	}
	
};
Model.include({
	newRecord:true,
	create:function(){
		if(!this.id) this.id = Math.guid();
		this.newRecord = false;
		this.parent.records[this.id] = this;
	},
	destroy:function(){
		delete this.parent.records[this.id];
	},
	update:function(){
		this.parent.records[this.id] = this;
	},
	save:function(){
		this.newRecord?this.create():this.update();
	}
});

Model.extend({
	find: function(id){
		return this.records[id] || console.log("Unknown record");
	}
});

Math.guid = function(){
	var d = new Date();
	return 'xxx'.replace(/[x]/g,function(c){
		var r = Math.random()*16|0,v = c == 'x'?r:(r&0x3|0x8);
		return v.toString(16);
	}).toUpperCase()+d.getTime();
};
var User = Model.create();
//console.log(User);
var Asset = Model.create();
//console.log(Asset.create());


var asset = Asset.init();
asset.save();
console.log(asset.id);
Asset.extend({
	find:function(id){
		var record = this.records[id];
		if( !record ) console.log('Unknown record');
		return record.dup();
	}
});
Asset.include({
	create:function(){
		if(!this.id) this.id = Math.guid();
		this.newRecord = false;
		this.parent.records[this.id] = this.dup();
	},
	update:function(){
		this.parernt.records[this.id] = this.dup();
	},
	dup:function(){
		return jQuery.extend(true,{},this);
	}
	
});
var a = Asset.init();
a.save();
console.log(Asset.find(a.id));

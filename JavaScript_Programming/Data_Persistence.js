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
jQuery.extend(Model,{
	find:function(){}
});
jQuery.extend(Model.prototype,{
	init:function(atts){
		if(atts) this.load(atts);
	},
	load:function(attributes){
		this.create();
		for(var name in attributes)
			this[name] = attributes[name];
	}
});

Model.include({
	newRecord:true,
	create:function(){
		if(!this.id) this.id = Math.guid();
		this.newRecord = false;
		this.parent.records[this.id] = this;
		return this;
	},
	destroy:function(){
		delete this.parent.records[this.id];
		return this.parent.records;
	},
	update:function(){
		this.parent.records[this.id] = this;
		return this;
	},
	save:function(){
		this.newRecord?this.create():this.update();
		return this;
	}
});

Model.extend({
	find: function(id){
		return this.records[id] || console.log("Unknown record");
	},
	created:function(){
		this.records = {};
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
		return this.parent;
	},
	update:function(){
		this.parent.records[this.id] = this.dup();
		return this.parent;
	},
	dup:function(){
		return jQuery.extend(true,{},this);
	}
	
});
//var a = Asset({name:"bao"});
//a.save();
var Asset = Model.create();
var a = Asset.init({name:"sss"});
var a1 = Asset.init({name:"s2ss"});
var a2 = Asset.init({name:"ss2s"});

a.name = "hh";
a.save();
a1.save();
a2.save();
a2.ddd='aaaa';
a.destroy()
console.log(Asset);

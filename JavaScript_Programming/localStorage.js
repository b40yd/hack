// to localStorage add data storage
Model.extend({
  created:function(){
		this.records = {};
		this.attributes = [];
	}
});

Model.include({
	attributes:function(){
		var result = {};
		console.log(this.parent.attributes);
		for(var i in this.parent.attributes){
			var attr = this.parent.attributes[i];
			result[attr] = this[attr];	
		}
		result.id = this.id;
		return result;
	},
	toJSON:function(){
		return(this.attributes());
	}
});
var Model.localStorage = {

	saveLocal:function(name){
		var result = [];
		for(var i in this.records){
			result.push(this.records[i]);
		}
		localStorage[name] = JSON.stringify(result);
	},
	loadLocal:function(name){
		var result = JSON.parse(localStorage[name]);
		this.populate(result);
	}
};



var Asset = Model.create();
Asset.attributes = ["name","password","body"];
var a = Asset.init({name:"string",password:"string",body:"text"});
a.save();
Asset.extend(Model.localStorage);
console.log(a.attributes());

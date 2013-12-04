var dateObject = function(){
	var formatDateTime = new Date();
	return this;
};
dateObject.prototype.getToday = function(){
	var formatDateTime = new Date();
	return formatDateTime.getFullYear()+"-"+(Number(formatDateTime.getMonth())+1)+"-"+formatDateTime.getDate();
};

dateObject.prototype.init = function(times){

	if(times == '' || typeof(times) == 'undefined'){
		this.formatDateTime = new Date();
	}else{
		if( typeof(times) == 'object' && (times instanceof Date) ){
			//new Date(times.getMonth()+"/"+times.getMonth()+"/"+times.getFullYear())
			this.formatDateTime = new Date(times.getFullYear(),times.getMonth(),times.getDate());
		}else
			this.formatDateTime = new Date(times);
	}
		
	return new Date(this.formatDateTime-(this.formatDateTime.getDay()-1)*86400000);
};

dateObject.prototype.getPrevWeekFirstDay = function(times){
	var WeekFirstDay = this.init(times);
	return new Date(WeekFirstDay-86400000*7);
};
dateObject.prototype.getNextWeekFirstDay = function(times){
	var WeekFirstDay = this.init(times);
	var WeekLastDay = new Date((WeekFirstDay/1000+6*86400)*1000);
	return new Date((WeekLastDay/1000+86400)*1000);
};
dateObject.prototype.getCurrentWeekFirstDay = function(times){
	return this.init(times);
};


dateObject.prototype.getPrevWeekLastDay = function(times){
	var WeekFirstDay = this.init(times);
	return new Date((WeekFirstDay/1000-86400)*1000);
};

dateObject.prototype.getNextWeekLastDay = function(times){
	var WeekFirstDay = this.init(times);
	var WeekLastDay=new Date((WeekFirstDay/1000+6*86400)*1000);
	return new Date((WeekLastDay/1000+7*86400)*1000);

};
dateObject.prototype.getCurrentWeekLastDay = function(times){
	var WeekFirstDay = this.init(times);
	return new Date((WeekFirstDay/1000+6*86400)*1000);
};
//get current week first and last day.
dateObject.prototype.getCurrentWeek =  function(times){
	return [this.getCurrentWeekFirstDay(times),this.getCurrentWeekLastDay(times)];
};
//get prev week first and last day.
dateObject.prototype.getPrevWeek =  function(times){
	return [this.getPrevWeekFirstDay(times),this.getPrevWeekLastDay(times)];
};
//get next week first and last day.
dateObject.prototype.getNextWeek =  function(times){
	return [this.getNextWeekFirstDay(times),this.getNextWeekLastDay(times)];
};

dateObject.prototype.getPrevMonthFirstDay = function(times){
	this.init(times);
	return new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()-1,1);
};
dateObject.prototype.getNextMonthFirstDay = function(times){
	this.init(times);
	return new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()+1,1);
};
dateObject.prototype.getCurrentMonthFirstDay = function(times){
	this.init(times);
	return new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth(),1);
};

dateObject.prototype.getPrevMonthLastDay = function(times){
	this.init(times);
	var MonthNextFirstDay=new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth(),1);
	return new Date(MonthNextFirstDay-86400000);
};

dateObject.prototype.getNextMonthLastDay = function(times){
	this.init(times);
	var MonthNextFirstDay = new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()+2,1);
	return new Date(MonthNextFirstDay-86400000);
};
dateObject.prototype.getCurrentMonthLastDay = function(times){
	this.init(times);
	var MonthNextFirstDay = new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()+1,1);
	return new Date(MonthNextFirstDay-86400000);
};

//get current month first and last day.
dateObject.prototype.getCurrentMonth = function(times){
	return [this.getCurrentMonthFirstDay(times),this.getCurrentMonthLastDay(times)];
};
//get perv month first and last day.
dateObject.prototype.getPrevMonth = function(times){
	return [this.getPrevMonthFirstDay(times),this.getPrevMonthLastDay(times)];
};
//get Next month first and last day.
dateObject.prototype.getNextMonth = function(times){
	return [this.getNextMonthFirstDay(times),this.getNextMonthLastDay(times)];
};




Date.prototype.toString = function ()
{
	return this.format("yyyy-MM-dd");
};
Date.prototype.toDateTimeString = function(){
	return this.format("yyyy-MM-dd hh:mm:ss");
};
Date.prototype.toTimeString = function(){
	return this.format("hh:mm:ss");;
}; 

//(new Date()).Format("yyyy-MM-dd hh:mm:ss.S") ==> 2006-07-02 08:09:04.423   
//(new Date()).Format("yyyy-M-d h:m:s.S")      ==> 2006-7-2 8:9:4.18   
Date.prototype.format = function(fmt)   
{ 
	//author: meizz   
	var o = {   
			"M+" : this.getMonth()+1,                 //月份   
			"d+" : this.getDate(),                    //日   
			"h+" : this.getHours(),                   //小时   
			"m+" : this.getMinutes(),                 //分   
			"s+" : this.getSeconds(),                 //秒   
			"q+" : Math.floor((this.getMonth()+3)/3), //季度   
			"S"  : this.getMilliseconds()             //毫秒   
	};   
	if(/(y+)/.test(fmt))   
		fmt=fmt.replace(RegExp.$1, (this.getFullYear()+"").substr(4 - RegExp.$1.length));   
	for(var k in o){
		if(new RegExp("("+ k +")").test(fmt)){
			fmt = fmt.replace(RegExp.$1, (RegExp.$1.length==1) ? (o[k]) : (("00"+ o[k]).substr((""+ o[k]).length)));
		}
	}
		
			   
	return fmt;   
} 

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
	if(times == ''){
		return new Date(WeekFirstDay-86400000);
	}
	var WeekLastDay=new Date((WeekFirstDay/1000-7*86400)*1000);
	return new Date((WeekLastDay/1000-86400)*1000);
};

dateObject.prototype.getNextWeekLastDay = function(times){
	var WeekFirstDay = this.init(times);
	var WeekLastDay=new Date((WeekFirstDay/1000+6*86400)*1000);
	if(times == '')
		return new Date((WeekLastDay/1000+7*86400)*1000);
	return new Date((WeekLastDay/1000)*1000);

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
	return this.getFullYear() + "-" + (this.getMonth()+1) + "-" + this.getDate();
};
Date.prototype.toDateTimeString = function(){
	return this.getFullYear() + "-" + (this.getMonth()+1) + "-" + this.getDate()+" "+this.getHours()+":"+this.getMinutes()+":"+this.getSeconds();
};
Date.prototype.toTimeString = function(){
	return this.getHours()+":"+this.getMinutes()+":"+this.getSeconds();
}; 

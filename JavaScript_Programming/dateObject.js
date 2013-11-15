var dateObject = function(){
				var formatDateTime = new Date();
				return this;
		};
		dateObject.prototype.getToday = function(){
			var formatDateTime = new Date();
			return formatDateTime.getFullYear()+"-"+(Number(formatDateTime.getMonth())+1)+"-"+formatDateTime.getDate();
		};

		dateObject.prototype.init = function(times){
			
			if(times == "" || typeof(times) == 'undefined' || typeof(times) == 'object'){
				this.formatDateTime = new Date();
			}else
				this.formatDateTime = new Date(times);
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
		dateObject.prototype.getCurrentWeekFirstDay = function(){
			return this.init();
		};
		
		
		dateObject.prototype.getPrevWeekLastDay = function(times){
			var WeekFirstDay = this.init(times);
			return new Date(WeekFirstDay-86400000);
		};

		dateObject.prototype.getNextWeekLastDay = function(times){
			var WeekFirstDay = this.init(times);
			var WeekLastDay=new Date((WeekFirstDay/1000+6*86400)*1000);
			return new Date((WeekLastDay/1000+7*86400)*1000);
			
		};
		dateObject.prototype.getCurrentWeekLastDay = function(){
			var WeekFirstDay = this.init();
			return new Date((WeekFirstDay/1000+6*86400)*1000);
		};
		//get current week first and last day.
		dateObject.prototype.getCurrentWeek =  function(){
			return [this.getCurrentWeekFirstDay(),this.getCurrentWeekLastDay()];
		};
		//get prev week first and last day.
		dateObject.prototype.getPrevWeek =  function(startTime,endTime){
			return [this.getPrevWeekFirstDay(startTime),this.getPrevWeekLastDay(endTime)];
		};
		//get next week first and last day.
		dateObject.prototype.getNextWeek =  function(startTime,endTime){
			return [this.getNextWeekFirstDay(startTime),this.getNextWeekLastDay(endTime)];
		};
		
		dateObject.prototype.getPrevMonthFirstDay = function(times){
			this.init(times);
			return new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()-1,1);
		};
		dateObject.prototype.getNextMonthFirstDay = function(times){
			this.init(times);
			return new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()+1,1);
		};
		dateObject.prototype.getCurrentMonthFirstDay = function(){
			this.init();
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
		dateObject.prototype.getCurrentMonthLastDay = function(){
			this.init();
			var MonthNextFirstDay = new Date(this.formatDateTime.getFullYear(),this.formatDateTime.getMonth()+1,1);
			return new Date(MonthNextFirstDay-86400000);
		};

		//get current month first and last day.
		dateObject.prototype.getCurrentMonth = function(){
			return [this.getCurrentMonthFirstDay(),this.getCurrentMonthLastDay()];
		};
		//get perv month first and last day.
		dateObject.prototype.getPrevMonth = function(startTime,endTime){
			return [this.getPrevMonthFirstDay(startTime),this.getPrevMonthLastDay(endTime)];
		};
		//get Next month first and last day.
		dateObject.prototype.getNextMonth = function(startTime,endTime){
			return [this.getNextMonthFirstDay(startTime),this.getNextMonthLastDay(endTime)];
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

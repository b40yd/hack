require 'observer'

class Tick
  include Observable
  def tick
    loop do 
      now = Time.now
      changed
      notify_observers(now.hour,now.min,now.sec)
      sleep 1.0 - Time.now.usec / 1000000.0
    end
  end
end

class TextClock
  def update(h,m,s)
    printf "\e[8D%02d:%02d:%02d",h,m,s
    STDOUT.flush
  end
  def modify
    puts 'Hello,Clock!~'
  end
end


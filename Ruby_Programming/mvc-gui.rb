#! /usr/bin/ruby 
require "observer"
require "tk"

# the Model class count clock ticks

class WatchModel
  include Observable
  def initialize
    @running = false
    @time = 0
    @last = 0.0
    Thread.start do
      loop do 
        sleep 0.01
        if @running
          now = Time.now.to_f
          @time += now-@last
          @last = now
          changed
          notify_observers(@time)
        end
      end
    end
  end
  
  def start_stop
    @last = Time.now.to_f
    @running = ! @running
  end

  def time
    @time
  end

end

class WatchWindow
  def initialize
    model = WatchModel.new
    model.add_observer(self)
    @label = TkLabel.new(nil).pack('fill'=>'x')
    self.update(0)
    btn = TkButton.new
    btn.text('start/stop')
    btn.command(proc{model.start_stop})
    btn.pack('fill'=>'x')
    btn = TkButton.new
    btn.text('quit')
    btn.command(proc{exit})
    btn.pack('fill'=>'x')
    Tk.mainloop
  end
  def update(time)
    @label.text format("%02d:%02d",time.to_i,(time-time.to_i)*100)
  end
end

WatchWindow.new


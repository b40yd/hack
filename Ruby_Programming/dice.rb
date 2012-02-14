class Dice
  def initialize(n)
    @n = n
  end
  
  def each
    @n.times{
      yield rand(6)+1
    }
  end
end

dice = Dice.new(10)

dice.each{|x| puts x}

class Dice
  include Enumerable
end

p dice.reject{|x| x<=3}

#
# scope testing
# (::) This scope is Object 
# Make double colon beginning interpreted as self == Object (as ::Engineer == Class Engineer)
#


class Engineer
    def engine
        puts 'this engine'
    end
end

module Web 
    module Engineer
        class Parser < ::Engineer
            puts 'parser'
        end
        
        puts Engineer
        puts ::Engineer
        puts self
    end
end

s = [10,4,12,44,33,2,1,4];


def quickSort(list)
  return [] if list.empty?
  right,left = list[0..-2].partition { |e| e>=list.last }
  quickSort(left)+[list.last]+quickSort(right)
end	

print s.last

print quickSort(s)

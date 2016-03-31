from sys import stdin,stdout,version_info

class ProgressBar(object):
	def __init__(self, total, progressChar=None):
		self.total = total
		self.blockcount = 0
		self.block = '';
		#
		# See if caller passed me a character to use on the
		# progress bar (like "*").  If not use the block
		# character that makes it look like a real progress
		# bar.
		#
		if not progressChar: 
			self.progressChar = chr(178)
		else:                
			self.progressChar = progressChar
		#
		# Get pointer to sys.stdout so I can use the write/flush
		# methods to display the progress bar.
		#
		self.buf = stdout
		#
		# If the final count is zero, don't start the progress gauge
		#
		if not self.total : 
			print("[Total Count] must be greater than zero")
			return
		self.buf.write('\n------------------- % Progress -------------------\n')
		return
 
	def progress(self, count):

		count = min(count, self.total)

		if self.total:
			percent = int(round(100*count/self.total))
			if percent < 1: percent=0
		else:
			percent=100
			
		blockcount = int(percent/2)

		if blockcount > self.blockcount:
			self.block += self.progressChar
		self.buf.write(self.block + str(percent) + "%\r")
		self.buf.flush()
		self.blockcount = blockcount
		return

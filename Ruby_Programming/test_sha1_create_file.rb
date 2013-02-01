require 'digest/sha1'
require 'zlib'
require 'fileutils'
def put_raw_object(content, type)
  size = content.length.to_s
	header = "#{type} #{size}\0" # type(space)size(null byte)
	store = header + content
	sha1 = Digest::SHA1.hexdigest(store)
	path =  './' + sha1[0...2] + '/' + sha1[2..40]
	if !File.exists?(path)
		content = Zlib::Deflate.deflate(store)
		FileUtils.mkdir_p('./'+sha1[0...2])
		File.open(path, 'w') do |f|
			f.write content
		end
	end
	return sha1
end

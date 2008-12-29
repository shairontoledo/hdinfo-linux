require 'rubygems'

spec=Gem::Specification.new do |s|
    s.name = 'hdinfo'
    s.version = '0.3'
    s.platform = Gem::Platform::RUBY
    s.summary = "Gets infomation about your hds SATA, IDE or Mass storage for Linux"
    s.description = s.summary
    s.author = "Shairon Toledo"
    s.email = 'shairon.toledo@gmail.com'
    s.homepage = 'http://github.com/shairontoledo/hdinfo-linux/wikis'
    s.files = ['extconfig.rb','hdinfo.c']
    s.extensions = ["extconfig.rb"]
  end
  
if $0 == __FILE__
      Gem::manage_gems
      Gem::Builder.new(spec).build
end

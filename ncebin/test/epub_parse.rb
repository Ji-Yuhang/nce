#!/usr/bin/env ruby
require 'epub/parser'
require 'awesome_print'
require 'active_record'
require 'sqlite3'
require 'awesome_print'
require 'date'

ActiveRecord::Base.establish_connection :adapter => "sqlite3",
    :database => "nce3.db"

class Articles < ActiveRecord::Base
end

class Sentences < ActiveRecord::Base
end

class Words < ActiveRecord::Base
end


data = {}
i = 1
flag = false
book = EPUB::Parser.parse('/home/jiyuhang/nce3.epub')
ap book.metadata.titles # => Array of EPUB::Publication::Package::Metadata::Title. Main title, subtitle, etc...
ap book.metadata.title # => Title string including all titles
ap book.metadata.creators # => Creators(authors)
book.each_page_on_spine do |page|
  page.media_type # => "application/xhtml+xml"
  page.entry_name # => "OPS/nav.xhtml" entry name in EPUB package(zip archive)
  html = page.read # => raw content document
  doc = Nokogiri.HTML(html)
doc.xpath('//p').each do|link|
#  doc.search('听录音，然后回答以下问题','//p').each do|link|
      con = link.content
      if con.include? '听录音'
        flag = true
        next
      end
      if con.include? '生词和短语'
          i += 1
          flag = false
      end

      if flag
          #ap con
          if data[i].nil?
              data[i] = con
          else
            data[i] += con + "\n"
                    end
      end
      
  end
  #ap doc
  #gets
  page.content_document.nokogiri # => Nokogiri::XML::Document. The same to Nokogiri.XML(page.read)
  # do something more
  #    :
end

File.open("output.txt","w") do |io|
    data.each do |index, content|
        ap "class " + index.to_s
        #ap content
        #gets
        article = Articles.new
        article.title = "nce3/class_"+index.to_s
        article.content = content
        article.author = "Ji-Yuhang"
        time = Time.now
        article.addtime= time.to_i
        article.updatetime= time.to_i
        article.save!

        io.puts "class " + index.to_s
        io.puts content
    end
end


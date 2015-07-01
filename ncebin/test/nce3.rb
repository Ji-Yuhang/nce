#!/usr/bin/env ruby
require 'active_record'
require 'sqlite3'
require 'awesome_print'
require './article'

module Nce3
    ActiveRecord::Base.establish_connection :adapter => "sqlite3",
        :database => "nce3.db"

    class Articles < ActiveRecord::Base
    end

    class Sentences < ActiveRecord::Base
    end

    class Words < ActiveRecord::Base
    end
end

worddata = {}
classword = {}
tempi = 0
wordsentencelist = {}
sqlwords = []
Nce3::Words.all().each do |word|
    sqlwords.push word.word
end
Nce3::Sentences.all().each do |sen|
    words = Article.get_words sen.sentence
    words.each do |word|
        if worddata[word].nil?
            worddata[word] = 1
        else
            worddata[word] += 1
        end
        if wordsentencelist[word].nil?
            wordsentencelist[word] = []
        end
        wordsentencelist[word].push sen.sentence_id
    end
    
end
ap sqlwords.size
worddata.each do |key,value|
    ap key
    ap value
    if sqlwords.include? key
        next
    end
    word = Nce3::Words.new
    word.word = key
    word.frequency = value
    word.sentence_id_list = wordsentencelist[key].join ','
    word.status = 0
    word.save!
end
ap worddata.size
=begin
Nce3::Articles.all().each do |s|
    title = s.title
    ap title
    content = s.content

    sentences = Article.get_sentences content
    sentences.each do |sen|

        sentencedata = Nce3::Sentences.new
        sentencedata.sentence = sen
        sentencedata.article_id = s.article_id
        time = Time.now
        sentencedata.addtime= time.to_i
        sentencedata.updatetime= time.to_i
        words = Article.get_words sen
        sentencedata.word_count = words.size
        sentencedata.status = 0
        #sentencedata.save!

    end
    words = Article.get_words content
    words.each do |word|
        if worddata[word].nil?
            worddata[word] = 0
        else
            worddata[word] += 1
        end

        if classword[word].nil?
            classword[word] = s.title
        end
    end
    
    #s.title = title
    s.sentence_count = sentences.size
    s.status = 0
    #s.save!
end

ap worddata.size
i = 0
temp = {}
classword.each do |key,value|
    if temp[value].nil?
        temp[value] = [key]
    else
        temp[value].push key
    end

end
#ap temp
=end


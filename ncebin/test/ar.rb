#!/usr/bin/env ruby
require 'active_record'
require 'sqlite3'
require 'awesome_print'
#ActiveRecord::Base.establish_connection :adapter => "sqlite3",
    #:database => "nce.db"

ActiveRecord::Base.establish_connection :adapter => "mysql",
    :host => "rds1m2iqskhitpx6nmx7u.mysql.rds.aliyuncs.com",
    :database => "english",
    :username => "jiyuhang",
    :password => "jiyuhang8757871"
class Wordlist < ActiveRecord::Base
end
Wordlist.all().each do |s|
    ap s
end
#s = Wordlist.first
#ap s
=begin
s.id=99991
s.sentence = "Nothing"
s.article="article"
s.addtime=123456778
s.updatetime=123456778
s.status=123456778

s.save!
=end

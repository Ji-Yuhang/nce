#!/usr/bin/env ruby
require './spell'
module Article
    def get_sentences(article)
        sentences = []
        #sentences = article.split(/[\\.!\?]/)
        #remove1 = article.gsub /[\\.!\?]/ do |match|
        #end
        # //TODO: ignore B.C, U.S.A etc.
        index = article.index /[\\.!\?]/
        last_index = 0
        u_s_a_flag = false
        mrs_flag = false
        while !index.nil? && index != 0
            #ap index
            if article[index+1] == '\''
                index += 1
            end
            sen = article[last_index,index + 1 - last_index]
            #ap sen
            sen.chomp!
            originsen = sen
            sen = sen.gsub /\s+$/, ''
            sen = sen.gsub /^\s+/, ''
            sen = sen.gsub /\n/, ''
            last_index = index + 1

            if !sen.include? ' ' and sen[-1] == '.' and sen.size == 2# contact B.C.
                lastsen = sentences.pop
                if lastsen.nil?
                    lastsen = ""
                end
                lastsen += sen
                sentences.push lastsen
                u_s_a_flag = true
            else
                
                tempc = originsen[1]
                lastsen = sentences.pop
                lastword = sen.scan /[A-Z]\w+\./
                mrsarray = ["St.","Mrs.","Mr."]
 
                # different of "B.C. It is ok " and "B.C. until yesterday"
                if u_s_a_flag and originsen[0] == ' ' and !tempc.nil? and tempc.downcase == tempc 
                    # Mrs. A is me
                    if lastsen.nil?
                        lastsen = ""
                    end

                    lastsen += originsen
                    sentences.push lastsen
=begin
                elsif lastword.size > 0 and mrsarray.include? sen and lastsen.nil?

                    if lastsen.nil?
                        lastsen = ""
                    end

                    ap "lastsen:"+lastsen
                    ap "originsen:"+originsen
                    lastsen += originsen
                    sentences.push lastsen
=end
                    

                else
                   haveMrs = false
                    if lastword.size > 0
                        tttt = lastword[0]
                        #ap "lastword[0]:"+tttt
                        if mrsarray.include? tttt
                            haveMrs = true
                            #ap "haveMrs : "+sen
                        end
                    end
                    if sen.size > 2 and haveMrs # when Mrs. A come.
                        mrs_flag = true
                        if lastsen.nil?
                            lastsen = ""
                            #sentences.push lastsen
                        else

                        #ap "lasword:"+lastword[0]
                        #lastsen += sen

                            sentences.push lastsen
                        end
                        sentences.push sen
                    else
                        if mrs_flag
                            if lastsen.nil?
                                lastsen = ""
                            end

                            #ap "lastsen:"+lastsen
                            #ap "originsen:"+originsen
                            lastsen += originsen

                            #ap lastsen
                            sentences.push lastsen

                            mrs_flag = false
                        else
                            u_s_a_flag = false
                            # normal
                            if lastsen.nil?
                                lastsen = ""
                            else
                                sentences.push lastsen
                            end
                            sentences.push sen
                        end
                    end
                end
                
            end

            index = article.index /[\\.!\?]/, last_index


        end
        
        sentences
    end

    def get_words(sentence)
        words = []
        spell = Spell.instance
        content = sentence
        remove1 = content.gsub /\w+\'\w+/ do |match|
            #ap match
            ""
        end
        remove2 = remove1.gsub /\w+\.\w+\.\w+/ do |match|
            #ap match
            ""
        end

        remove3 = remove2.gsub /\w+\.\w+/ do |match|
            #ap match
            ""
        end
        remove4 = remove3.gsub /\w+/ do |match|
            match = match.downcase
            if !match.nil? and spell.check? match
                temp = spell.remove_plural match
                if !words.include? temp
                    words.push temp
                end

            end
            ""
        end
        words
    end

    module_function :get_sentences, :get_words
end

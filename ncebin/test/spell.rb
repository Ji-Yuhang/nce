#!/usr/bin/env ruby
require 'ffi/hunspell'
require 'singleton'
require 'awesome_print'
class Spell
    include Singleton
    def initalize
        init
    end
    def check?(word)
        init
        (@dict_US.check? word or @dict_US.check? word)
    end
    def remove_plural(word)
        init

        stems =  @dict_US.stem word
        if !stems[0].nil? and stems[0] != word
            st = stems[0]
            y = st[-1]
            ky = word[-1]
            f = st[-2]
            if st + "s" == word or st + "es" == word
                return st
            end
            if y == "y" and ky == "s"
                return st
            end
            if st[-2..-1] == "fe" and ky ==  "s"
                return st
            end
            if y == "f" and ky ==  "s"
                return st
            end
        end
        word
    end
    def init
        @dict_US = FFI::Hunspell.dict("en_US") if @dict_US.nil?
        @dict_GB = FFI::Hunspell.dict("en_GB") if @dict_GB.nil?
    end
end

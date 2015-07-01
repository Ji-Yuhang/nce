#!/usr/bin/env ruby
require 'awesome_print'
require 'minitest/autorun'
require './article'

class ArticleTest < MiniTest::Test
    def setup

    end

    def test_empty_array
        assert_equal [],
            Article.get_sentences("")
    end

    def test_point
        assert_equal [],
            Article.get_sentences(".!?")
    end

    def test_BC
        assert_equal ["B.C. until yesterday."],
            Article.get_sentences("B.C. until yesterday.")
    end
    def test_BC_next
        assert_equal ["B.C.","It is over."],
            Article.get_sentences("B.C. It is over.")
    end
    def test_Mrs0
        assert_equal ["Mrs. five."],
            Article.get_sentences("Mrs. five.")
    end
    def test_Mrs
        assert_equal ["Mrs. Five."],
            Article.get_sentences("Mrs. Five.")
    end
    def test_Mrs1
        sens = []
        sen = %{After her husband had gone to work. Mrs. Richards sent her children to school and went upstairs to her bedroom.}
        sens.push %{After her husband had gone to work.}
        sens.push %{Mrs. Richards sent her children to school and went upstairs to her bedroom.}
        assert_equal sens,
            Article.get_sentences(sen)
    end
    def test_Mrs2
        assert_equal ["Mrs. Five is me."],
            Article.get_sentences("Mrs. Five is me.")
    end
    def test_Mrs3
        assert_equal ["I am Mrs. Five."],
            Article.get_sentences("I am Mrs. Five.")
    end
    def test_Mrs4
        assert_equal ["I am Mrs. Five's father."],
            Article.get_sentences("I am Mrs. Five's father.")
    end

    def test_one_sentence
        sens=[]
        sen = "I am Ji-Yuhang."
        sens.push sen
        assert_equal sens,
            Article.get_sentences(sen)
    end

    def test_wenhao_sentence
        sens=[]
        sen = "Was the vicar pleased that the clock was striking? Why?"

        sens.push "Was the vicar pleased that the clock was striking?"

        sens.push "Why?"

        assert_equal sens,
            Article.get_sentences(sen)

    end

    def test_para
        sens=[]
        sen = %{Our vicar is always raising money for one cause or another, but he has never managed to get enough money to have the church clock repaired. The big clock which used to strike the hours day and night was damaged many years ago and has been silent ever since.}
        sens.push "Our vicar is always raising money for one cause or another, but he has never managed to get enough money to have the church clock repaired."
        sens.push "The big clock which used to strike the hours day and night was damaged many years ago and has been silent ever since."
        assert_equal sens,
            Article.get_sentences(sen)
    end

    def test_maohao
        sens = []
        sen = %{One night, however, our vicar work up with a start: the clock was striking the hours! Looking at his watch, he saw that it was one o'clock, but the bell struck thirteen times before it stopped.}
        sens.push "One night, however, our vicar work up with a start: the clock was striking the hours!"
        sens.push "Looking at his watch, he saw that it was one o'clock, but the bell struck thirteen times before it stopped."
        assert_equal sens,
            Article.get_sentences(sen)

    end
    def test_talk_sentence
        sens = []
        sen = %{'Whatever are you doing up here Bill?' asked the vicar in surprise. }
        sens.push %{'Whatever are you doing up here Bill?'}
        sens.push %{asked the vicar in surprise.}
        assert_equal sens,
            Article.get_sentences(sen)

    end
end

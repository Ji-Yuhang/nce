本程序原意是为了分析出新概念4册书中所有的单词数。并分析出单词出现的次数频率。分析出每个单词的例句。

后来呢，加了一个阅读的功能。从网上下载一本txt文档。导入textEdit。在断句之后显示。并能双击选中单词。自动弹出释义。释义调用扇贝的api。

我的目的呢。是读书。能够分析出一篇英文文章中哪些单词我认识，哪些单词我不认识。然后背诵不认识的单词。

分析单词。我需要建立自己的单词库。存储认识的单词。刚认识的单词。

下一步是建立自己的单词数据库。
table: [known]
字段 key id word 读到过次数 read english Chinese sentence mp3 熟悉程度
    1  213123 silence [sil] no voice 安静 
    silence is no voice /path/silence.mp3
    
table: [sentence]
 id word sentence
 可重复


table: [history]
查询单词的历史记录
 
 table: [article]
 文章 id 读次数 单词数 认识单词个数  不认识单词数
 
关键还是读书。
nce
===

统计新概念英语中单词出现的次数、频率


sed 's/ /\n/g' */* | sed '/^$/d' | sort | uniq -c | sort -rn > test.txt


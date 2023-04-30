#!/bin/bash







# ./minishell -p 'ls -la | ls -a'
# ./minishell -p 'ls -la | echo KAAS | cat -e'
# ./minishell -p 'ls -la | ls | cat'
# ./minishell -p 'ls -la | cat -e | cat | cat | cat -e'
# ./minishell -p 'ls -la | wc | ls'
# ./minishell -p '< infile < infile2 PlsF cat -e | cat -e > outfile'
# ./minishell -p '< infile < infile PlsF cat -e | cat -e > outfile'
# ./minishell -p '< infile2 < infile PlsF cat -e | cat -e > outfile'
# ./minishell -p 'ls -la > outfile | wc -l > outfile'
# ./minishell -p 'ls -la > outfile | wc -l hoi2.txt >> outfile | cat -e'
# ./minishell -p 'ls -la >> outfile | cat -e'
# ./minishell -p 'ls -la > outfile | unset TEST | cat -e'
# ./minishell -p 'ls -la > outfile | unset TEST | cat -e'

# ./minishell -p 'ls | cat | grep m | ls -la | cat | wc | cat -e'
# ./minishell -p 'ls | cat | grep m | ls -la | cat -e | cat | cat -e'

./minishell -p 'cat | ls'
# ./minishell -p 'cat > outfile2| ls'
# ./minishell -p 'cat | cat | ls'

# ./minishell -p 'cat file.txt | cat | cat'
# ./minishell -p 'cat file.txt | cat | cat'
# ./minishell -p 'cat file.txt | cat | cat'
# ./minishell -p 'cat file.txt | cat | cat'
# ./minishell -p 'cat file.txt | cat | cat'
# ./minishell -p 'cat file.txt | cat -e file.txt'
# ./minishell -p 'cat file.txt | cat | cat -e'
# ./minishell -p 'cat file.txt | cat | cat -e'
# ./minishell -p 'cat file.txt | cat | cat -e'
# ./minishell -p 'cat file.txt | cat | cat -e'
# ./minishell -p 'cat file.txt | cat -e'

# ./minishell -p 'ls | ls | ls | ls'












# ./minishell -p 'ls -l'
#./minishell -p 'export'
# ./minishell -p 'export'  'export' 'export'
# ./minishell -p 'export test'
# ./minishell -p 'export test=mooi'
# ./minishell -p 'export test='

# ./minishell -p 'cd'
# ./minishell -p 'cd ~'
# ./minishell -p 'cd .'
# ./minishell -p 'cd ..'
# ./minishell -p 'cd obj'
# ./minishell -p 'cd ob'

# ./minishell -p '<< echo %<<$He llo' '|' 'echo Hello' 
# ./minishell -p 'echo -nn Hello'
# ./minishell -p 'echo -nns Hello World'

# ./minishell -p 'ls -la > outfile > outfile2 | cat -e | cat -e'
# ./minishell -p 'ls -la > outfile | cat -e | cat -e'
# ./minishell -p 'ls -la > outfile | cat -e | cat -e'
# # ./minishell -p 'echo "hello  $USER " > file | grep h | cat >> file | echo "done"'
# ./minishell -p 'echo ""hello  $USER"" > file | grep h | cat >> file | echo "done"'
# ./minishell -p 'echo 'hello  "$USEsR"' > file | grep h | cat >> file | echo 'done''
# echo 'hello  "$USEsR"' > file | grep h | cat >> file | echo 'done
# ./minishell -p 'echo -n -n Hello'
# ./minishell -p 'echo -n-n -nnn -n -n- Hello'
# ./minishell -p 'echo USER'
# ./minishell -p 'echo "s ' USER ' s" | echo "USER"          s '
# ./minishell -p 'echo "USER"'
# ./minishell -p 'echo $USER
# ./minishell -p 'echo $USER'
# ./minishell -p 'echo $USER 'plus''
# ./minishell -p 'echo "$USER 'plus'"'
# ./minishell -p 'echo ~'

# ./minishell -p '> a'
# ./minishell -p '< a'
# ./minishell -p '>> a'
# ./minishell -p '<< a'

# ./minishell -p '$'
# ./minishell -p '$$'
# ./minishell -p '$$$'
# ./minishell -p '$?'
# ./minishell -p '$?$'

# ./minishell -p 'env'
# ./minishell -p 'top'

# ./minishell -p '  ls | cat | cat | cat           | cat -e'
# ./minishell -p 'ls | cat | cat -e | cat | cat -e'


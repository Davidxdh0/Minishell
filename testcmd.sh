#!/bin/bash







# ./minishell -p 'ls -la | cat | wc -l'
# ./minishell -p 'ls -la | wc | cat -e'
# ./minishell -p 'ls -la | ls | cat'
# ./minishell -p 'ls -la | cat -e | cat | cat | cat -e'
# ./minishell -p 'ls -la | wc | ls'
# ./minishell -p 'ls -la > outfile | < Makefile wc -l > outfile | cat -e > outfile'
./minishell -p 'ls -la > outfile | unset | cat -e'

# ./minishell -p 'ls | cat | grep m | ls -la | cat | wc | cat -e'
# ./minishell -p 'ls | cat | grep m | ls -la | cat -e | cat | cat -e'

# ./minishell -p 'cat file.txt'
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

# ./minishell -p 'echo "hello  $USER " > file | grep h | cat >> file | echo "done"'
# ./minishell -p 'echo "hello  $USER" > file | grep h | cat >> file | echo "done"'
# ./minishell -p 'echo -n -n Hello'
# ./minishell -p 'echo -n-n -nnn -n -n- Hello'
# ./minishell -p 'echo USER'
# ./minishell -p 'echo "s ' USER ' s"' 
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

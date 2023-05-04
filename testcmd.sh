#!/bin/bash

# ./minishell -p 'ls'
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
# PARSING
# ./minishell -p 'ls -la > outfile | cat -e | cat -e'
# ./minishell -p '<< redirect < redirect > $redirect >> redirect'
# EXPANDING
# ./minishell -p '<< redirect < redirect > $redirect >> redirect'
# ./minishell -p " < mooi ls -la > outfile > outfile2 | cat -e | cat -e"

# ./minishell -p 'ls -la > outfile | cat -e | cat -e'
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

#		redirects < 
# ./minishell -p '< "  a"' #werkt niet
# ./minishell -p '< "a"' #werkt niet
# ./minishell -p '< "$USER"' #NIET = VAR
# ./minishell -p '< ""' #NIET = VAR
# ./minishell -p '< 'a'' # V
# ./minishell -p '< '$a'' # ?
# ./minishell -p '< $USER' #V
# ./minishell -p '< $a'

#		redirects >
# ./minishell -p '> a'
# ./minishell -p '> 'a''
# ./minishell -p '> "USER"'
# ./minishell -p '> "USER "'
# ./minishell -p '> $a'
# ./minishell -p '> '$a''
# ./minishell -p '> "$a"'

# ./minishell -p '>> a'
# ./minishell -p '<< ""'

#	VARIABLE
# ./minishell -p '$'
# ./minishell -p '$$'
# ./minishell -p 'echo $'
./minishell -p 'echo "ss $USER sss" | echo $?'
./minishell -p 'echo "$USER" | echo $?'
./minishell -p 'echo "$USER" | echo $?'
./minishell -p 'echo '$USER' | echo $?'
# ./minishell -p 'echo $'
# ./minishell -p 'echo $'
# ./minishell -p '$?'
# ./minishell -p '$?$'

# ./minishell -p 'env'
# ./minishell -p 'top'

# ./minishell -p '  ls | cat | cat | cat           | cat -e'
# ./minishell -p 'ls | cat | cat -e | cat | cat -e'


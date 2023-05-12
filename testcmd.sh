#!/bin/bash

#te fixen echo $? goed expanden met als het tweede command = 0
# ./minishell -p 'export a=b"end"'
./minishell -p '> "echo "USER  s"'
# ./minishell -p 'ls'
# ./minishell -p 'export'
./minishell -p 'export'  'export' 'export'
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
./minishell -p 'echo "USER"'
./minishell -p 'echo $USER'
./minishell -p 'echo $USER'
./minishell -p 'echo $USER 'plus''
./minishell -p 'echo "$USER 'plus'"""'
# ./minishell -p 'echo ~'

#		redirects < 
# ./minishell -p '< "  a"' #werkt
# ./minishell -p '< "a"' #werkt 
# ./minishell -p '< "$USER"' #
# ./minishell -p '< ""' #
# ./minishell -p '< 'a'' # V
# ./minishell -p '< '$a'' # 
# ./minishell -p '< $USER' #V
# ./minishell -p '< $a'

#		redirects >
# ./minishell -p '> a'
# ./minishell -p '> 'a''
# ./minishell -p '> "USER"'
# ./minishell -p '> "USER "'
# ./minishell -p 'Hello > $a'
# ./minishell -p 'echo test > $USER $A'
# ./minishell -p '> "$a"' #faalt

#		redirects >> 
# ./minishell -p '>> a'
# ./minishell -p '>> a'
# ./minishell -p '>> 'a''
# ./minishell -p '>> "USER"'
# ./minishell -p '>> "USER "'
# ./minishell -p 'Hello >> $a'
# ./minishell -p 'echo test >> $A'
# ./minishell -p 'ls >> "$a"' #faalt


#		redirects <<
# ./minishell -p '<< ""'

#	VARIABLE
# ./minishell -p '$'
# ./minishell -p '$?'
# ./minishell -p '$$'
# ./minishell -p 'echo $'
# ./minishell -p 'echo "ss $USER sss" | echo $?'
# ./minishell -p 'echo "$USER" | echo $?' 
# ./minishell -p 'echo "$USER$USER" | echo $?'
# ./minishell -p 'echo '$USER' | echo $?'
# ./minishell -p 'echo $'
# ./minishell -p 'echo $'
# ./minishell -p '$'
# ./minishell -p 'echo $USER $shes $USER $USER'

# ./minishell -p 'env'
# ./minishell -p 'top'

# ./minishell -p '  ls | cat | cat | cat           | cat -e'
# ./minishell -p 'ls | cat | cat -e | cat | cat -e'

# 		syntax check pipe
# ./minishell -p 'echo "|" | cat e'
# ./minishell -p 'echo "hoi 1 2 3" | cat "e" '
# ./minishell -p '|'
# ./minishell -p '||'
# ./minishell -p 'ls ||'

# 		syntax check redirects
# ./minishell -p '<'
# ./minishell -p '<<'
# ./minishell -p '>'
# ./minishell -p '>>'
# ./minishell -p 'ss < '
# ./minishell -p 'ss << '
# ./minishell -p '> ss'
# ./minishell -p 'ss >>'
#EVAL
# ./minishell -p '' # ?
# ./minishell -p ' '
# ./minishell -p '   ' #segmentation fault.
# ./minishell -p '   \t ' #
 
# ./minishell -p '\t \t' #  cmd[0] = \t en cmd[1] = \t
# ./minishell -p '/bin/ls '
# ./minishell -p '/bin/ls | cat'
# ./minishell -p 'echo HELLO'
# ./minishell -p 'echo -nnn HELLo'
# ./minishell -p 'exit' 
# ./minishell -p 'exit | echo $?' # = 0 en exit niet'
# ./minishell -p 'exit(1)' # bash: syntax error near unexpected token `1'
# ./minishell -p '/bin/ls '
# ./minishell -p '/bin/ls'
# ./minishell -p '/bin/ls filethatdoesntexist' #TEST!! ls: filethatdoesntexist: No such file or directory

# #SIGNALS check

# ./minishell -p 'echo "cat lol.c | cat > lol.c"'
# ./minishell -p 'echo "HELLO"'
# ./minishell -p 'ECHO 'hello'' 
# ./minishell -p 'echo '$USER''
# ./minishell -p 'env'
# ./minishell -p 'export'
# ./minishell -p 'cd . | /bin/ls'
# ./minishell -p 'cd .. | /bin/ls'
#unset path
#redirections
#pipes
#history

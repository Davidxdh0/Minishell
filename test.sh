#!/bin/bash

# This is a simple tester for minishell

./minishell -p 'ls'
./minishell -p 'echo Hello'
./minishell -p 'echo -n Hello'
./minishell -p 'echo USER'
./minishell -p 'echo USER'
./minishell -p 'echo $USER'

./minishell -p '> a'
./minishell -p '< a'
./minishell -p '>> a'
./minishell -p '<< a'

# ./minishell -p 'env'
# ./minishell -p 'top'

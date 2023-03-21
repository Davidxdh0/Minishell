# 42 Minishell a bash knockoff

How do I push a local Git branch to master branch in the remote?
I would say:

git checkout master
git pull               # to update the state to the latest remote master state
git merge develop      # to bring changes to local master from your develop branch
git push origin master # push current HEAD to remote master branch

OR

$ git push origin develop:master

or, more generally

$ git push <remote> <local branch name>:<remote branch to push into>


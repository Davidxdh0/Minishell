# 42 Minishell a bash knockoff

https://blog.greenroots.info/top-10-git-commands-every-developer-should-know

van branch naar master pushen:
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

vanuit branch up to date met master:
git checkout david
git pull origin master

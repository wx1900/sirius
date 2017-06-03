git notes
git init // to turn a directory to a repository git could control
git add readme.txt // to add files to repository
git commit -m "notes" // to commit a file to repository
git log // show the log from recently to remote
git reset --hard HEAD^ //get back to last version
git reflog // all your commands
git status // look up your status
git diff HEAD --readme.txt // the difference
git checkout --readme.txt // drop the edit in your workspace
git reset HEAD file // unstage drop the file already add but not commit yet
git rm fiel // delete file from repository

remote repository
git remote add origin git@github.com:michaelliao/learngit.git //add to the remote repository 
git push -u origin master // add all files to the remote repository
git push origin master // after that
git clone git@github.com:youaccount/gitskills.git //clone from the remote repository

dev
git checkout -b dev // equals : git branch dev ; git checkout dev
git branch //checkout the current branchs
git merge dev // merge to the master
git brach -d dev // delete dev
git merge --no-ff -m "merge with no-ff" dev // forbidden use "fast forward"
git push origin brach-name // push your update
git pull // if failed may be the remote version is newer so merge first
git branch --set-upstream branch-name origin/brach-name
git remote -v // check out the remote repository


@echo off
set ADDR=https://github.com/kino-6/lgp_cpp.git
git init
git pull %ADDR%
git add .
git status
git commit -m "commit"

rem remote
git remote rm origin
git remote add origin %ADDR%
git remote -v

rem masterにpush
git push -u origin master
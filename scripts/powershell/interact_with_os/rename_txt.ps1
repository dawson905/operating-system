Get-ChildItem *.txt | Rename-Item -NewName { "OLD_"+$_.Name }

# Github Merging

---

Pick a partner that you want to work with for next week's final project.  You'll be making a video game!

Create a github repo for the project which you both have write access to (one of you can make it and add the other as a collaborator)

The goal of this lab for you to practice performing merges as you both edit the files in the repo

## Easy mode

Create a merge commit which doesn't have any conflicts by doing the following

* Partner 1: edit the readme file, commit, and push
* Partner 2: before pulling the changes from partner 1, create a new file, add and commit it, then pull from github

This should cause partner 2 to have to perform a merge, but there should be no conflicts since you didn't edit the same files in your commits

Once the merge is completed, push partner 2's changes, and make both partner's local repos have all the latest changes (verify with `git log`)

Repeat the process with roles reversed

## Hard mode

Sync up again, then both partner edit the same line of the same file, commit, and then try to push.

Whoever pushes second will not be able to, and will have to perform a merge with a conflict.

One the conflict is resolved, the merge is completed, and pushed, repeat the process with the other partner performing a conflicted merge


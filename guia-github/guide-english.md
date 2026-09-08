# <p style="text-align: center;">**Basic git-GitHub guide**</p>

## 1. Installation.

First, git must be installed on the computer ([https://git-scm.com/](https://git-scm.com/)).

Once installed, its correct installation can be verified by running the command `git --version` in the CMD. Something like `git version 2.54.0.windows.1` should appear.

## 2. Create an account on GitHub

GitHub is a service, distinct from git, which is a program. To use git, it is only necessary to have it installed. To use GitHub, an account is needed:

An account must be created on GitHub ([https://github.com/](https://github.com/)). The username or the associated email is important, remember it.

## 3. Link GitHub account with git

Once the account is created on GitHub, it must be connected with git on the computer. To do this, two commands must be run in the CMD:

* `git config --global user.name "[GitHub username]"`
* `git config --global user.email "[email address]"`

## 4. Create the project folder

Once linked, on the computer, the folder in which you want to work and manage as a repository must be created. Normally, no spaces are left in its name, but rather the words in the name are separated by hyphens, `-`. For example, `GitHub-Information` or `General-Testing-Repository`. By convention, the use of uppercase letters is also usually avoided.

Once created, work can be added or not to the folder before connecting it to GitHub.

## 5. Open the project in *Visual Studio Code*

After creating it, the repository folder in which you want to work must be opened in *Visual Studio Code* (*Open Folder → [Repository]*).

This opens the folder in VS Code as the main directory of a project. (This implies that inside this folder, for example, the pdfs generated with Python will appear).

## 6. Enter GitHub on the Internet and create a repository

On [GitHub](https://github.com/), a repository must be created by clicking the 📕*New* button. It leads to the following page:

In this example, the repository has been created as public, which implies that everyone can see it, clone it, and download files from here. However, to be able to contribute, permissions must be requested, as can be seen later.

Once created, instructions appear to connect the repository with local files:

## 7. Connect the GitHub repository with the local one

Now, using *Visual Studio Code*, proceed to connect the repository created on GitHub with the local files.

### In case of having an empty repository or wanting to discard what is there

To do this, we open a *Terminal* in *Visual Studio Code* in the folder we want to connect. In this, the following commands are written in order:

* `git init`: initializes a local git repository on our equipment.
* `git remote add origin [https://github.com/](https://github.com/)[username]/[remote repository name].git`: penultimate line indicated in the GitHub instructions to connect the repository with local files. Links the local repository with the remote one.

### In case of wanting to link an existing repository (and with content)

You can navigate with the terminal or open directly inside the folder where you want to place the repository. This process will result in **a folder with the name of the repository** inside the location where the command is executed. Once there, execute:

```bash
git clone [REPO_URL]

```

For reliability reasons, the repo URL can be obtained from the `code` button that appears on the main page, and the SSH option is the most robust for this command.

This command could fail if the GitHub user does not have permissions or is not a collaborator in a private repository.

## 8. Start adding and staging changes

Once initialized, there might already be changes in the local repository or not. To see this, the `git status` command can be run, which gives information about the repository's status, the files, and if they are being *tracked*, as well as if a *merge* or *rebase* is being done. If files appear in red, it means they are not being *tracked*, there are changes to update.

For git to start *tracking* the files and updating them, they must be added to the *Staging area*. To do this, one of the following commands must be used:

* `git add [name of the added file with its extension]`: adds the file `[name of the added file with its extension]` to the commit, which would appear in red in the *Terminal* when running `git status`.
* `git add .`: adds all files in the directory where it is executed to the *Staging Area*. If they were already inside, nothing happens. It is the best way to ensure that all files that were in red are added.

If `git status` is run again, the previous files appear in green.

With this, the commit can now be made. To do this, the command `git commit -m "[desired description to characterize the commit]"` must be run. Upon doing so, a brief description of what has happened appears. A commit is a 'photo' of the current state of the working folder (the repository), so that changes are saved and could be reverted to.

This way, locally, everything is ready to upload to GitHub. It is recommended to run `git status` again beforehand to verify that everything has been stored correctly and there are no errors.

## 9. Upload changes to GitHub

To upload changes to GitHub, the `git push` command must be run.

* In case it is the first time information is uploaded to the remote repository, an error will occur, because the necessary *branch* has not been created. Therefore, this *branch* must be set before being able to do *push*. In the *Terminal*, git already offers the command that must be used, `git push --set-upstream origin main`. Upon doing so, it appears that the content has indeed been uploaded to GitHub.

The name of the main branch used to be `master`, but this is being deprecated and most repositories use the new convention of calling the main branch `main`.

Now, if we go to the repository on GitHub, it can be seen that the modifications have occurred and the description for the corresponding files is included, like this:

## 10. Limit files uploaded to GitHub (`.gitignore`)

If you do not want all local files to be uploaded to the remote repository, a `.gitignore` file must be created at the first level inside the repository folder. In this, the extensions, folders, or files that you want or do not want to include when doing `git add .` using `bash` syntax are included. For example:

```bash
# So that extensions, files, or folders are not uploaded to GitHub unnecessarily.

# Do not include any folder named "out".
**/out/*
# Do include any .pdf inside any "out" folder.
!**/out/*.pdf 
# Do not include files of an extension located at any level.
*.log
*.aux
*.f06


```

It must be taken into account that, in case of adding extensions or files to the `.gitignore` after they already exist in the *staging area*, git will not start ignoring them, and they will not disappear from GitHub. In this case, the command `git rm --cached -r .` must be written, which removes all files from the *staging area*. From here on, `git add .` will respect the `.gitignore` rules.

## 11. Download changes made by other users

If working in a group project, when other users with access to the remote repository make changes and upload them to GitHub with `git push`, to be able to work locally with the most updated version, that latest version must be downloaded locally. To do this, the `git pull` command must be executed in the repository's *Terminal*.

It is worth mentioning that the standard way to check if there has been work in the remote repository that is not in the local one is to run the sequence `git fetch` + `git status`, which receives, detects, and indicates the differences between repositories. After this, `git pull` is executed.

In case several users have made changes and want to do `git push` from local repositories in different states, an error appears in the *Terminal* of the one doing `git push` later. To resolve this, everything must be *merged* to a final version, deciding which changes you want to keep in this last version. To do this, `git pull` must be done first. Then, the conflicts in the files are corrected directly or with the *Merge Editor* of *Visual Studio Code*, which does a subsequent *merge*, generating the final version with the combined changes as desired. Finally, the usual sequence to upload changes can be followed (`git add .` + `git commit -m "[description]"` + `git push`). In this way, an updated version that combines the simultaneous changes made by the two users would be uploaded to the remote repository.

* It is possible that when doing this in *Visual Studio Code*, the *Terminal* remains in *rebase* or *merge* mode, preventing continuation with the necessary commands to upload the changes to the remote repository. To exit these modes, the following different commands can be executed:
* `git merge --abort`: aborts the merge, and returns to the state before running `git pull`.
* `git rebase --abort`: aborts the rebase, and returns to the state before running `git pull`.

If you want to avoid this for next time, the `git` configuration can be changed:

* `git config pull.rebase false` : Avoids entering *rebase* mode the next time a *merge* is necessary in this repository.
* `git config --global pull.rebase false` : Avoids entering *rebase* mode the next time a *merge* is necessary in all repositories (global `git` configuration).

Supposedly, it is enough to run the desired command once so that the *Terminal* no longer stays in those modes and defaults back to the usual operation after doing a *merge* or *rebase*. However, the *VS Code* terminal sometimes gets fussy, and a good way to avoid this has not yet been found.

## 12. Download another user's remote repository

To work in the indicated manner but in a repository created by another user, you must navigate to a folder where you want to copy the repository. Opening a terminal in that folder, the command must be executed:

```bash
git clone [GitHub repository url]


```

Which creates a local copy of the remote repository and connects it with GitHub.

From here on, you already have all the files. If you have write permissions (the remote repository owner has added the user as a collaborator), the standard workflow can be used. If not, the section on **collaborating without being a collaborator** should be consulted.

## 13. View change history (`git log`)

To check the made commits:

```bash
git log --oneline

```

Shows a summarized line per commit with its ID (the hash) and message, useful to identify references when using `git reset`. The *Terminal* might remain 'busy' after running this command. To solve this, simply press the `q` (lowercase) key.

## 14. Revert commits (`git reset`)

If you need to undo a commit (for example, after adding a file that exceeds GitHub's 100 MB limit):

```bash
git reset --[type] [commit-ID]

```

Reset types:

* `--hard`: Restores the repository and files exactly to the commit state (unsaved local changes are lost).
* `--soft`: Keeps local files intact and leaves all subsequent changes in the *staging area*.
* `--mixed`: Keeps local files intact but empties the *staging area* to the indicated commit state.

**Example to remove a large file (e.g. `.f06`) already committed:**

If it is not clear in which commit the file was added, but the commits are not being uploaded to the remote repository (to GitHub), the local commits can be deleted **without losing the work** and remove the large file from the *staging area*.

```bash
git reset --mixed origin/main #mixed to keep local files
git add .
git rm --cached *.f06 #we remove all files with .f06 extension
git commit -m "Correct commit and exclude .f06"
git push

```

## 15. Create a working branch

To work more properly and not affect the work of others, independent working branches can be created that, while maintaining the same command logic already described, separate from the main branch and do not affect it. Later, they can be *merged* with the main one if desired.

To see all branches open in the local repository, you can run

```bash
git branch

```

To see all branches open in the local and remote repository (simultaneously) you can run:

```bash
git branch -a

```

Before creating a new branch, if we are in `main`, it is highly recommended to run `git pull` to ensure the branch starts from the most recent state of `main`.

To create a branch, the command must be run:

```bash
git branch [branch name]

```

Then, to switch to it and work on it, run:

```bash
git checkout [branch name]

```

Here work is already done in the usual way.

* Both steps can be joined with the command `git checkout -b [branch name]`, which creates the branch and switches you to it.
* When the work is finished and you want to upload a *commit* to the remote repository, you have to tell `git` that it now has to upload the changes to a new branch. `git` is smart enough to give the error if the `git checkout` command has already been executed. So, after the standard workflow:

```bash
git add .
git commit -m "description of changes"

```

The `-u [branch-name]` flag must be added to the `git push`:

```bash
git push -u origin [branch-name]

```

Once the desired work in the branch is finished, it can be *merged* with the main branch (usually called `main` or `master`). To do this, the command `git checkout [name of the branch you want to keep, usually main or master]` is executed to move to the desired branch, and then `git merge [name of the branch you wish to merge]`. A `git pull` can be run in between to load possible changes in the `main` or `master` branch so there are no conflicts.

For example, to merge *feature* with *main*, the workflow would be:

1. `git checkout main`
2. `git merge feature`
3. Resolve possible conflicts in the *merge*.

Also, if you want to delete a branch in your GitHub remote repository once it has already been merged with `main`, the command must be executed:

```bash
git push origin --delete [name of the branch to delete]

```

## 16. Personal Access Tokens (PAT) for virtual machines

To clone or operate in remote environments where web login is not viable:

1. On GitHub: Profile $\to$ *Settings* $\to$ *Developer settings* $\to$ *Personal access tokens* $\to$ *Fine-grained tokens* $\to$ *Generate new token*.
2. Select *All repositories*.
3. In *Permissions*, configure with read and write permissions (*Read and write*):

* *Contents*
* *Pull requests*
* *Commit statuses* (The *Metadata* field will be added automatically in read mode).

4. Generate, copy the token and use it as a password when authenticating in the remote terminal.

# Collaboration on GitHub

The main reason why it has been decided to use this tool for collaboration in the Flying Club is version control and its versatility. Although the length of this guide demonstrates that it is somewhat complex to use, the combination of git + GitHub allows for constant availability so that any member can access the Club's designs, codes, and documentation.

This section explains how to collaborate. There are two main ways.

## A) Without being a collaborator

You cannot collaborate directly to a repository unless the owner has added the user as a collaborator. Without this permission, the workflow is the **Fork and Pull-Request**.

### 1. Fork the Repository

On the GitHub page of the original repository, click on the **Fork** button (top right). This will create a copy of the original repository, which you own, but is linked to the original repo.

### 2. Clone your *Fork*

Clone the URL of the *Fork* that was just created:

```bash
git clone https://github.com/[your-username]/[repo-name].git

```

### 3. Make a new branch and commits

Make a new branch, make the changes, and commit to save them locally:

```bash
git checkout -b branch-name
git add .
git commit -m "Description of changes"

```

### 4. Push to your *Fork*

Since you are the owner of the *Fork*, you have permissions to upload the changes to the remote:

```bash
git push -u origin branch-name

```

### 5. Create a Pull Request (PR)

Go to the [the original repository's page](https://github.com/Ohmyus/club-de-vuelo) on GitHub. A banner will automatically appear suggesting opening a *Pull Request*. Click on "Compare & pull request", add a description of your changes or work to help the reviewer, and submit it. Then the repository owner or collaborators will be able to review, approve, and *merge* your work or code into the repository.

### 6. Stay updated

It is possible that during the time you are working, the original repository receives *commits*, which when working on a copy of the repository, are not applied automatically to the *fork*.

To maintain synchronization with the original repository, there is a **Sync Fork** button on GitHub, which is in charge of applying the commits in the original repository to the *fork*.

All this work can be done locally, defining an 'upstream' repository with the address of the original repo. In this way, you can later `git pull` the changes that have been made in the original repo.

1. Define 'upstream':

```bash
git remote add upstream [url-of-original-repo.git]

```

2. *Pull* the most recent changes to the local repo

```bash
git pull upstream main

```

3. After making the *commit*, `push` to the *forked* repo:

```bash
git push origin main

```

## B) Being a collaborator

To be a collaborator in a repository, the owner must be asked to add you as a collaborator. Once this is done, the operation is the same as it would be if you were the owner of the repository.

# Summary

## Upload changes to GitHub

Every time you want to upload changes to the repository, the following steps must be performed:

* #### 0. Make the changes in the local repository and save: `Ctrl + s`.


* #### 1. Open the *Terminal* in the repository folder (Ctrl + ñ in *VS Code*).


* #### 2. (optional, to check that there are *unstaged changes*) `git status`


* #### 3. `git add .`


* #### 4. (optional) `git status`)


* #### 5. `git commit -m "[descriptive message]"`


* #### 6. (optional) `git status`)


* #### 7. `git push`


* #### 8: Verify the correct repository update on GitHub.



## `.gitignore` management

* #### 1. Create the `.gitignore` before the files you want to ignore exist.


* #### (2.) In case files have been generated that are later decided to be ignored, update the `.gitignore` and use the command `git rm --cached -r .`



## Download changes from GitHub

* #### 1. `git fetch`


* #### 2. `git status`


* #### 3. `git pull`



## Resolve conflicts when doing `git push`

* #### 1. `git pull`


* #### 2. *Merge* the changes in the desired way.


* #### 3. `git add .`


* #### 4. `git commit -m "[description]"`


* #### 5. `git push`



## Create and *merge* branches

* #### 1. `git checkout -b [branch name]`


* #### 2. Upload and download changes from GitHub in the same way as in the `main` branch


* #### 3. `git checkout main`


* #### 4. `git merge [branch name]`


* #### (5.) If you want to delete from the remote repository, `git push origin --delete [branch name]`



## Download and connect remote repository

* #### 1. `git clone [GitHub repository url]`



## Collaborate without being a collaborator in the repository:

* #### 1. Fork the repository


* #### 2. Clone the *forked* repository: `git clone [forked repo url]`


* #### 3. Open a new branch: `git checkout -b descriptive-name`


* #### 4. Do the work, you can make *commits* to save your progress:



```bash
git add .
git commit -m "Added something"

```

* #### 5. Upload the changes to the branch you have opened:



```bash
git add .
git commit -m "finished work on descriptive-name"
git push -u origin descriptive-name

```

* #### 6. Create a *Pull Request*

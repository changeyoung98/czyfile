# What is Git Workflow?
## - Definition
### A Git Workflow is a **recipe** or **recommendation** for how to use Git to **accomplish work** in a consistent and productive manner. 
------
## - Different types of Workflows
### 1. Centralized Workflow
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-svn.png&objectId=1190000002918123&token=18dea553725e6476043e5f15aaa01357)
#### - a great Git workflow for teams transitioning from SVN
#### - uses a central repository to serve as the single point-of-entry for all changes to the project
#### - doesn’t require any other branches besides *master*

### 2.Feature branching
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-feature-branch-1.png&objectId=1190000002918123&token=7b6b5ef4d971842877613c04afd454f6)
#### -all feature development should take place in a dedicated branch instead of the master branch
#### -makes it easy for multiple developers to work on a particular feature without disturbing the main codebase
#### -the master branch should never contain broken code, which is a huge advantage for continuous integration environments. 
### 3.Gitflow Workflow
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflows-gitflow.png&objectId=1190000002918123&token=ee270ee95a574ec7c0b3161043b94ea0)
#### -defines a strict branching model designed around the project release
#### -assigns very specific roles to different branches and defines how and when they should interact
### 4.Forking Workflow
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflows-forking.png&objectId=1190000002918123&token=556ec96e04a6af9aa60d8ec1c999ba30)
#### -it gives every developer a server-side repository
#### -each contributor has not one, but two Git repositories: a private local one and a public server-side one
### 5. Pull Requests
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/pull-request-overview.png&objectId=1190000002918123&token=a11eee54c054994945f6ca5aa279f566)


------

##  - Some things to consider when evaluating a Git workflow are:
#### -  Does this workflow scale with team size?
#### -  Is it easy to undo mistakes and errors with this workflow?
#### -  Does this workflow impose any new unnecessary cognitive overhead to the team?

------

# Why should we use Git workflow?
## Total consideration
### When working with a team on a Git managed project, it’s important to make sure the team is **all in agreement** on how the flow of changes will be applied. **To ensure the team is on the same page**, an agreed upon Git workflow should be developed or selected.
## Using Git to power your development workflow presents a few advantages over SVN.
### -it gives every developer their own local copy of the entire project
### -it gives you access to Git’s robust branching and merging model

----
# How to use it?
## Some key points:
### -There is no one-size-fits-all Git workflow
### -A workflow should be simple and enhance the productivity of your team
### -Your business requirements should help shape your Git workflow

-----
## Let's take centralized workflow as an example

### 1.Initialize the central repository
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-svn-push-local.png&objectId=1190000002918123&token=cb6d4428bd989a9db24ea68b29588a67)

 First, someone needs to create the central repository on a server.
 ![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-svn-initialize.png&objectId=1190000002918123&token=87ea7a312eea3ac60744ef5997f686c7)

 If it’s a new project, you can initialize an empty repository. Otherwise, you’ll need to import an existing Git or SVN repository.They should always be bare, like this:
>ssh user@host git init --bare /path/to/repo.git
### 2. Hosted central repositories
The process of initializing a bare repository discussed above is handled for you by the hosting service. The hosting service will then provide an address for the central repository to access from your local repository.
### 3. Clone the central repository
Next, each developer creates a local copy of the entire project. This is accomplished via the git clone command:
>git clone ssh://user@host/path/to/repo.git

![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-svn-clone.png&objectId=1190000002918123&token=74230960454bff61cc38e28016dde2c4)
### 4. Make changes and commit
Once the repository is cloned locally, a developer can make changes using the standard Git commit process


    git status # View the state of the repo
    git add <some-file> # Stage a file
    git commit # Commit a file</some-file>> 

### 5. Push new commits to central repository
Once the local repository has new changes committed. These change will need to be pushed to share with other developers on the project.

    git push origin master
This command will push the new committed changes to the central repository. 
### 6. Managing conflicts
The central repository represents the official project, so its commit history should be treated as sacred and immutable.If a developer’s local commits diverge from the central repository, Git will refuse to push their changes because this would overwrite official commits.
![](https://segmentfault.com/image?src=http://static.ixirong.com/pic/gitflow/git-workflow-svn-8.png&objectId=1190000002918123&token=e9fff79b5189565698de39b45d42551d)
Before the developer can publish their feature, they need to fetch the updated central commits and rebase their changes on top of them. 

------
# That's all. Thank you.
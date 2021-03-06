[//]: # (author:    alex oswald)
[//]: # (course:    eece 2560)
[//]: # (semester:  fall 2021)
[//]: # (group:     philip andress, colin boisvert)
[//]: # (group-num: 3)
[//]: # (group-id:  AndBoiOsw)
[//]: # (professor: ninfang mi)

# EECE 2560 – Fundamentals of Engineering Algorithms

Submission convention ex:  `3-AndBoiOsw-5a.zip`

Dev environment:  **Clion** using [CodeWithMe](https://www.jetbrains.com/code-with-me/)

#### Final Scores

| Name                         | Due                 | Comments                                                                       | 
|------------------------------|---------------------|--------------------------------------------------------------------------------| 
| Project #1 MasterMind-a      | 85 / 100            | Significant errors in one important function -- check<br> incorrect is wrong 25/40 | 
| Project #1 MasterMind-b      | 98 / 100            | small errors in one important function -- no out of <br>range error handler 38/40.  i think this was also more<br> fkd up than we were docked for bc we started super<br> last min | 
| Project #2, Flip Cards-a     | 100 / 100           | submission comment: "🥴"                                                       | 
| Project #2, Flip Cards-b     | 100 / 100           |                                                                                | 
| Project #3 Word Search-a     | 100 / 100           |                                                                                | 
| Project #3 Word Search-b     | 100 / 100           |                                                                                | 
| Project #4 Sudoku a          | 100 / 100           |                                                                                | 
| Project #4 Sudoku b          | 115 / 100           | see other [notes](proj4b/README.md)                                            | 
| Project #5 Maze a            | 100 / 100           | see other [notes](proj5a/README.md)                                            | 
| Total                        | 1,459.00 / 1,500.00 | **A**                                                                          | 


Recommended `.zshrc` settings to make life easier (testing out of clion is od necessary too):

```zsh
alias gbuild="g++-11 main.cpp -o main -pedantic -Wall -Wextra -I/opt/homebrew/include/ -Wno-sign-compare"
alias grun="g++-11 main.cpp -o main -pedantic -Wall -Wextra  -I/opt/homebrew/include/ -Wno-sign-compare; ./main"

alias g++="$(echo /opt/homebrew/Cellar/gcc/*/bin/g++-*)"
alias gcc="$(echo /opt/homebrew/Cellar/gcc/*/bin/gcc-* | cut -d" " -f1)"
alias clang="/opt/homebrew/opt/llvm/bin/clang"
alias clang++="/opt/homebrew/opt/llvm/bin/clang++"
alias lldb="/opt/homebrew/opt/llvm/bin/lldb"
alias clangd="/opt/homebrew/opt/llvm/bin/clangd"
```

Better resources:

 - Library:  [boost](https://www.boost.org/doc/libs/)
 - Library:  [gnu scientific library](https://www.gnu.org/software/gsl/doc/html/index.html)

#### clangd config for alt txt editors: ~/Library/Preferences/clangd/config.yaml

```yaml
CompileFlags:
  Add: [-xc++, -std=c++17, -Wall, -pedantic, -Wextra, -I/opt/homebrew/include/]
  Remove: [-Wsign-compare]

Diagnostics:
  ClangTidy:
    Add: [modernize*, boost*]
    Remove: misc-definitions-in-headers
    CheckOptions:
      readability-identifier-naming.VariableCase: CamelCase
```

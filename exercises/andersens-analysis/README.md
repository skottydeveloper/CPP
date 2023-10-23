# Andersen's Analysis
## AA Folder Layout

$tree Assignment-3

|-- Assignment-3.cpp

|-- Assignment-3.h

|-- CMakeLists.txt

|-- Test3.cpp

`-- testcase
    
    |-- bc

    |   |-- CI-global.ll

    |   `-- CI-local.ll
    
    `-- src
        |-- CI-global.c

        `-- CI-local.c

## Instructions
1. Install the "Docker", "Remote Containers" and "C/C++" extensions in VSCode.
2. Enter this command in cmd or terminal: `docker pull svftools/teaching-software-analysis:latest`
3. Then enter: `docker run -itd svftools/teaching-software-analysis:latest /bin/bash` (remove `/bin/bash` for Windows).
4. On the sidebar, click on the Docker icon. Under "Containers", right click the container item and select `Attach to Visual Studio Code`.
5. If you can't see the working directory, please select: `File -> Open (folder)`, then enter: `/home/SVF-tools/Teaching-Software-Analysis`.
6. Ensure that you have the latest code template, by typing `cd $HOME/Teaching-Software-Analysis` and `git pull` in the terminal.
7. Open the "Assignment-3" folder from the file explorer on the left side, and then copy and paste the "Assignment-3" cpp code from this project into the "Assignment-3" cpp file in Visual Studio Code.
8. Then, in the terminal - type: `cd Assignment-3`, and `make`.
9. Then, in the terminal again - type: `cd ..`, and `./bin/assign-3`.
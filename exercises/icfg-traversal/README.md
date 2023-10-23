# ICFG Traversal
## ICFG Folder Layout

$tree Assignment-2

├── Assignment-2.cpp

├── Assignment-2.h

├── Test2.cpp

├── CMakeLists.txt

## Instructions
1. Install the "Docker", "Remote Containers" and "C/C++" extensions in VSCode.
2. Enter this command in cmd or terminal: `docker pull svftools/teaching-software-analysis:latest`
3. Then enter: `docker run -itd svftools/teaching-software-analysis:latest /bin/bash` (remove `/bin/bash` for Windows).
4. On the sidebar, click on the Docker icon. Under "Containers", right click the container item and select `Attach to Visual Studio Code`.
5. If you can't see the working directory, please select: `File -> Open (folder)`, then enter: `/home/SVF-tools/Teaching-Software-Analysis`.
6. Ensure that you have the latest code template, by typing `cd $HOME/Teaching-Software-Analysis` and `git pull` in the terminal.
7. Open the "Assignment-2" folder from the file explorer on the left side, and then copy and paste the "Assignment-2" cpp code from this project into the "Assignment-2" cpp file in Visual Studio Code.
8. Then, in the terminal - type: `cd Assignment-2`, and `make`.
9. Then, in the terminal again - type: `cd ..`, and `./bin/assign-2`.

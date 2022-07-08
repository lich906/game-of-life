## Game of Life
This C++ application implements classic [Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) with aperiodic rules.

---
### Installation
* Windows x32 installer: [game-of-life_setup.msi](https://github.com/lich906/game-of-life/releases/download/20220630/game-of-life_setup.msi)

---
### How to play

1. First, you have to determine the initial state of cells. CLICK on the field area by left mouse button to make cell alive. You can reset cell status with `Backspace`
2. When you've done with initialization simply hit `Enter` button to RUN GAME
3. Game will continue run until you close the window.
4. You can go back to initialization using `Backspace`
* Note that the game will not stop if a cyclic or stable state is reached

---
### Settings
To adjust game process you can use `config.txt` file.
Explore `config_sample.txt` file for more info.

---
### Build project
#### Using Visual Studio:
Set following project properties:
* Windows SDK Version: 10.0.19041.0
* Platform Toolset: Visual Studio 2017 (v141)
* C++ Language Standard: C++17

Install SFML graphic library package for the project:
via NuGet package manager:
* browse for `sfml_graphics`
* select and install 2.5.1 version

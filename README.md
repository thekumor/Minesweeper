# Minesweeper
Game resembling Minesweeper from Windows XP.

## Background
Minesweeper is a classic Windows XP game. It’s well-known within online culture. Such a game
consists of fields that player needs to uncover. Player must be smart about their decisions,
because a bad move means game is lost due to a bomb exploding.

## Description
Game consists of scenes. First scene a player sees is main menu. They can choose a
difficulty, or they can check out high scores. High scores are sorted by time and contain
information such as time, player’s name, difficulty, date. Each difficulty has different time a
player has left, amount of flags avaiable and amount of bombs. Clicking on a bomb makes
player lose the game, flagging all bombs makes player win the game. When player clicks on
a field, it uncovers itself and some fields around it. Fields that are adjacent to bombs have
number of them written down.

![Screenshot of main menu.](https://github.com/thekumor/Minesweeper/tree/main/images/github/Main menu.png)
![Screenshot of high scores.](https://github.com/thekumor/Minesweeper/tree/main/images/github/High scores.png)
![Screenshot of bombs.](https://github.com/thekumor/Minesweeper/tree/main/images/github/Bombs.png)
![Screenshot of gameplay.](https://github.com/thekumor/Minesweeper/tree/main/images/github/Hard.png)

## Features and Functionalities
Game contains timers, callbacks and a simple database for high scores.

## Software & Hardware Requirements
Insanely low, anyone with potato PC can run it. There’s a caveat though: it only runs under
Windows due to WinAPI being the only system-level API.
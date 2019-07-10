# 42-Wolf3D

![Main](/screenshots/Main.png)

This project was made to learn about 2D raycasting and rendering techniques using [SDL2](https://www.libsdl.org/).

## Install

Works on **macOS Sierra 10.12.6** not sure about portability for other operating systems. This project countains several submodules you must initialize them beforehand :

```shell
$> git clone --recurse-submodules -j3 https://github.com/kibotrel/42-Wolf3D
$> cd 42-Wolf3d && make
```

## Usage
### Run the program

Once the program is compiled, run it with the following command line :
```shell
$> ./wolf3d 'desired map'
```
To get more informations on how the program works and how you can interact with it type :
```shell
$> ./wolf3d
```
### Features
Name | Value | Description | Color on the minimap
:---: | :---: | :---: | :---:
Void | 0 | Cell in which the player can move freely | Black
Wall | 1 | Solid Cell that can't be crossed | White
Teleporter | 2 | Move the player from one cell to another | Green
End | 5 | Exit the labyrinth | Cyan
Spawn | 9 | Origin position for the player | Purple

Every other values are considered as void cells during the parsing process.
### Controls

Keyboard :
* **W / A / S / D** Move the player in the given direction
* **< / >** Rotate camera angle
* **Page_Up / Page_Down** Update the point of view's height
* **P** Pause the process in order to unlock cursor position
* **R** Restore player's position to the spawn cell
* **F** Switch between **windowed** and **fullscreen** mode
* **TAB** Toggle minimap display
* **T** Switch between cell-shaded and textured walls
* **LSHIFT** Turn on sprinting
* **ESC** Close the program

Mouse:
* **Movements** Update camera's angle and camera's height depending on the direction
* **Cursor and left click** resize the window if pause mode is set.  

## Error management

Each following error is handled by the program leading to a complete memory free and program exit :
* Wrong running directory (*ERROR-CODE 1*)
* Wrong map filename (*ERROR-CODE 2*)
* Can't open file (*ERROR-CODE 3*)
* Can't close file (*ERROR-CODE 4*)
* Can't allocate memory (*ERROR-CODE 5*)
* Empty line within the map file (*ERROR-CODE 6*)
* Incorrect map format (*ERROR-CODE 7*)
* Can't retrieve line infos (*ERROR-CODE 8*)
* Uneven width in the map (*ERROR-CODE 9*)
* Empty file (*ERROR-CODE 10*)
* Unbounded map (*ERROR-CODE 11*)
* Unable to connect to SDL API (*ERROR-CODE 12*)
* Can't create window (*ERROR-CODE 13*)
* Can't create SDL renderer (*ERROR-CODE 14*)
* Can't create SDL texture (*ERROR-CODE 15*)
* Can't hide cursor position (*ERROR-CODE 16*)
* Can't update SDL texture (*ERROR-CODE 17*)
* Can't update SDL renderer (*ERROR-CODE 18*)
* No spawnable cell within the map (*ERROR-CODE 19*)
* Wrong teleporter amount (*ERROR-CODE 20*)
* No free cell around teleporter (*ERROR-CODE 21*)

Whenever one of these error occurs, the correct error message is displayed on the **standard output** and the whole program return an error code that you can retrieve by running :
```shell
$> echo $?
```

## Screenshots

![1](/screenshots/01.png)
![0](/screenshots/00.png)
![2](/screenshots/02.png)

## Credits

In collaboration with [@nde-jesu](https://github.com/nde-jesu) and [@reda-con](https://github.com/RemiDC)!

Turn Terror

<details>
<summary><strong>Read in other languages</strong></summary>
<br>

*   [English](README.md)
*   [Русский](README.ru.md)

</details>

![Turn Terror](https://img.shields.io/badge/Version-1.0-blue.svg)
![Roguelike](https://img.shields.io/badge/Genre-Roguelike-orange.svg)
![C](https://img.shields.io/badge/Language-C-green.svg)

**Turn Terror** is a classic roguelike featuring procedurally generated dungeons, a tactical combat system, and permadeath. Play as an adventurer trapped in dangerous caves and try to find the exit while fighting a variety of monsters.

## Game Features

- **Procedural Generation**: Each playthrough is unique thanks to randomly generated caves.
- **Tactical Combat**: A combat system with action selection and a reactive mini-game.
- **Permanent Death**: Losing progress upon death adds thrill to the game.
- **Save System**: Ability to save and load progress via files.

## Installation and Launch

```bash
# Clone the repository
git clone https://github.com/your-username/turn-terror.git

# Build the project
cd turn-terror
make

# Launch the game
./Turn-Terror

# Launch with save capability
./Turn-Terror --save-file filename
```

## Controls

### Basic Controls
- **h** — move left
- **j** — move down
- **k** — move up
- **l** — move right
- **s** — save the game (only when launched with --save-file parameter)
- **d** — load the game
- **q** — quit the game

### Combat System
When approaching an enemy within 2 tiles, combat initiates:
1. Select an action (use k/j keys to navigate the menu):
   - **Attack** — deals damage (costs 5 SP)
   - **Defend** — restores 1 SP
   - **Parry** — reduces the cost of the next attack to 3 SP
2. Press **i** to start the mini-game
3. In the mini-game, press any key when the pointer is in the green zone

## Game World

- **Walls** — `#` (impassable obstacles)
- **Player** — `@` (playable character)
- **Exit** — `^` (game objective)
- **Monsters**:
  - **G** — Goblin (weak enemy)
  - **O** — Orc (medium enemy)
  - **T** — Troll (strong enemy)

## Configuring Controls

To change controls, edit the `src/include/control.h` file and rebuild the project:

```bash
make clean
make
```

## Development

The game is developed in C using cross-platform libraries. Project structure:

```
src/
├── include/    # Header files
├── src/        # Source code
├── Makefile    # Build file
```

**Note**: I welcome any feedback and criticism regarding the code and gameplay.

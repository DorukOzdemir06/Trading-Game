# Trading Game

A text-based console trading simulation game written in C++. You run a shop, negotiate with customers, buy low, and sell high to grow your wealth across multiple in-game days.

---

## Table of Contents

- [Overview](#overview)
- [Gameplay](#gameplay)
- [Features](#features)
- [Project Structure](#project-structure)
- [Data Files](#data-files)
- [How to Build](#how-to-build)
- [How to Play](#how-to-play)
- [Customisation](#customisation)

---

## Overview

Trading Game is a single-player, console-based trading game. You start with a fixed amount of money (determined by difficulty), then spend in-game days accepting or denying buy/sell offers from randomly generated customers. Your goal is to make as much profit as possible before retiring.

---

## Gameplay

Each day lasts **4 minutes** of real time. During that window customers visit your shop one at a time. Each visit is one of two scenarios:

| Scenario | Description |
|----------|-------------|
| **Customer wants to sell** | A customer offers you an item. You can buy it at the offered price and store it in your inventory. |
| **Customer wants to buy** | A customer wants to purchase one of the items you already hold. You can sell it at the offered price. |

At the end of every day you can:
- **Continue** to the next day (`P`)
- **Save & quit** (`Q`) — your progress is written to `data/save_data.txt`
- **Retire** (`R`) — see your final stats and end the run

---

## Features

- **Three difficulty levels** — Easy ($2 000 starting money), Normal ($1 000), Hard ($500)
- **Levelling system** — gain XP by earning money; higher levels give you better price estimates (up to level 10)
- **Dynamic customer AI** — each customer has randomised *richness* and *market knowledge* that influence the price they offer
- **Price estimation** — the game shows you an estimated fair price each turn so you can judge whether a deal is good
- **Save / Load** — save your run at the end of any day and resume later
- **Extensible item list** — add or remove tradeable items simply by editing a text file (no recompile needed)
- **500 named customers** — customers are picked randomly from a pool of 500 unique names for immersion

---

## Project Structure

```
Trading-Game/
├── Trading Game.sln               # Visual Studio solution file
└── ConsoleApplication1/
    ├── ConsoleApplication1.vcxproj
    ├── ConsoleApplication1.vcxproj.filters
    ├── game.cpp                   # All game logic (single source file)
    └── data/
        ├── items.txt              # Tradeable items and their price multipliers
        ├── names.txt              # Pool of 500 customer names
        ├── held_items.txt         # Your current inventory (runtime file)
        └── save_data.txt          # Save file (created on save, deleted on new game)
```

---

## Data Files

### `data/items.txt`

Each line defines one tradeable item in the format `Name:multiplier`.  
The multiplier is an integer that scales the item's base price (`price = multiplier × 50 + gain / 3`).

```
Smart watch:3
Phone:4
Diamond:6
Notebook:1
Computer:4
```

### `data/names.txt`

One customer name per line. The game picks a random line each time a customer appears.

### `data/held_items.txt`

Automatically managed by the game. Stores items you currently own in the format `Name:multiplier-purchase_price`.

### `data/save_data.txt`

Automatically created when you save. Stores: money, player name, difficulty, total gain, total earned, and current day.

---

## How to Build

The project targets **Windows** (uses `\` path separators and the MSVC runtime).

**Requirements**
- Visual Studio 2017 or later (with the *Desktop development with C++* workload), **or**
- Any C++11-capable compiler on Windows (e.g. MinGW/g++)

**Visual Studio**

1. Open `Trading Game.sln`.
2. Select *Release* or *Debug* configuration.
3. Press **Ctrl + Shift + B** to build.
4. Run the resulting executable from inside the `ConsoleApplication1/` folder so that the relative `data\` paths resolve correctly.

**Command line (MinGW example)**

```bash
cd ConsoleApplication1
g++ -std=c++11 -o TradingGame game.cpp
TradingGame.exe
```

> **Important:** the executable must be run from the `ConsoleApplication1/` directory so it can find the `data\` folder.

---

## How to Play

```
<----------- Welcome to the game ------------->
 | 1-) Start new game (deletes old saved data)|
 | 2-) Resume game                            |
 | 3-) Delete saved data                      |
 | 4-) Close the game                         |
<--------------------------------------------->
```

1. **Start a new game** — enter your name and pick a difficulty.
2. Each turn a customer appears with an offer. The game shows:
   - The customer's name
   - The item and price they offer
   - Your *estimated fair price* (improves as you level up)
3. Enter your action:
   | Key | Action |
   |-----|--------|
   | `A` | Accept the offer |
   | `D` | Deny the offer |
   | `E` | End the day early |
4. At the end of a day choose `P` (continue), `Q` (save & quit), or `R` (retire).

---

## Customisation

You can customise the game **without recompiling** by editing the data files:

- **Add an item** — append a line to `data/items.txt` in the format `ItemName:multiplier` (multiplier is a positive integer; higher = more expensive).
- **Remove an item** — delete the corresponding line from `data/items.txt`.
- **Add customer names** — append names (one per line) to `data/names.txt`.

---

## License

See [LICENSE](LICENSE) for details.

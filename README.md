# Advanced Tic-Tac-Toe with Minimax AI

A sophisticated implementation of Tic-Tac-Toe featuring an intelligent AI opponent powered by the Minimax algorithm with alpha-beta pruning. This project demonstrates advanced game theory concepts and AI decision-making in a classic strategy game.

## Table of Contents
- [Features](#features)
- [Technologies Used](#technologies-used)
- [Minimax Algorithm](##minimax-algorithm-with-alpha-beta-pruning)
- [Getting Started](#getting-started)
- [How to Play](#how-to-play)
- [Game Rules](#game-rules)

## Features

### Core Gameplay
- **Variable Board Sizes**: Play on boards from 3x3 to 10x10
- **Flexible Win Conditions**: 3-in-a-row for smaller boards (3x3, 4x4), 5-in-a-row for larger boards
- **Two Game Modes**: 
  - Player vs Player
  - Player vs AI Computer
- **Dynamic Turn Order**: Random selection of who goes first
- **Visual Board Display**: Clear grid layout with coordinates
- **Win Pattern Visualization**: Final board display showing the winning combination

### Advanced AI Features
- **Minimax Algorithm**: Optimal decision-making through game tree search
- **Alpha-Beta Pruning**: Enhanced performance by eliminating irrelevant branches
- **Adaptive Depth Control**: Intelligent depth limiting based on board size
- **Strategic Move Selection**: AI considers winning, blocking, and positioning
- **Randomized Optimal Moves**: When multiple best moves exist, random selection prevents predictability

### Robust Game Logic
- **Input Validation**: Prevents invalid moves and coordinates
- **Collision Detection**: Handles occupied squares gracefully
- **Draw Detection**: Automatic detection of tie games
- **Error Handling**: User-friendly error messages

## Technologies Used

### Primary Language
- **C++**: Modern C++ implementation with STL containers and algorithms

### Key Libraries
- `<vector>`: Dynamic 2D board representation
- `<algorithm>`: Minimax algorithm implementation
- `<ctime>`: Random number generation for move selection
- `<iostream>`: User interface and game display

### Core Algorithms

#### **Minimax Algorithm with Alpha-Beta Pruning**
The heart of this project is the implementation of the Minimax algorithm, a decision-making algorithm used in game theory and artificial intelligence.

**How it works:**
1. **Game Tree Exploration**: The algorithm explores all possible future game states
2. **Recursive Evaluation**: Each position is evaluated recursively to determine its value
3. **Optimal Move Selection**: The AI chooses moves that maximize its winning potential while minimizing the opponent's chances
4. **Alpha-Beta Pruning**: Significantly reduces computation time by eliminating branches that won't affect the final decision

**Implementation Details:**
- **Depth-Limited Search**: Prevents excessive computation on larger boards
- **Position Evaluation**: +100000 for AI wins, -100000 for human wins, 0 for draws/neutral
- **Pruning Optimization**: Alpha-beta bounds eliminate up to 50% of search space

#### **Adaptive Depth Strategy**
The AI uses different search depths based on board complexity:

- **3x3 boards**: Depth 9 (near-perfect play)
- **4x4 boards**: Depth 6 (strong strategic play)
- **5x5-6x6 boards**: Depth 4 (good tactical awareness)
- **7x7+ boards**: Depth 3 (efficient strategic play)

#### **Smart Move Generation**
The `possibleMoves()` function implements intelligent move prioritization:

1. **Neighbor Priority**: Prioritizes moves adjacent to existing pieces
2. **Full Board Fallback**: If no adjacent moves exist, considers all empty squares
3. **Strategic Positioning**: Focuses search on relevant board areas

## Getting Started

### Prerequisites
- C++ compiler (GCC, Clang, or MSVC)
- Terminal/Command Prompt access

### Installation & Compilation

```bash
# Clone the repository
git clone https://github.com/yourusername/advanced-tictactoe.git

# Navigate to project directory
cd advanced-tictactoe

# Compile the program
g++ tictactoe.cpp -o tictactoe

# Run the game
./tictactoe

```

## How to Play

### **Game Setup**
- **Choose Board Size:** Select any size from **3×3** up to **10×10**.
- **Select Game Mode:**
  - `0` — Player vs Player  
  - `1` — Player vs AI
- **Enter Player Name(s):** Personalize your gameplay.
- **Random Assignment:**  
  Signs (**X** / **O**) and turn order are randomly generated each game.

---

### Making Moves
When prompted, enter:
- **Row:** `0` to `board_size - 1`
- **Column:** `0` to `board_size - 1`

The game will:
- Validate your input  
- Inform you of errors  
- Forfeit your turn if the move is invalid (with explanation)

---

## Game Rules

### **Board Sizes & Win Conditions**
| Board Size | Win Condition | AI Difficulty |
|-----------:|---------------|----------------|
| 3×3        | 3 in a row    | Expert         |
| 4×4        | 3 in a row    | Expert         |
| 5×5–6×6    | 5 in a row    | Advanced       |
| 7×7–10×10  | 5 in a row    | Intermediate   |

---

## Move Validation
- Coordinates must be **within board boundaries**
- Selected square must be **empty**
- Invalid moves **forfeit the turn**
- Clear error messages guide the player

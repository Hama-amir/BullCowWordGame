# Bull Cow Word Game

A word guessing game built with Unreal Engine and C++. Players must guess isographic words (words with no repeating letters) and receive feedback in the form of Bulls and Cows.

## Game Rules

- Player must guess an isographic word (no repeating letters)
- Each guess provides feedback in the form of Bulls and Cows:
  - **Bulls**: Letters that are in the correct position
  - **Cows**: Letters that exist in the word but are in the wrong position
- Players have limited lives (2 × word length)
- Players can ask for hints using 'h' command (maximum 2 hints)
- Each hint costs 2 lives

## Technical Features

- Built using Unreal Engine and C++
- Uses terminal-style interface for input/output
- Features include:
  - Random word selection from a curated list
  - Input validation
  - Hint system
  - Bulls and Cows calculation
  - Life management system

## Code Structure

- **[`BullCowCartridge.h`](Source/BullCowGame/BullCowCartridge.h)**: Main game logic header
- **[`BullCowCartridge.cpp`](Source/BullCowGame/BullCowCartridge.cpp)**: Game implementation
- **[`HiddenWordList.h`](Source/BullCowGame/HiddenWordList.h)**: Word database
- **[`Terminal.h`](Source/BullCowGame/Console/Terminal.h)**: Terminal interface header
- **[`Terminal.cpp`](Source/BullCowGame/Console/Terminal.cpp)**: Terminal implementation

## Example Gameplay

```
Welcome to the Bull Cows Game!
Guess the 5 letter word!
You Have 10 lives.
Type in your guess and press enter to continue...

> STARE
Sorry, that is the wrong word, try again.
You have 9 lives left
You have 2 Bulls and 1 Cows

> h
You have asked for a Hint,
The 1 letter is: P
You have lost 2 lives for that hint
You now have 7 Lives
```

## Installation

1. Clone the repository
2. Open the project in Unreal Engine
3. Build and run the game

## Development

This game was developed using:
- Unreal Engine
- C++ programming language
- Visual Studio Code
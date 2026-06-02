# GameLand

A three-level terminal game written in C++. Each level is a different puzzle — beat all three to win.

---

## How to Run

```bash
g++ -o gameland "Full Game.cpp"
./gameland
```

---

## Levels

**Level 1 — Unscramble the Word**
The guard shows you 5 scrambled letters. Each letter is secretly mapped to its mirror in the alphabet (A↔Z, B↔Y, etc). Figure out the pattern and type the correct answer to pass.

**Level 2 — Crack the Code**
A secret 3-digit code is generated. You have 10 guesses. After each guess you get a hint:
- 🟢 Green — right digit, right position
- 🟠 Orange — right digit, wrong position
- 🔴 Red — wrong digit

**Level 3 — Find the Pearls**
Three pearls are hidden on a 60×15 grid. You have 16 moves to find them. Each move tells you the distance to the nearest pearl — use it to close in.

---

## Concepts Used

- Arrays (1D and 2D)
- Functions and modular design
- Random number generation
- STL: `<algorithm>`, `<string>`, `<cmath>`
- Input validation and game loops

---

## Author

Ranjan Budhathoki — first semester C++ project

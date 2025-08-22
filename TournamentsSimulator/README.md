# Football Tournament Simulator

This project implements a **Football Tournament System** in C, based on **Queues, Stacks, and Linked Lists**.  
The program determines both the **Champion** and the **Real Runner-up** of a knockout-style tournament.

---

## 📌 Features
- Teams are stored in a **Queue** for each round.
- Losers of each match are stored in a **Stack**.
- Final results are stored in a **Linked List**.
- Handles multiple test cases in a single run.
- Supports automatic qualification if the number of teams is odd in a round.
- Determines:
  - **Champion** (winner of the main tournament).
  - **Real Runner-up** (best among all teams that lost to the champion, using a secondary tournament).

---

## 📥 Input Format
- Each test case is given on a single line:
  ```
  n id1 id2 ... idn
  ```
  - `n` → number of teams (2 ≤ n < 10000)  
  - `id` → unique integer ID of each team (−10000 < id < 10000)  

- Program keeps asking the user to enter info for different tournies, untill the user types:
  ```
  -9999
  ```
- Then the simulator terminates and displays the final tournaments results.

### Example Input
```
5 4 3 6 9 2
6 10 80 30 20 15 25
-9999
```

---

## 📤 Output Format
After entering each tournament info the program will simulate the tournament round by round, then in the end For each input case, the program prints the **real runner-up team ID** and the **Champion ID**.

### Example Output
```
||============== FINAL RESULTS ==============||
TournamentNumber    Real-Runner-Up    Champion
        1               4               3
        2               20              15
||===========================================||
```

---

## ⚙️ How It Works
1. Teams are enqueued at the start of each round.  
2. Matches are played according to the rules:
   - **Odd rounds** → team with smaller ID wins.  
   - **Even rounds** → team with larger ID wins.  
3. If an odd number of teams exists in a round, the last team automatically qualifies.  
4. When the champion is determined:
   - All teams that lost to the champion are pushed into a stack.
   - These teams are then reversed into a queue for a **runner-up tournament**.
   - The winner of this secondary tournament is the **real runner-up**.

---

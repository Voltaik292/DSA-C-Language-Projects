# District & Town Information System

This project implements a **District and Town Information Management System** in C Language, using **AVL Trees** and **Hash Tables**.  
The system reads information about districts and their towns, maintains them efficiently, and provides multiple operations for insertion, deletion, search, and updates.

---

## 📌 Features

### AVL Tree Operations
- Load districts and towns from `districts.txt` and build an **AVL Tree**.
- Insert a new town with its population, elevation, and municipality status.
- Search for a town and update its information (population, elevation, municipality).
- List all towns in alphabetical order.
- List all towns with population greater than a given number.
- List all towns that have municipalities (or not).
- Delete a town from the tree.
- Save all towns and their information into `towns.txt`.

### Hash Table Operations
- Build a **Hash Table** using data from `towns.txt`.
- Print the entire hash table (including empty spots).
- Print the table size and load factor.
- Insert a new town into the hash table.
- Search for a specific town and report collisions (if any).
- Delete a town from the hash table.
- Save updated hash table back to `towns.txt`.

---

## 📥 Input Format
The input file `districts.txt` has the following format:

```
district:town:population:elevation:HasMunicipality
```

### Example Input
```
AlQuds:Hezma:5000:550:yes
Nablus:Asira:8000:350:yes
AlQuds:Qatanna:3000:300:No
Jenin:Yabda:12000:200:yes
```

---

## 📤 Output
- Intermediate results displayed to the screen.
- Final town information stored in `towns.txt`.

---

## ⚙️ How It Works
1. Load data from `districts.txt` into an AVL Tree.
2. Perform user operations (insert, search, update, delete, list).
3. Save final AVL Tree results into `towns.txt`.
4. Load `towns.txt` into a Hash Table.
5. Perform operations on the Hash Table (insert, search, collisions, delete).
6. Save updated Hash Table back to `towns.txt`.

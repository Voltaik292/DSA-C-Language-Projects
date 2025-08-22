/*!/////////////////////////////////////////!*/
/*! Name: Abdulrahman Orwah Fahmi Sawalmeh. !*/
/*!            StudentId: 1221574.          !*/
/*!               Section: 1.               !*/
/*!/////////////////////////////////////////!*/


//! Libraries.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// in case the compiler on windows doesn't recognize strcasecmp.
/*
#ifdef _WIN32
#define strcasecmp _stricmp
#endif
*/

//! Defining some constants for better code readability.
#define MAX_LINE_SIZE 1024
#define DELETED 2
#define OCCUPIED 1
#define EMPTY 0

//! A struct for holding town data.
struct TownData {
    bool hasMunicipality;
    char townDistrict[50];
    char townName[50];
    int population;
    int elevation;
};
//! A avl tree node struct.
struct TownNode {
    struct TownData town_data;
    struct TownNode* Right;
    struct TownNode* Left;
    int height;
};
//! A hash cell struct to make an array of hash cells.
struct TownField {
    struct TownData town_info;
    int field_status;
};

//! Setting some global variables to simplify passing data.
int towns_found = 0;
int hash_table_size;
int double_hashing_load;
struct TownField* HASH_TABLE;

//! defining another name for two structs just for better readability.
typedef struct TownField* HashTable;
typedef struct TownNode* AVL;

//! AVL functions.
int Height(AVL T);
int getHeight(AVL T);
int Max(int a, int b);
int BalanceFactor(AVL T);
AVL makeEmpty(AVL T);
AVL findMin(AVL T);
AVL findMax(AVL T);
AVL avl_find(struct TownData tData, AVL T);
AVL user_find_update(AVL T);
AVL avl_insert(struct TownData tData, AVL T);
AVL avl_delete(char* tName, AVL T);
AVL SR_Rotate(AVL T);
AVL SL_Rotate(AVL T);
AVL DLR_Rotate(AVL T);
AVL DRL_Rotate(AVL T);
AVL loadFileData(AVL T);
AVL avl_user_insert(AVL T);
AVL avl_user_delete(AVL T);
void HprintInOrder(AVL T);
void printInOrder(AVL T);
void printAboveNumber(int n, AVL T);
void HprintAboveNumber(AVL T);
void HprintHaveMunicipalities(AVL T);
void printHaveMunicipalities(bool hasMunicipalities, AVL T);
void print_avl_to_file(FILE* output, AVL T);
void Hprint_avl_to_file(AVL T);

//! Double Hash functions.
bool isPrime(int n);
int nextPrime(int n);
int previousPrime(int n);
int string_hash_value(char* key);
int h1_function(int x);
int h2_function(int x, int i);
int hash_function(char* key, int i);
HashTable insert_into_hash_table(HashTable HT, struct TownData tData);
HashTable user_insert_into_hash_table(HashTable HT);
HashTable loadTownsIntoHashTable(HashTable HT);
HashTable initialize_hash_table(HashTable HT);
HashTable hash_delete(HashTable HT, char* tName);
HashTable user_hash_delete(HashTable HT);
HashTable rehash(HashTable HT);
bool search(HashTable HT);
void upload_hash_table_data(HashTable HT);
void print_hash_table(HashTable HT);
void printLoadFactor();
void displayMainMenu();
float get_load_factor();


int main(void) {
    printf("||================= Districts/Cities Information Manager =================||\n");
    system("color 04");
    printf("\nInitiallizing a hash table with an initial size = 7...\n");
    printf("Making an empty AVL tree...\n");

    //! initiallizing the data structures used in the project.
    AVL TOWNS_TREE = NULL;
    HASH_TABLE = NULL;
    hash_table_size = 7;
    HASH_TABLE = loadTownsIntoHashTable(HASH_TABLE);

    //! flags to control the flow of the program.
    bool program_status = true;
    bool file_read_status = false;

    //! program infinite loop.
    while (program_status == true) {
        int operation;
        printf("\nEnter the operation number: \n");
        displayMainMenu();
        scanf("%d", &operation);
        printf("\n");

        switch (operation) {
        case 1:
            if (file_read_status == false) {
                TOWNS_TREE = loadFileData(TOWNS_TREE);
                file_read_status = true;
            }
            else {
                printf("The file data has already been uploaded to the AVL tree!\n");
            }
            break;

        case 2:
            TOWNS_TREE = avl_user_insert(TOWNS_TREE);

            break;

        case 3:
            TOWNS_TREE = user_find_update(TOWNS_TREE);
            break;

        case 4:
            HprintInOrder(TOWNS_TREE);
            break;

        case 5:
            HprintAboveNumber(TOWNS_TREE);
            break;

        case 6:
            HprintHaveMunicipalities(TOWNS_TREE);
            break;
        case 7:
            TOWNS_TREE = avl_user_delete(TOWNS_TREE);
            break;

        case 8:
            Hprint_avl_to_file(TOWNS_TREE);
            printf("data uploaded succussfully !");
            break;
        case 9:
            print_hash_table(HASH_TABLE);
            break;

        case 10:
            printLoadFactor();
            break;

        case 11:
            HASH_TABLE = user_insert_into_hash_table(HASH_TABLE);
            break;

        case 12:
            search(HASH_TABLE);
            break;

        case 13:
            HASH_TABLE = user_hash_delete(HASH_TABLE);
            break;

        case 14:
            upload_hash_table_data(HASH_TABLE);
            printf("Data uploaded successfully!\n");
            break;
        case 15:
            free(HASH_TABLE);
            hash_table_size = 7;
            double_hashing_load = 0;
            HASH_TABLE = NULL;
            HASH_TABLE = loadTownsIntoHashTable(HASH_TABLE);
            printf("Data loaded successfully!\n");
            break;
        case 16:
            printf("Freeing heap-allocated memory...\n");
            free(HASH_TABLE);
            makeEmpty(TOWNS_TREE);
            printf("Thank you for using my program\n");
            program_status = false;
            break;
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
    return 0;
}

//! Displays main menu.
void displayMainMenu() {
    printf("1. Read districts.txt file and create the tree.\n");
    printf("2. Insert a new town with all it's associated information.\n");
    printf("3. Find a town and update it's information(optional).\n");
    printf("4. List the towns in the tree in alphabetical order with their associated information.\n");
    printf("5. List all towns that have population greater than an input number.\n");
    printf("6. List all towns that have municipalities or not.\n");
    printf("7. Delete a town from the tree.\n");
    printf("8. Save all information to a file called towns.txt.\n");
    printf("9. Print the hashed table.\n");
    printf("10. Print the size of the hash table and the load factor.\n");
    printf("11. Insert a new record into the hash table.\n");
    printf("12. Search for a specific town and print the number of collisions to reach the town.\n");
    printf("13. Delete a specific record from the hash table.\n");
    printf("14. Save the data back to the file towns.txt.\n");
    printf("15. Empty the hash table and load the towns.txt file into it.\n");
    printf("16. Exit.\n");
}
//! Loads districts.txt file data into the avl tree.
AVL loadFileData(AVL T) {
    FILE* input = fopen("districts.txt", "r");
    if (input == NULL) {
        printf("Failed to open the folder !!\n");
        return NULL;
    }
    char line[MAX_LINE_SIZE] = "";
    while (fgets(line, MAX_LINE_SIZE, input)) {
        struct TownData tx = { false, "", "", 0, -1 };

        char* splitter = strtok(line, ":");
        strcpy(tx.townDistrict, splitter);

        splitter = strtok(NULL, ":");
        strcpy(tx.townName, splitter);

        splitter = strtok(NULL, ":");
        tx.population = atoi(splitter);

        splitter = strtok(NULL, ":");
        tx.elevation = atoi(splitter);

        splitter = strtok(NULL, "\n");
        if (strcasecmp(splitter, "yes") == 0) {
            tx.hasMunicipality = 1;
        }
        else {
            tx.hasMunicipality = 0;
        }
        T = avl_insert(tx, T);
    }
    fclose(input);
    printf("File read succussfully !\n");
    return T;
}

int Height(AVL T) {
    return  (T == NULL) ? -1 : T->height;
}

int getHeight(AVL T) {
    return Max(Height(T->Left), Height(T->Right)) + 1;
}

int Max(int a, int b) {
    return  a > b ? a : b;
}
//! Calculates the balance factor for a tree node.
int BalanceFactor(AVL T) {
    return  (T == NULL) ? -2 : Height(T->Left) - Height(T->Right);
}

AVL makeEmpty(AVL T) {
    if (T != NULL) {
        makeEmpty(T->Left);
        makeEmpty(T->Right);
        free(T);
    }
    return NULL;
}

AVL findMin(AVL T) {
    if (T == NULL) {
        return NULL;
    }
    else if (T->Left == NULL) {
        return  T;
    }
    else {
        return findMin(T->Left);
    }
}

AVL findMax(AVL T) {
    while (T != NULL) {
        if (T->Right == NULL) {
            return T;
        }
        T = T->Right;
    }
    return NULL;
}

AVL avl_find(struct TownData tData, AVL T) {
    if (T == NULL) {
    }
    else if (strcasecmp(tData.townName, T->town_data.townName) < 0) {
        return  avl_find(tData, T->Left);
    }
    else if (strcasecmp(tData.townName, T->town_data.townName) > 0) {
        return  avl_find(tData, T->Right);
    }
    return T;
}

AVL SR_Rotate(AVL T) {
    AVL newRoot = T->Left;
    T->Left = newRoot->Right;
    newRoot->Right = T;

    T->height = getHeight(T);
    newRoot->height = getHeight(newRoot);
    return  newRoot;
}

AVL SL_Rotate(AVL T) {
    AVL newRoot = T->Right;
    T->Right = newRoot->Left;
    newRoot->Left = T;

    T->height = getHeight(T);
    newRoot->height = getHeight(newRoot);
    return newRoot;
}

AVL DLR_Rotate(AVL T) {
    T->Left = SL_Rotate(T->Left);
    return SR_Rotate(T);
}

AVL DRL_Rotate(AVL T) {
    T->Right = SR_Rotate(T->Right);
    return SL_Rotate(T);
}
//! inserts a value into the avl tree
AVL avl_insert(struct TownData tData, AVL T) {
    if (T == NULL) {
        T = (AVL)malloc(sizeof(struct TownNode));
        if (T == NULL) {
            printf("Failed to allocate memory for the new town !\n");
            return NULL;
        }
        T->Right = T->Left = NULL;
        T->height = 0;
        T->town_data.elevation = tData.elevation;
        T->town_data.population = tData.population;
        T->town_data.hasMunicipality = tData.hasMunicipality;
        strcpy(T->town_data.townDistrict, tData.townDistrict);
        strcpy(T->town_data.townName, tData.townName);
    }
    else if (strcasecmp(tData.townName, T->town_data.townName) < 0) {
        T->Left = avl_insert(tData, T->Left);
        if (BalanceFactor(T) == 2) {
            if (strcasecmp(tData.townName, T->Left->town_data.townName) < 0) {
                T = SR_Rotate(T);
            }
            else {
                T = DLR_Rotate(T);
            }
        }
    }
    else if (strcasecmp(tData.townName, T->town_data.townName) > 0) {
        T->Right = avl_insert(tData, T->Right);
        if (BalanceFactor(T) == -2) {
            if (strcasecmp(tData.townName, T->Right->town_data.townName) > 0) {
                T = SL_Rotate(T);
            }
            else {
                T = DRL_Rotate(T);
            }
        }
    }
    T->height = getHeight(T);
    return T;
}
//! deletes a value from the avl tree.
AVL avl_delete(char* tName, AVL T) {
    if (T == NULL) {
        printf("The town the you are trying to delete Does not exist in the tree !");
    }
    else if (strcasecmp(tName, T->town_data.townName) < 0) {
        T->Left = avl_delete(tName, T->Left);
        if (BalanceFactor(T) == -2) {
            if (BalanceFactor(T->Right) == -1) {
                T = SL_Rotate(T);
            }
            else if (BalanceFactor(T->Right) == 1) {
                T = DRL_Rotate(T);
            }
            else if (BalanceFactor(T->Right) == 0) {
                T = SL_Rotate(T);
            }
        }
    }
    else if (strcasecmp(tName, T->town_data.townName) > 0) {
        T->Right = avl_delete(tName, T->Right);
        if (BalanceFactor(T) == 2) {
            if (BalanceFactor(T->Left) == 1) {
                T = SR_Rotate(T);
            }
            else if (BalanceFactor(T->Left) == -1) {
                T = DLR_Rotate(T);
            }
            else if (BalanceFactor(T->Left) == 0) {
                T = SR_Rotate(T);
            }
        }
    }
    else {
        AVL tempCell;
        if (T->Right && T->Left) {
            tempCell = findMin(T->Right);
            T->town_data = tempCell->town_data;
            T->Right = avl_delete(tempCell->town_data.townName, T->Right);
        }
        else if (T->Right) {
            tempCell = T;
            T = T->Right;
            free(tempCell);
        }
        else {
            tempCell = T;
            T = T->Left;
            free(tempCell);
        }
    }
    if (T != NULL) {
        T->height = getHeight(T);
    }
    return  T;
}
//! wrapper/helper function.
void HprintInOrder(AVL T) {
    printInOrder(T);
    if (towns_found == 0) {
        printf("The tree is empty !");
    }
    towns_found = 0;
}
//! print the tree data alphabitaclly.
void printInOrder(AVL T) {
    if (T != NULL) {

        printInOrder(T->Left);
        towns_found++;
        if (T->town_data.hasMunicipality == true) {
            printf("%s:%s:%d:%d:yes\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
        }
        else {
            printf("%s:%s:%d:%d:no\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
        }

        printInOrder(T->Right);
    }
}
//! wrapper function.
AVL avl_user_insert(AVL T) {
    struct TownData tx;
    printf("Enter the Town District Name: ");
    scanf("%s", &(tx.townDistrict));

    printf("Enter the Town Name: ");
    scanf("%s", &(tx.townName));
    if (avl_find(tx, T) != NULL) {
        printf("A town with the same name already exist in the tree!\n");
        return T;
    }

    while (true) {
        printf("Enter the town population: ");
        scanf("%d", &(tx.population));

        if (tx.population < 0) {
            printf("Error: Population cannot be negative.Please enter a valid population.\n");
        }
        else {
            break;
        }

    }

    printf("Enter the town elevation: ");
    scanf("%d", &(tx.elevation));

    int value = -1;
    while (true) {
        printf("Enter (1) if the town has a Municipality and (0) if it doesn't: ");
        scanf("%d", &value);
        if (value != 0 && value != 1) {
            printf("Please make sure you only enter (1 or 0)!\n");
        }
        else {
            break;
        }
    }
    if (value) {
        tx.hasMunicipality = true;
    }
    else {
        tx.hasMunicipality = false;
    }
    T = avl_insert(tx, T);
    printf("Town inserted successfully !\n");
    return T;
}
//! finds and updates a town in the tree.
AVL user_find_update(AVL T) {
    struct TownData tx;
    printf("Enter the name of the town that you are looking for: ");
    scanf("%s", &(tx.townName));
    if (avl_find(tx, T) == NULL) {
        printf("Town not found !!\n");
    }
    else {
        printf("Town found !!\n");

        int answer;
        while (true) {
            printf("Do you want to update the town data ? (1 if yes, 0 if no): ");
            scanf("%d", &answer);
            if (answer != 1 && answer != 0) {
                printf("Please make sure you only enter (1 or 0)!\n");
            }
            else {
                break;
            }
        }
        if (answer) {
            AVL nodeUnderUpdate = avl_find(tx, T);
            while (true) {
                printf("Enter the updated town population: ");
                scanf("%d", &(tx.population));

                if (tx.population < 0) {
                    printf("Error: Population cannot be negative.Please enter a valid population.\n");
                }
                else {
                    break;
                }
            }

            printf("Enter the town elevation: ");
            scanf("%d", &(tx.elevation));

            int value = -1;
            while (true) {
                printf("Enter (1) if the town still has a Municipality and (0) if it doesn't: ");
                scanf("%d", &value);
                if (value != 0 && value != 1) {
                    printf("Please make sure you only enter (1 or 0)!\n");
                }
                else {
                    break;
                }
            }
            if (value) {
                tx.hasMunicipality = true;
            }
            else {
                tx.hasMunicipality = false;
            }
            nodeUnderUpdate->town_data.population = tx.population;
            nodeUnderUpdate->town_data.elevation = tx.elevation;
            nodeUnderUpdate->town_data.hasMunicipality = tx.hasMunicipality;
            printf("Town data updated successfully !\n");
        }
        else {
            printf("Why did you waste my time if ur not going to update the town data....\n");
        }
    }
    return T;
}
//! wrapper function.
void HprintAboveNumber(AVL T) {
    int pop_floor = 0;
    while (true) {
        printf("Enter the population floor limit: ");
        scanf("%d", &pop_floor);
        if (pop_floor < 0) {
            printf("Please enter a valid population number!\n");
        }
        else {
            break;
        }
    }
    printAboveNumber(pop_floor, T);
    if (towns_found == 0) {
        printf("No towns were found with population greater than %d !!\n", pop_floor);
    }
    else {
        printf("\nTowns printed successfully !\n");
        printf("%d Towns were found with population Greater than %d !\n", towns_found, pop_floor);
    }
    towns_found = 0;
}
//! prints the towns in the tree with population above a user given number.
void printAboveNumber(int n, AVL T) {
    if (T != NULL) {

        printAboveNumber(n, T->Left);
        if (T->town_data.population > n) {
            towns_found++;
            if (T->town_data.hasMunicipality == true) {
                printf("%s:%s:%d:%d:yes\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
            }
            else {
                printf("%s:%s:%d:%d:no\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
            }
        }

        printAboveNumber(n, T->Right);
    }
}
//! wrapper function.
void HprintHaveMunicipalities(AVL T) {
    int print_status = -1;
    while (true) {
        printf("Enter 0 if you want to print towns with no Municipalities and 1 if you want to print towns with Municipalities: ");
        scanf("%d", &print_status);
        if (print_status != 0 && print_status != 1) {
            printf("Please make sure you enter only (1 or 0)!\n");
        }
        else {
            break;
        }

    }
    bool hasMunicipalities = (print_status == 1) ? true : false;
    printHaveMunicipalities(hasMunicipalities, T);
    if (towns_found == 0) {
        if (hasMunicipalities == true) {
            printf("No towns were found with Active Municipalities !\n");
        }
        else {
            printf("No towns were found with no Municipalities !\n");
        }
    }
    else {
        printf("\nTowns printed successfully !\n");
        if (hasMunicipalities == true) {
            printf("%d Towns were found with active Municipalities !\n", towns_found);
        }
        else {
            printf("%d Towns were found with no Municipalities !\n", towns_found);
        }
    }
    towns_found = 0;
}
//!  to print the nodes that have or doesn't have municipalities.
void printHaveMunicipalities(bool hasMunicipalities, AVL T) {
    if (T != NULL) {

        printHaveMunicipalities(hasMunicipalities, T->Left);
        if (T->town_data.hasMunicipality == hasMunicipalities) {
            towns_found++;
            if (T->town_data.hasMunicipality == true) {
                printf("%s:%s:%d:%d:yes\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
            }
            else {
                printf("%s:%s:%d:%d:no\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
            }
        }

        printHaveMunicipalities(hasMunicipalities, T->Right);
    }
}
//! wrapper function.
AVL avl_user_delete(AVL T) {
    struct TownData tx;
    printf("Enter the name of the town that you want to delete: ");
    scanf("%s", &(tx.townName));
    if (avl_find(tx, T) != NULL) {
        printf("Town deleted succussfully !\n");
    }
    return avl_delete(tx.townName, T);
}
//! prints the avl data to a file.
void print_avl_to_file(FILE* output, AVL T) {
    if (T != NULL) {

        print_avl_to_file(output, T->Left);

        if (T->town_data.hasMunicipality == true) {
            fprintf(output, "%s:%s:%d:%d:yes\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
        }
        else {
            fprintf(output, "%s:%s:%d:%d:no\n", T->town_data.townDistrict, T->town_data.townName, T->town_data.population, T->town_data.elevation);
        }

        print_avl_to_file(output, T->Right);
    }
}
//! helper function.
void Hprint_avl_to_file(AVL T) {
    FILE* output = fopen("towns.txt", "w");
    print_avl_to_file(output, T);
    fclose(output);
}

bool isPrime(int n) {
    if (n <= 1) {
        return false;
    }
    for (int i = 2; i < n; i++) {
        if (n % i == 0) {
            return false;
        }
    }
    return true;
}

int nextPrime(int n) {
    int nextPrime = n + 1;
    while (true) {
        if (isPrime(nextPrime)) {
            return nextPrime;
        }
        nextPrime++;
    }
}

int previousPrime(int n) {
    if (n == 3) {
        return 2;  // Special case for n == 3
    }
    if (n <= 2) {
        return -1;  // No prime exists less than 2
    }
    for (int i = n - 1; i > 1; i--) {
        if (isPrime(i)) {
            return i;
        }
    }
    return -1;  // If no prime is found (although this is unlikely)
}

int string_hash_value(char* key) {
    int string_hash_value = 0;
    char* lower_key = strdup(key);
    strlwr(lower_key);

    for (int i = 0; (i < 5) && (*lower_key != '\0'); i++) {
        string_hash_value = (string_hash_value << 5) + *lower_key;
        lower_key++;
    }
    return string_hash_value;
}
//! first hash function.
int h1_function(int x) {
    return x % hash_table_size;
}
//! second hash function.
int h2_function(int x, int i) {
    int R = previousPrime(hash_table_size);
    return (R - (x % R));
}
//! double hash function h = (h1 + i*h2) % tableSize.
int hash_function(char* key, int i) {
    int x = string_hash_value(key);
    int h1 = h1_function(x);
    int h2 = h2_function(x, i);
    int hash_index = (h1 + (i * h2)) % hash_table_size;
    return hash_index;
}

void printLoadFactor() {
    float load_factor = (float)double_hashing_load / (float)hash_table_size;
    printf("The size of the hash table is: %d\n", hash_table_size);
    printf("Load factor = number of occupied cell / Table size");
    printf("= (%d / %d) = %f", double_hashing_load, hash_table_size, load_factor);
}
//! initializes the hash table with empty cells.
HashTable initialize_hash_table(HashTable HT) {
    HT = (HashTable)malloc(sizeof(struct TownField) * hash_table_size);
    for (int i = 0; i < hash_table_size; i++) {
        HT[i].field_status = EMPTY;
    }
    return HT;
}
//! inserts data into the hash table.
HashTable insert_into_hash_table(HashTable HT, struct TownData tData) {
    if (get_load_factor() >= 0.65) {
        printf("load factor = %f ( LF >= 0.65)\n", get_load_factor());
        printf("Rehashing...\n");
        HT = rehash(HT);
        printf("The new table size is %d, with (LF = %f)\n", hash_table_size, get_load_factor());

    }
    for (int i = 0; i < hash_table_size; i++) {
        int h = hash_function(tData.townName, i);
        if ((HT[h].field_status == EMPTY) || (HT[h].field_status == DELETED)) {
            HT[h].town_info = tData;
            HT[h].field_status = OCCUPIED;
            double_hashing_load++;
            return HT;
        }
    }
    return HT;

}
//! prints the hash table.
void print_hash_table(HashTable HT) {
    for (int i = 0; i < hash_table_size; i++) {
        if (HT[i].field_status != OCCUPIED) {
            printf("%d\t ______\n", i);
        }
        else {
            printf("%d\t %s\n", i, HT[i].town_info.townName);
        }
    }
}
//! loads the towns.txt file data into the hash table.
HashTable loadTownsIntoHashTable(HashTable HT) {
    FILE* input = fopen("towns.txt", "r");
    HT = initialize_hash_table(NULL);
    if (input == NULL) {
        printf("Failed to open the folder !!\n");
        return NULL;
    }
    char line[MAX_LINE_SIZE] = "";
    while (fgets(line, MAX_LINE_SIZE, input)) {
        struct TownData tx = { false, "", "", 0, -1 };
        if (line[0] == '\n') {
            continue;
        }
        char* splitter = strtok(line, ":");
        strcpy(tx.townDistrict, splitter);

        splitter = strtok(NULL, ":");
        strcpy(tx.townName, splitter);

        splitter = strtok(NULL, ":");
        tx.population = atoi(splitter);

        splitter = strtok(NULL, ":");
        tx.elevation = atoi(splitter);

        splitter = strtok(NULL, "\n");
        if (strcasecmp(splitter, "yes") == 0) {
            tx.hasMunicipality = 1;
        }
        else {
            tx.hasMunicipality = 0;
        }
        HT = insert_into_hash_table(HT, tx);
    }
    fclose(input);
    return HT;
}
//! searrches for an element into the hash table.
bool search(HashTable HT) {
    int number_of_collisions = 0;
    char tName[50] = "";
    printf("Enter the name of the town you are looking for: ");
    scanf("%s", &tName);
    for (int i = 0; i < hash_table_size; i++) {
        int h = hash_function(tName, i);
        if (HT[h].field_status == EMPTY) {
            return false;
        }
        else if (HT[h].field_status == OCCUPIED && strcasecmp(HT[h].town_info.townName, tName) != 0) {
            number_of_collisions++;
            continue;
        }
        else if (HT[h].field_status == DELETED) {
            number_of_collisions++;
            continue;
        }
        else if (HT[h].field_status == OCCUPIED && strcasecmp(HT[h].town_info.townName, tName) == 0) {
            printf("The town was found at index: %d, with total number of collisions = %d", h, number_of_collisions);
            return true;
        }
    }
    printf("The town you are looking for doesn't exist in the hash table!\n");
}
//! wrapper function.
HashTable user_insert_into_hash_table(HashTable HT) {
    struct TownData tx;
    printf("Enter the Town District Name: ");
    scanf("%s", &(tx.townDistrict));

    printf("Enter the Town Name: ");
    scanf("%s", &(tx.townName));

    while (true) {
        printf("Enter the town population: ");
        scanf("%d", &(tx.population));
        if (tx.population < 0) {
            printf("Please enter a valid population number !\n");
        }
        else {
            break;
        }
    }

    printf("Enter the town elevation: ");
    scanf("%d", &(tx.elevation));

    int value = -1;
    while (true) {
        printf("Enter (1) if the town has a Municipality and (0) if it doesn't: ");
        scanf("%d", &value);
        if (value != 0 && value != 1) {
            printf("The value must be (1 or 0) !\n");
        }
        else {
            break;
        }
    }
    if (value) {
        tx.hasMunicipality = true;
    }
    else {
        tx.hasMunicipality = false;
    }
    HT = insert_into_hash_table(HT, tx);
    printf("Town inserted successfully !\n");
    return HT;
}
//! deletes data from the hash table.
HashTable hash_delete(HashTable HT, char* tName) {
    for (int i = 0; i < hash_table_size; i++) {
        int h = hash_function(tName, i);
        if (HT[h].field_status == OCCUPIED && strcasecmp(HT[h].town_info.townName, tName) == 0) {
            HT[h].field_status = DELETED;
            double_hashing_load--;
            printf("town deleted successfully!\n");
            return HT;
        }
        else if (HT[h].field_status == OCCUPIED && strcasecmp(HT[h].town_info.townName, tName) != 0) {
            continue;
        }
        else if (HT[h].field_status == DELETED) {
            continue;
        }
        else if (HT[h].field_status == EMPTY) {
            return HT;
        }
    }
    return HT;
}
//! wrapper function.
HashTable user_hash_delete(HashTable HT) {
    printf("Enter the name of the town that you want to delete: ");
    char tName[50] = "";
    scanf("%s", &tName);
    HT = hash_delete(HT, tName);
    return HT;
}
//! uploads the hash table data to a file named towns.txt.
void upload_hash_table_data(HashTable HT) {
    FILE* output = fopen("towns.txt", "w");
    for (int i = 0; i < hash_table_size; i++) {
        if (HT[i].field_status == OCCUPIED) {
            if (HT[i].town_info.hasMunicipality == true) {
                fprintf(output, "%s:%s:%d:%d:yes\n", HT[i].town_info.townDistrict, HT[i].town_info.townName, HT[i].town_info.population, HT[i].town_info.elevation);
            }
            else {
                fprintf(output, "%s:%s:%d:%d:no\n", HT[i].town_info.townDistrict, HT[i].town_info.townName, HT[i].town_info.population, HT[i].town_info.elevation);
            }
        }
    }
    fclose(output);
}
//! rehashes the hash table when needed (LF >= 0.65).
HashTable rehash(HashTable HT) {
    int old_table_size = hash_table_size;
    int new_table_size = nextPrime(2 * hash_table_size);
    hash_table_size = new_table_size;
    HashTable HT2 = initialize_hash_table(NULL);
    double_hashing_load = 0;

    for (int i = 0; i < old_table_size; i++) {
        if (HT[i].field_status == OCCUPIED) {
            insert_into_hash_table(HT2, HT[i].town_info);
        }
    }

    free(HT);
    return HT2;
}
//! calculates the current load factor.
float get_load_factor() {
    float load_factor = (float)double_hashing_load / (float)hash_table_size;
    return load_factor;
}

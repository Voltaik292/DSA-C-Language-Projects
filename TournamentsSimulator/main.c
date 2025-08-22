/*!/////////////////////////////////////////!*/
/*! Name: Abdulrahman Orwah Fahmi Sawalmeh. !*/
/*!            StudentId: 1221574.          !*/
/*!               Section: 1.               !*/
/*!/////////////////////////////////////////!*/


//! Libraries.
#include <stdio.h>
#include <stdlib.h>


//! Defining some constants for better code readability.
#define TOURNAMENTS_TERMENATION_CODE -9999
#define MAX_NUMBER_OF_TEAMS 10000
#define MIN_NUMBER_OF_TEAMS 1
#define MIN_ID -10000
#define MAX_ID 10000
#define TRUE 1
#define FALSE 0


//! Linked list struct for storing final results.
struct TournyResults {
    int Champion;
    int RunnerUp;
};
struct LNode {
    struct LNode* next;
    struct TournyResults finalResults;
};

//! Queue struct for storing teams in Queue.
struct Queue {
    int number_of_teams;
    int round_number;
    struct QNode* front;
    struct QNode* rear;
};
struct QNode {
    int id;
    struct QNode* next;
};

//! Stack struct to store losing teams.
struct Stack {
    struct SNode* top;
    int number_of_teams;
};
struct SNode {
    int eliminated_id;
    int eliminator_id;
    struct SNode* next;
};


//! New definitions for better code readability.
typedef struct Queue* Queue;
typedef struct QNode* QNode;
typedef struct Stack* Stack;
typedef struct SNode* SNode;
typedef struct LNode* List;
typedef struct LNode* LNode;
typedef int bool;


//! Global variables/ list.
bool TERMINATE_ALL_TOURNAMENTS;     // A flag to know when to end all the tournaments.
int numberOfTournaments;            // A variable to track the number Of Tournaments.
List finalResults;                  // A list to store each tournament final result.


//! Main Tournaments Function.
void initiate_all_tournaments(Queue Q, Stack losers_stack);

//! Tournament Organizing functions.
void initiate_single_full_tournament(Queue Q, Stack losers_stack);
void insertResults(List L, struct TournyResults TR);
void enter_single_tournament_data(Queue Q);

//! Basic stack operations.
void push(Stack S, int winner_team_id, int loser_team_id);
int pop(Stack S);

//! Basic Queue Operations.
void enqueue(Queue Q, int team_id);
int dequeue(Queue Q);

//! Functions to make Empty Data structures.
Queue makeEmptyQueue(Queue Q);
Stack makeEmptyStack(Stack S);
List makeEmptyList(List L);

//! Helper Functions.
bool is_new_team(Queue Q, int new_team_id);
bool is_even(int n);
void printFinalResults(List L);
void printQueue(Queue Q);


//! Main function.
int main() {
    system("color 06");
    printf("||========== Tournaments Simulator ==========||\n");

    //! Initializing global variables.
    numberOfTournaments = 0;
    TERMINATE_ALL_TOURNAMENTS = FALSE;
    finalResults = makeEmptyList(NULL);

    //! Initializing losers_stack.
    Stack losers_stack;
    losers_stack = makeEmptyStack(NULL);

    //! Initializing teams Queue.
    Queue teamsQueue;
    teamsQueue = makeEmptyQueue(NULL);

    //! Starting all the tournaments.
    initiate_all_tournaments(teamsQueue, losers_stack);

    //! Freeing all heap allocated memory.
    printf("Freeing all heap allocated memory!\n");
    free(finalResults);
    free(teamsQueue);
    free(losers_stack);

    printf("Thanks for using my tournament simulator Program!\n");
    return 0;
}


void enter_single_tournament_data(Queue Q) {
    int number_of_participating_teams = 0;
    printf("\n||========== Tournament number (%d) ==========||\n\n", numberOfTournaments + 1);
    printf("Enter the number of the participating teams(-9999 to terminate & display results): ");
    scanf("%d", &number_of_participating_teams);
    printf("\n");

    //! Make sure it's not the termination code.
    if (number_of_participating_teams == TOURNAMENTS_TERMENATION_CODE) {
        TERMINATE_ALL_TOURNAMENTS = TRUE;
        return;
    }

    //! Validate the participating teams number.
    while (number_of_participating_teams <= MIN_NUMBER_OF_TEAMS || number_of_participating_teams >= MAX_NUMBER_OF_TEAMS) {
        printf("Please enter a valid number of teams!\n");
        printf("The number of teams should be between %d and %d.\n", MIN_NUMBER_OF_TEAMS, MAX_NUMBER_OF_TEAMS);
        printf("Enter the number of the participating teams: ");
        scanf("%d", &number_of_participating_teams);
    }

    //! Enqueue teams by id after validating them.
    int teams_counter = 0;
    while (teams_counter < number_of_participating_teams) {
        int team_id = -999999;
        printf("Enter the id of the number (%d) participant: ", teams_counter + 1);
        scanf("%d", &team_id);

        while (team_id <= MIN_ID || team_id >= MAX_ID || (is_new_team(Q, team_id) == FALSE)) {
            printf("Please enter a valid id number!\n");
            if ((is_new_team(Q, team_id) == FALSE)) {
                printf("The id number should be distinct!\n");
            }else {
                printf("The id number should be between %d and %d.\n", MIN_ID, MAX_ID);
            }
            printf("Enter the id of the number (%d) participant: ", teams_counter + 1);
            scanf("%d", &team_id);
        }
        enqueue(Q, team_id);
        teams_counter++;
    }
    printf("\n");
    Q->round_number = 1;
}

void printQueue(Queue Q) {
    QNode qPtr = Q->front;
    int i = 0;
    printf("#of Teams: (%d):", Q->number_of_teams);
    while (qPtr != NULL) {
        if (i == 0) {
            printf(" %d", qPtr->id);
            i++;
        }
        else {
            printf(", %d", qPtr->id);
        }
            qPtr = qPtr->next;
    }
}

Queue makeEmptyQueue(Queue Q) {
    Q = (Queue)malloc(sizeof(struct Queue));
    if (Q == NULL) {
        printf("Failed to allocate memory !\n");
        return NULL;
    }
    Q->front = NULL;
    Q->rear = NULL;
    Q->number_of_teams = 0;
    Q->round_number = 0;
    return Q;
}

void enqueue(Queue Q, int team_id) {
    QNode newNode = (QNode)malloc(sizeof(struct QNode));
    if (Q->rear != NULL) {
        Q->rear->next = newNode;
    }
    else {
        Q->front = newNode;
    }

    newNode->next = NULL;
    Q->rear = newNode;
    Q->number_of_teams++;
    newNode->id = team_id;
}

int dequeue(Queue Q) {
    int x = -777777;
    if (Q->rear == NULL) {
        return -7777777;
    }
    else if (Q->number_of_teams == 1) {
        x = Q->front->id;
        QNode temp = Q->front;
        free(temp);
        Q->rear = NULL;
        Q->front = NULL;
        Q->number_of_teams--;
    }
    else {
        x = Q->front->id;
        QNode temp = Q->front;
        Q->front = temp->next;
        free(temp);
        Q->number_of_teams--;
    }
    return x;
}

Stack makeEmptyStack(Stack S) {
    S = (Stack)malloc(sizeof(struct Stack));
    if (S == NULL) {
        printf("Failed to allocate memory!\n");
        return NULL;
    }
    S->number_of_teams = 0;
    S->top = NULL;
}

bool is_new_team(Queue Q, int new_team_id) {
    QNode ptr = Q->front;
    while (ptr != NULL) {
        if (ptr->id == new_team_id) {
            return FALSE; // If the team ID is found, it's not a new team.
        }
        ptr = ptr->next; // Move to the next node in the queue.
    }
    return TRUE; // If the loop completes, the team is unique.
}

void push(Stack S, int winner_team_id, int loser_team_id) {
    SNode newNode = (SNode)malloc(sizeof(struct SNode));
    SNode temp = S->top;
    S->top = newNode;
    S->number_of_teams++;
    newNode->next = temp;
    newNode->eliminated_id = loser_team_id;
    newNode->eliminator_id = winner_team_id;
}

int pop(Stack S) {
    int x = -777777;
    if (S->number_of_teams == 0) {
        return x;
    }
    else {
        SNode temp = S->top;
        x = temp->eliminated_id;
        S->top = temp->next;
        S->number_of_teams--;
        free(temp);
        return x;
    }
}

List makeEmptyList(List L) {
    L = (List)malloc(sizeof(struct LNode));
    if (L == NULL) {
        printf("Out of space !\n");
        return NULL;
    }
    L->next = NULL;
    L->finalResults.Champion = -9999999;
    L->finalResults.RunnerUp = -9999999;
    return L;
}

void printFinalResults(List L) {
    LNode Lptr = L->next;
    if (numberOfTournaments == 0) {
        printf("No tournaments were played!!");
        return;
    }
    printf("\n");
    printf("||============== FINAL RESULTS ==============||\n");
    printf("TournamentNumber    Real-Runner-Up    Champion\n");
    for (int i = 0; i < numberOfTournaments; i++) {
        printf("\t%d\t\t%d\t\t%d\n", i + 1, Lptr->finalResults.RunnerUp, Lptr->finalResults.Champion);
        Lptr = Lptr->next;
    }
    printf("||===========================================||\n");
    printf("\n");

}

void insertResults(List L, struct TournyResults TR) {
    LNode Lptr = L;
    while (Lptr->next != NULL) {
        Lptr = Lptr->next;
    }
    LNode newNode = (LNode)malloc(sizeof(struct LNode));
    Lptr->next = newNode;
    newNode->next = NULL;
    newNode->finalResults.Champion = TR.Champion;
    newNode->finalResults.RunnerUp = TR.RunnerUp;
    numberOfTournaments++;
}

bool is_even(int n) {
    return (n % 2) == 0;
}

void initiate_single_full_tournament(Queue Q, Stack losers_stack) {
    printQueue(Q);
    printf("\t(Main tournament)\n");
    //! Dequeue the top 2 elements and compare them according to the project given algorithm.
    while (Q->number_of_teams != 1) {
        int number_of_matches = Q->number_of_teams / 2;
        while (number_of_matches != 0) {

            int t1_id = dequeue(Q);
            int t2_id = dequeue(Q);
            int winner;
            int loser;
            if (!is_even(Q->round_number)) {
                if (t1_id < t2_id) {
                    winner = t1_id;
                    loser = t2_id;
                }
                else {
                    winner = t2_id;
                    loser = t1_id;
                }
            }
            else {
                if (t1_id > t2_id) {
                    winner = t1_id;
                    loser = t2_id;
                }
                else {
                    winner = t2_id;
                    loser = t1_id;
                }
            }
            enqueue(Q, winner);
            push(losers_stack, winner, loser);
            number_of_matches--;
        }
        printQueue(Q);
        printf("\t(Round %d results)\n", Q->round_number);
        Q->round_number++;
    }
    struct TournyResults TR1;
    TR1.Champion = losers_stack->top->eliminator_id;
    TR1.RunnerUp = losers_stack->top->eliminated_id;

    dequeue(Q);

    Q->front = NULL;
    Q->rear = NULL;
    Q->round_number = 1;

    while (losers_stack->top != NULL) {

        if (losers_stack->top->eliminator_id == TR1.Champion) {
            enqueue(Q, pop(losers_stack));
        }
        else {
            pop(losers_stack);
        }
    }
    //! If only one team is left in the Queue don't start the second tourney.
    if (Q->number_of_teams == 1) {
        insertResults(finalResults, TR1);
        while(losers_stack->top != NULL) {
            pop(losers_stack);
        }
        return;
    }

    printf("\n");
    printQueue(Q);
    printf("\t(Secondary Tournament)\n");
    //! Initialize the second tournament.
    while (Q->number_of_teams != 1) {
        int number_of_matches = Q->number_of_teams / 2;
        while (number_of_matches != 0) {

            int t1_id = dequeue(Q);
            int t2_id = dequeue(Q);
            int winner;
            int loser;
            if (!is_even(Q->round_number)) {
                if (t1_id < t2_id) {
                    winner = t1_id;
                    loser = t2_id;
                }
                else {
                    winner = t2_id;
                    loser = t1_id;
                }
            }
            else {
                if (t1_id > t2_id) {
                    winner = t1_id;
                    loser = t2_id;
                }
                else {
                    winner = t2_id;
                    loser = t1_id;
                }
            }
            enqueue(Q, winner);
            push(losers_stack, winner, loser);
            number_of_matches--;

        }
        printQueue(Q);
        printf("\t(Round %d results)\n", Q->round_number);
        Q->round_number++;
    }
    //! Insert both the winners of the main and secondary tournament into the final results list.
    struct TournyResults TR2;
    TR2.Champion = losers_stack->top->eliminator_id;
    TR2.RunnerUp = losers_stack->top->eliminated_id;
    struct TournyResults TR = { TR1.Champion, TR2.Champion };
    insertResults(finalResults, TR);
    dequeue(Q);
}

void initiate_all_tournaments(Queue Q, Stack losers_stack) {
    //! While the program is running keep processing the tournaments and getting the results.
    while (TRUE) {
        enter_single_tournament_data(Q);
        //! If the user entered the termenation code into the number of teams, terminated the program and display the results.
        if (TERMINATE_ALL_TOURNAMENTS == TRUE) {
            printFinalResults(finalResults);
            return;
        }
        initiate_single_full_tournament(Q, losers_stack);
            while (losers_stack->top != NULL) {
                pop(losers_stack);
            }
    }
}

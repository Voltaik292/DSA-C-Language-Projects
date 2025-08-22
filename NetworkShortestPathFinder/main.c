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
#include <limits.h>

//! in case the compiler on windows doesn't recognize strcasecmp.
/*
#ifdef _WIN32
#define strcasecmp _stricmp
#endif
*/

//! Defining some constants for better code readability.
#define MAX_LINE_LENGTH 1024
#define MAX_ROUTER_NAME_LENGTH 15
#define MAX_NUM_OF_ROUTERS 100
#define CONNECTED true
#define DISCONNECTED false
#define INFINITE INT_MAX

//! A struct for each cell in the adjacency matrix.
struct MatrixCell {
    int latency;
    bool connection_status;
};
//! A struct for DJK and BFS algorithms arrays.
struct BFS_DJK_array {
    char router_name[MAX_ROUTER_NAME_LENGTH];
    int cost_to_node;
    bool is_known;
    char parent[MAX_ROUTER_NAME_LENGTH];
};
//! A struct for every single cell in the minheap queue.
struct HeapCell {
    char router_name[MAX_ROUTER_NAME_LENGTH];
    int distance;
};
//! A struct for the min Heap.
struct MinHeap {
    int size;
    int max_size;
    struct HeapCell* heap_array;
};
//! A struct to hold the single queue node data.
struct qData {
    char router_name[MAX_ROUTER_NAME_LENGTH];
    int latency;
};
//! A struct for BFS queue.
struct Queue {
    struct Queue* next;
    struct qData data;
    struct Queue* tail;
};


typedef struct BFS_DJK_array BFS_array;
typedef struct BFS_DJK_array DJK_array;

//! Setting some global variables to simplify passing data.
int number_of_network_routers = 0;
struct MatrixCell** adjacency_matrix;
DJK_array* DJK_ARRAY;
BFS_array* BFS_ARRAY;
char** network_routers;


bool router_in_network(char* rName);
void initialize_adjacency_matrix();
void loadNetworkInfo();
void print_network_routers();
void displayMainMenu();
void print_adjacency_matrix();
void initialize_DJK_array();
char** calculate_number_of_routers();
char* get_router_name(int index);
int get_router_index(char* router_name);
void free_network_routers();
void free_adjacency_matrix();

//! DJK MinHeap functions.
struct MinHeap* initialize_min_heap_array();
struct MinHeap* insert_into_heap(struct MinHeap* H, int latency, char* rName);
struct MinHeap* swap(struct MinHeap* H, int p1, int p2);
struct MinHeap* minHeapify(struct MinHeap* H, int position);
int isLeaf(struct MinHeap* H, int pos);
struct HeapCell extract_min(struct MinHeap* H);

//! BFS Queue functions.
struct Queue* makeEmptyQueue(struct Queue* Q);
void enqueue(struct Queue* Q, char* router_name, int latency);
struct Queue* dequeue(struct Queue* Q);

//! BFS and DJK functions.
void initialize_BFS_array();
int BFS(char* src, char* dst, struct Queue* BFS_Q);
int DJK(char* src, char* dst, struct MinHeap* H);
void print_BFS_path(char* dst);
void print_DJK_path(char* dst);
void file_print_BFS_path(FILE* output, char* dst);
void file_print_DJK_path(FILE* output, char* dst);
void print_BFS();
void print_DJK();

int main()
{
    printf("||=========== Network Path Finder ===========||\n");
    system("color 0c");

    //! Some flags to control the flow of the program.
    bool program_status = true;
    bool file_read_status = false;
    bool source_read = false;
    bool path_indentified = false;

    //! BFS queue and DJK heap.
    struct Queue* BFS_QUEUE = makeEmptyQueue(NULL);
    struct MinHeap* DJK_HEAP = NULL;

    char src_router[MAX_ROUTER_NAME_LENGTH] = "";
    char dst_router[MAX_ROUTER_NAME_LENGTH] = "";

    int BFS_CPY = 0;
    int DJK_CPY = 0;

    //! Main program loop.
    while (program_status == true) {
        int operation;
        printf("\nEnter the operation number: \n");
        displayMainMenu();
        scanf("%d", &operation);
        printf("\n");

        switch (operation) {
        case 1:
            if (file_read_status == false) {
                network_routers = calculate_number_of_routers();
                initialize_adjacency_matrix();
                DJK_HEAP = initialize_min_heap_array(DJK_HEAP);
                loadNetworkInfo();
                printf("You have %d routers in the network.\n", number_of_network_routers);
                print_network_routers();
                file_read_status = true;
            }
            else {
                printf("You have already loaded the file info into a graph network!\n");
                printf("You have %d routers in the network.\n", number_of_network_routers);
                print_network_routers();
            }
            break;
        case 2:
            while (true) {
                printf("Enter the name of the source router: ");
                scanf("%s", src_router);
                if (router_in_network(src_router) == true) {
                    printf("Source located successfully !\n");
                    source_read = true;
                    break;
                }
                printf("Please enter a valid network router name!\n");
                printf("The network routers are:\n");
                print_network_routers();
            }

            break;
        case 3:
            if (source_read == false) {
                printf("Please enter the source router first!\n");
            }
            else {
                while (true) {
                    printf("Enter the name of the destination router: ");
                    scanf("%s", dst_router);
                    if (router_in_network(dst_router) == true) {
                        source_read = true;
                        break;
                    }
                    printf("Please enter a valid network router name!\n");
                    printf("The network routers are:\n");
                    print_network_routers();
                }
                int BFS_result = BFS(src_router, dst_router, BFS_QUEUE);
                int DJK_result = DJK(src_router, dst_router, DJK_HEAP);
                BFS_CPY = BFS_result;
                DJK_CPY = DJK_result;
                print_DJK();
                if (DJK_ARRAY[get_router_index(dst_router)].is_known == false) {
                    printf("Dijkstra: Path doesn't exist! total time = INFINITE.\n ");
                }
                else {
                    printf("Dijkstra: ");
                    print_DJK_path(dst_router);
                    printf(" with a total time of %d msec.\n", DJK_result);
                }
                if (BFS_ARRAY[get_router_index(dst_router)].is_known == false) {
                    printf("BFS: Path doesn't exist! total time = INFINITE.\n ");
                }
                else {
                    printf("BFS: ");
                    print_BFS_path(dst_router);
                    printf(" with a total time of %d msec.\n", BFS_result);

                }
                path_indentified = true;
            }
            break;

        case 4:
            printf("Freeing heap-allocated memory...\n");
            if (path_indentified == false) {
                printf("No path was calculated !\n");
                printf("Nothing will be printed to the output file!\n");
            }
            else {
                FILE* output = fopen("shortest_distance.txt", "w");
                if (DJK_ARRAY[get_router_index(dst_router)].is_known == false) {
                    fprintf(output, "Dijkstra: Path doesn't exist! total time = INFINITE.\n ");
                }
                else {
                    fprintf(output, "Dijkstra: ");
                    file_print_DJK_path(output, dst_router);
                    fprintf(output, " with a total time of %d msec.\n", DJK_CPY);
                }
                if (BFS_ARRAY[get_router_index(dst_router)].is_known == false) {
                    fprintf(output, "BFS: Path doesn't exist! total time = INFINITE.\n ");
                }
                else {
                    fprintf(output, "BFS: ");
                    file_print_BFS_path(output, dst_router);
                    fprintf(output, " with a total time of %d msec.\n", BFS_CPY);

                }
                printf("Data printed successfully !\n");
                fclose(output);
            }

            printf("Thank you for using my program!\n");
            program_status = false;
            break;
        default:
            printf("No such operation! Please try again.\n");
        }
    }

    //! Freeing all heap allocated memory.
    free(BFS_QUEUE);
    free(DJK_HEAP);
    free(BFS_ARRAY);
    free(DJK_ARRAY);
    free_network_routers();
    free_adjacency_matrix();
    return 0;
}

//! Caluclates number of network routers.
char** calculate_number_of_routers() {
    FILE* input = fopen("routers.txt", "r");
    if (!input) {
        printf("Error: Failed to open 'routers.txt'.\n");
        return NULL;
    }

    char line[MAX_LINE_LENGTH] = "";
    char** routers_names;
    routers_names = (char**)malloc(sizeof(char*) * MAX_NUM_OF_ROUTERS);
    for (int i = 0; i < MAX_NUM_OF_ROUTERS; i++) {
        routers_names[i] = (char*)malloc(sizeof(char) * MAX_ROUTER_NAME_LENGTH);

    }


    for (int i = 0; i < MAX_NUM_OF_ROUTERS; i++) {
        routers_names[i][0] = '\0';
    }

    while (fgets(line, MAX_LINE_LENGTH, input)) {

        if (line[0] == '\0' || line[0] == '\n') {
            continue;
        }

        char* splitter = strtok(line, "-");

        for (int i = 0; i < MAX_NUM_OF_ROUTERS; i++) {
            if (routers_names[i][0] == '\0') {
                strcpy(routers_names[i], splitter);
                number_of_network_routers++;
                break;
            }
            if (strcasecmp(routers_names[i], splitter) == 0) {
                break;
            }
        }

        splitter = strtok(NULL, "-");

        for (int i = 0; i < MAX_NUM_OF_ROUTERS; i++) {
            if (routers_names[i][0] == '\0') {
                strcpy(routers_names[i], splitter);
                number_of_network_routers++;
                break;
            }
            if (strcasecmp(routers_names[i], splitter) == 0) {
                break;
            }
        }
    }
    fclose(input);
    return routers_names;
}

void initialize_adjacency_matrix() {
    adjacency_matrix = (struct MatrixCell**)malloc(sizeof(struct  MatrixCell*) * number_of_network_routers);
    if (adjacency_matrix == NULL) {
        // Handle malloc failure
        return;
    }
    for (int i = 0; i < number_of_network_routers; i++) {
        adjacency_matrix[i] = (struct MatrixCell*)malloc(sizeof(struct MatrixCell) * number_of_network_routers);
        if (adjacency_matrix[i] == NULL) {
            // Handle malloc failure
            return;
        }
    }
    for (int i = 0; i < number_of_network_routers; i++) {
        for (int j = 0; j < number_of_network_routers; j++) {
            adjacency_matrix[i][j].connection_status = DISCONNECTED;
            adjacency_matrix[i][j].latency = INT_MAX;
        }
    }

}
//! Loads the network info into a graph.
void loadNetworkInfo() {
    FILE* input = fopen("routers.txt", "r");
    if (!input) {
        printf("Error: Failed to open 'routers.txt'.\n");
        return;
    }

    char line[MAX_LINE_LENGTH] = "";

    while (fgets(line, MAX_LINE_LENGTH, input)) {
        char* src_router = NULL;
        char* dst_router = NULL;
        int latency = INT_MAX;

        char* splitter = strtok(line, "-");
        src_router = strdup(splitter);

        splitter = strtok(NULL, "-");
        dst_router = strdup(splitter);

        splitter = strtok(NULL, "\n");
        latency = atoi(splitter);
        if (latency < 0) {
            printf("NEGATIVE NUMBERS DETECTED ALGORITHM WON'T FUNCTION CORRECTLY!\n");
        }

        // printf("ADJ[%d = %s][%d = %s] = %d\n",get_router_index(src_router), src_router,get_router_index(dst_router),dst_router, latency );
        adjacency_matrix[get_router_index(src_router)][get_router_index(dst_router)].latency = latency;
        adjacency_matrix[get_router_index(dst_router)][get_router_index(src_router)].latency = latency;
        adjacency_matrix[get_router_index(src_router)][get_router_index(dst_router)].connection_status = CONNECTED;
        adjacency_matrix[get_router_index(dst_router)][get_router_index(src_router)].connection_status = CONNECTED;

    }
    fclose(input);

}

void print_network_routers() {
    printf("\n");
    for (int i = 0; i < number_of_network_routers; i++) {
        printf("Router[%d]: %s\n", i, network_routers[i]);
    }
}

void print_adjacency_matrix() {


    // Print the header with router names (to show columns)
    printf("Adjacency Matrix (Connection Info):\n\n");
    for (int i = 0; i < number_of_network_routers; i++) {
        for (int j = 0; j < number_of_network_routers; j++) {
            printf("Router[%d][%d]: Connection status: %d, latency: %d\n", i, j, adjacency_matrix[i][j].connection_status, adjacency_matrix[i][j].latency);
        }
    }

}
//! looks for a router in a network.
bool router_in_network(char* rName) {
    for (int i = 0; i < MAX_NUM_OF_ROUTERS; i++) {
        if (strcasecmp(network_routers[i], rName) == 0) {
            return true;
        }
    }
    return false;
}

void displayMainMenu() {
    printf("1- Load Network Routers.\n");
    printf("2- Enter The source Router.\n");
    printf("3- Enter The Destination Router and print shortest path in BFS and DJK.\n");
    printf("4- Exit the program and print results to shortest_distance.txt.\n");
}

int get_router_index(char* router_name) {
    for (int i = 0; i < number_of_network_routers; i++) {
        if (strcasecmp(network_routers[i], router_name) == 0) {
            return i;
        }
    }
    return -1;
}

char* get_router_name(int index) {
    return network_routers[index];
}

struct MinHeap* initialize_min_heap_array(struct MinHeap* H) {
    H = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    H->heap_array = (struct HeapCell*)malloc(sizeof(struct HeapCell) *( number_of_network_routers + 1));

    if (H == NULL) {
        printf("Failed to allocate memory for the min heap struct !\n");
        return NULL;
    }
    if (H->heap_array == NULL) {
        printf("Failed to allocate memory for the heap matrix");
        return H;
    }
    H->size = 0;
    H->max_size = number_of_network_routers + 1;
    H->heap_array[0].router_name[0] = '\0';
    H->heap_array[0].distance = INT_MIN;
    return H;
}

struct MinHeap* swap(struct MinHeap* H, int p1, int p2) {
    int tempLatency = H->heap_array[p1].distance;
    H->heap_array[p1].distance = H->heap_array[p2].distance;
    H->heap_array[p2].distance = H->heap_array[p1].distance;

    char* rName1 = strdup(H->heap_array[p1].router_name);
    char* rName2 = strdup(H->heap_array[p2].router_name);
    strcpy(H->heap_array[p1].router_name, rName2);
    strcpy(H->heap_array[p2].router_name, rName1);

    free(rName1);
    free(rName2);

    return H;
}

struct MinHeap* insert_into_heap(struct MinHeap* H, int latency, char* rName) {
    if (H->size >= H->max_size) {
        printf("The heap is full!");
        return H;
    }
    H->size = H->size + 1;
    H->heap_array[H->size].distance = latency;
    char* rName1 = strdup(rName);
    strcpy(H->heap_array[H->size].router_name, rName1);
    free(rName1);

    int current = H->size;
    while (H->heap_array[current].distance < H->heap_array[current / 2].distance) {
        H = swap(H, current, current / 2);
        current = current / 2;
    }
    return H;
}

int isLeaf(struct MinHeap* H, int pos) {
    if ((pos >= (H->size / 2)) && pos <= H->size) {
        return 1;
    }
    return 0;
}
//! Function to heapify a node at a given position.
struct MinHeap* minHeapify(struct MinHeap* H, int position) {
    if (!isLeaf(H, position)) {
        if (H->heap_array[position].distance > H->heap_array[position * 2].distance || H->heap_array[position].distance > H->heap_array[(position * 2) + 1].distance) {
            if (H->heap_array[position * 2].distance < H->heap_array[(position * 2) + 1].distance) {
                H = swap(H, position, position * 2);
                H = minHeapify(H, position * 2);
            }
            else {
                H = swap(H, position, (position * 2) + 1);
                H = minHeapify(H, (position * 2) + 1);
            }
        }

    }
    return H;
}
//! Function to extract the min cell in the min heap and then heapifying.
struct HeapCell extract_min(struct MinHeap* H) {
    if (H->size <= 0) {
        printf("The heap is empty!\n");
        struct HeapCell emptyCell = {"\0", INT_MAX};
        return emptyCell;
    }

    char* rName = strdup(H->heap_array[1].router_name);

    struct HeapCell minCell;
    strcpy(minCell.router_name, rName);
    minCell.distance = H->heap_array[1].distance;

    H = swap(H, 1, H->size);

    H->size--;

    H = minHeapify(H, 1);

    return minCell;


}

void initialize_DJK_array() {
    if (DJK_ARRAY != NULL) {
        free(DJK_ARRAY);
    }
    DJK_ARRAY = (DJK_array*)malloc(sizeof(DJK_array) * number_of_network_routers);
    for (int i = 0; i < number_of_network_routers; i++) {
        DJK_ARRAY[i].cost_to_node = INFINITE;
        DJK_ARRAY[i].is_known = false;
        DJK_ARRAY[i].parent[0] = '\0';

        char* rName = "";
        rName = strdup(get_router_name(i));
        strcpy(DJK_ARRAY[i].router_name, rName);
    }
}

void initialize_BFS_array() {
    if (BFS_ARRAY != NULL) {
        free(BFS_ARRAY);
    }
    BFS_ARRAY = (BFS_array*)malloc(sizeof(BFS_array) * number_of_network_routers);
    for (int i = 0; i < number_of_network_routers; i++) {
        BFS_ARRAY[i].cost_to_node = INFINITE;
        BFS_ARRAY[i].is_known = false;
        BFS_ARRAY[i].parent[0] = '\0';

        char* rName = "";
        rName = strdup(get_router_name(i));
        strcpy(BFS_ARRAY[i].router_name, rName);
    }
}

struct Queue* makeEmptyQueue(struct Queue* Q) {
    Q = (struct Queue*)malloc(sizeof(struct Queue));
    if (Q == NULL) {
        printf("Failed to allocate memory for the Queue!");
        return NULL;
    }
    Q->next = NULL;
    Q->tail = NULL;
}

void enqueue(struct Queue* Q, char* router_name, int latency) {
    struct Queue* newNode = (struct Queue*)malloc(sizeof(struct Queue));
    if (newNode == NULL) {
        printf("Failed to allocate memory for the new queue node!\n");
        return;
    }
    if (Q->next == NULL) {
        Q->next = newNode;
        Q->tail = newNode;
    }
    else {
        Q->tail->next = newNode;
        Q->tail = newNode;
    }
    newNode->next = NULL;
    newNode->data.latency = latency;
    char* rName = strdup(router_name);
    strcpy(newNode->data.router_name, router_name);
}

struct Queue* dequeue(struct Queue* Q) {
    if (Q->next == NULL) {
        printf("The queue is empty!\n");
        return NULL;
    }
    else {
        struct Queue* temp = Q->next;
        if (Q->next == Q->tail) {
            Q->next = NULL;
            Q->tail = NULL;
        }
        else {
            Q->next = Q->next->next;
        }
        return temp;
    }
}
//! Main BFS function.
int BFS(char* src, char* dst, struct Queue* BFS_Q) {
    initialize_BFS_array();
    BFS_ARRAY[get_router_index(src)].cost_to_node = 0;
    BFS_ARRAY[get_router_index(src)].is_known = true;
    char* rName1 = strdup(src);
    strcpy(BFS_ARRAY[get_router_index(src)].parent, rName1);
    enqueue(BFS_Q, src, 0);

    while (BFS_Q->next != NULL) {
        struct Queue* temp = dequeue(BFS_Q);

        for (int i = 0; i < number_of_network_routers; i++) {
            if (!BFS_ARRAY[i].is_known && (adjacency_matrix[get_router_index(temp->data.router_name)][i].connection_status != DISCONNECTED)) {
                BFS_ARRAY[i].is_known = true;
                BFS_ARRAY[i].cost_to_node = adjacency_matrix[get_router_index(temp->data.router_name)][i].latency + BFS_ARRAY[get_router_index(temp->data.router_name)].cost_to_node;
                char* rName = strdup(temp->data.router_name);
                strcpy(BFS_ARRAY[get_router_index(get_router_name(i))].parent, rName);
                enqueue(BFS_Q, get_router_name(i), BFS_ARRAY[i].cost_to_node);
            }
        }
    }

    return BFS_ARRAY[get_router_index(dst)].cost_to_node;
}
//! Main DJK function.
int DJK(char* src, char* dst, struct MinHeap* H) {
    initialize_DJK_array();
    DJK_ARRAY[get_router_index(src)].cost_to_node = 0;
    char* rName1 = strdup(src);
    strcpy(DJK_ARRAY[get_router_index(src)].parent, rName1);
    H = insert_into_heap(H, 0, src);


    while (H->size != 0) {
        struct HeapCell temp = extract_min(H);
        int u = get_router_index(temp.router_name);
        if (DJK_ARRAY[u].is_known) {
            continue;
        }
        DJK_ARRAY[u].is_known = true;
        for (int i = 0; i < number_of_network_routers; i++) {
            if (adjacency_matrix[u][i].connection_status != DISCONNECTED) {
                int updated_cost =  DJK_ARRAY[u].cost_to_node + adjacency_matrix[u][i].latency;

                if (updated_cost < DJK_ARRAY[i].cost_to_node) {
                    DJK_ARRAY[i].cost_to_node = updated_cost;
                    char* rName = strdup(temp.router_name);
                    strcpy(DJK_ARRAY[i].parent, rName);
                    H = insert_into_heap(H, DJK_ARRAY[i].cost_to_node, get_router_name(i));
                }
            }
        }
    }

    return DJK_ARRAY[get_router_index(dst)].cost_to_node;
}

void print_BFS() {
    for (int i = 0; i < number_of_network_routers; i++) {
        if (BFS_ARRAY[i].is_known == false) {
            printf("%s\tfalse\t%d\t%s\n", BFS_ARRAY[i].router_name, BFS_ARRAY[i].cost_to_node, BFS_ARRAY[i].parent);
        }
        else {
            printf("%s\ttrue\t%d\t%s\n", BFS_ARRAY[i].router_name, BFS_ARRAY[i].cost_to_node, BFS_ARRAY[i].parent);

        }
    }
}

void print_DJK() {
    for (int i = 0; i < number_of_network_routers; i++) {
        if (DJK_ARRAY[i].is_known == false) {
            printf("%s\tfalse\t%d\t%s\n", DJK_ARRAY[i].router_name, DJK_ARRAY[i].cost_to_node, DJK_ARRAY[i].parent);
        }
        else {
            printf("%s\ttrue\t%d\t%s\n", DJK_ARRAY[i].router_name, DJK_ARRAY[i].cost_to_node, DJK_ARRAY[i].parent);

        }
    }
}

void print_BFS_path(char* dst) {
    char tracker[MAX_NUM_OF_ROUTERS][MAX_ROUTER_NAME_LENGTH];
    int routers_passed = 0;
    int current = get_router_index(dst);

    while (strcasecmp(BFS_ARRAY[current].parent, get_router_name(current)) != 0) {
        char* tRName = strdup(get_router_name(current));
        strcpy(tracker[routers_passed], tRName);
        routers_passed++;
        current = get_router_index(BFS_ARRAY[current].parent);
    }
    char* tRName = strdup(get_router_name(current));
    strcpy(tracker[routers_passed], tRName);
    routers_passed++;

    for (int i = routers_passed - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%s", tracker[i]);
        }
        else {
            printf("%s -> ", tracker[i]);
        }

    }
}

void print_DJK_path(char* dst) {
    char tracker[MAX_NUM_OF_ROUTERS][MAX_ROUTER_NAME_LENGTH];
    int routers_passed = 0;
    int current = get_router_index(dst);

    while (strcasecmp(DJK_ARRAY[current].parent, get_router_name(current)) != 0) {
        char* tRName = strdup(get_router_name(current));
        strcpy(tracker[routers_passed], tRName);
        routers_passed++;
        current = get_router_index(DJK_ARRAY[current].parent);
    }
    char* tRName = strdup(get_router_name(current));
    strcpy(tracker[routers_passed], tRName);
    routers_passed++;

    for (int i = routers_passed - 1; i >= 0; i--) {
        if (i == 0) {
            printf("%s", tracker[i]);
        }
        else {
            printf("%s -> ", tracker[i]);
        }

    }
}

void file_print_DJK_path(FILE* output, char* dst) {
    char tracker[MAX_NUM_OF_ROUTERS][MAX_ROUTER_NAME_LENGTH];
    int routers_passed = 0;
    int current = get_router_index(dst);

    while (strcasecmp(DJK_ARRAY[current].parent, get_router_name(current)) != 0) {
        char* tRName = strdup(get_router_name(current));
        strcpy(tracker[routers_passed], tRName);
        routers_passed++;
        current = get_router_index(DJK_ARRAY[current].parent);
    }
    char* tRName = strdup(get_router_name(current));
    strcpy(tracker[routers_passed], tRName);
    routers_passed++;

    for (int i = routers_passed - 1; i >= 0; i--) {
        if (i == 0) {
            fprintf(output, "%s", tracker[i]);
        }
        else {
            fprintf(output, "%s -> ", tracker[i]);
        }

    }
}

void file_print_BFS_path(FILE* output, char* dst) {
    char tracker[MAX_NUM_OF_ROUTERS][MAX_ROUTER_NAME_LENGTH];
    int routers_passed = 0;
    int current = get_router_index(dst);

    while (strcasecmp(DJK_ARRAY[current].parent, get_router_name(current)) != 0) {
        char* tRName = strdup(get_router_name(current));
        strcpy(tracker[routers_passed], tRName);
        routers_passed++;
        current = get_router_index(DJK_ARRAY[current].parent);
    }
    char* tRName = strdup(get_router_name(current));
    strcpy(tracker[routers_passed], tRName);
    routers_passed++;

    for (int i = routers_passed - 1; i >= 0; i--) {
        if (i == 0) {
            fprintf(output, "%s", tracker[i]);
        }
        else {
            fprintf(output, "%s -> ", tracker[i]);
        }

    }
}
//! Function to free heap memory for the routers.
void free_network_routers() {
    if (network_routers == NULL) {
        return;
    }
    for (int i = 0; i < number_of_network_routers; i++) {
        if (network_routers[i] != NULL) {
            free(network_routers[i]);
        }
    }
    free(network_routers);
}
//! Function to free adjacency matrix.
void free_adjacency_matrix() {
    if (adjacency_matrix == NULL) {
        return;
    }
    for (int i = 0; i < number_of_network_routers; i++) {
        if (adjacency_matrix[i] != NULL) {
            free(adjacency_matrix[i]);
        }
    }
    free(adjacency_matrix);
}
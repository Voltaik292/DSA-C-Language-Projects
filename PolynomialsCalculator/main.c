/*!/////////////////////////////////////////!*/
/*! Name: Abdulrahman Orwah Fahmi Sawalmeh. !*/
/*!            StudentId: 1221574.          !*/
/*!               Section: 1.               !*/
/*!/////////////////////////////////////////!*/


//! Libraries.
#include <stdio.h>
#include <stdlib.h>


//! Defining some constants for better code readability.
#define MAX_COEFFICIENT_DIGIT_COUNT 20
#define MAX_EXPONENTIAL_DIGIT_COUNT 10
#define MAX_POLYNOMIAL_SIZE 1024
#define MULTIPLICATION 2
#define SUBTRACTION 0
#define ADDITION 1
#define false 0
#define true 1


//! defining another name for integer just for better readability.
typedef int bool;


//! A struct for holding the term data.
struct TermData {
    int coefficient;
    int exponent;
};

//! Defining the terms node struct (Acts as a Linked-list).
struct TermNode {
    struct TermData termInfo;       // Used to hold the single term data.
    struct TermNode* next_term;     // A pointer to the next term in the same polynomial.
};

//! Defining the Polynomial Node struct (Acts as a Stack which points to the Linked-list that holds the terms of the polynomial).
struct PolyNode {
    int number_of_terms;            // Specifies the number of terms in each polynomial.
    struct TermNode* terms;         // Points to the polynomial terms.
    struct PolyNode* next_poly;     // Points to the next polynomial.
};

//! Defining the Polynomials Stack struct (Simply a wrapper struct for all the polynomials in the same stack).
struct PolyStack {
    int number_of_polynomials;      // Specifies the number of polynomials in the same stack.
    struct PolyNode* Top;           // Specifies the top element in the polynomials.
};


//! Setting some global variables to simplify passing data.
struct PolyStack* resultsStack;         // A Stack pointer which points to the results stack.
struct PolyNode* additionResult;        // A Polynomial pointer which points to the result of adding all the input polynomials.
struct PolyNode* subtractionResult;     // A Polynomial pointer which points to the result of subtracting all the input polynomials.
struct PolyNode* multiplicationResult;  // A Polynomial pointer which points to the result of multiplying all the input polynomials.


//! Functions prototypes(Each function is explained in the function body).
struct PolyStack* copyStack(struct PolyStack* P1, struct PolyStack* P2);
struct PolyStack* makeEmptyStack(struct PolyStack* PolynomialsStack);
struct PolyNode* copyPolynomial(struct PolyNode* poly1, struct PolyNode* Poly2);
struct PolyNode* pop_and_return_poly(struct PolyStack* PolynomialsStack);
void insert_term(struct PolyNode* Polynomial, struct TermNode* term, int co, int exp);
void push(struct PolyStack* PolynomialsStack, struct PolyNode* Polynomial);
void delete_term(struct PolyNode* polynomial, struct TermNode* term);
void print_stack_to_screen(struct PolyStack* PolynomialsStack);
void print_results_to_file(struct PolyStack* PolynomialsStack);
void loadPolynomialsFile(struct PolyStack* PolynomialsStack);
void ALU(struct PolyStack* PolynomialsStack, int OpCode);
void free_polynomial_terms(struct PolyNode* Polynomial);
void process_Polynomial(struct PolyNode* Polynomial);
void printPolynomial(struct PolyNode* polynomial);
void free_stack(struct PolyStack* Stack);
void printFilePolynomials();
void displayMainMenu();
int size_of_string(char* str);
int POWER(int x, int n);
bool is_even(int x);


int main() {
    printf("||=========== Polynomials Calculator ===========||\n");
    system("color 09");

    //!  Initializing program stacks.
    struct PolyStack* PolynomialsStack = makeEmptyStack(NULL);
    resultsStack = makeEmptyStack(resultsStack);

    //! Some flags to control the flow of the program.
    bool operations_status = false;
    bool multiplication_status = false;
    bool subtraction_status = false;
    bool addition_status = false;
    bool file_read_status = false;
    bool program_status = true;
    bool polynomial_more_than_one = false;


    while (program_status == true) {

        int operation;
        printf("\nEnter the operation number: \n");
        displayMainMenu();
        scanf("%d", &operation);
        printf("\n");

        switch (operation) {
        //! loading the polynomials from a file named polynomials.txt
        case 1:
            if (file_read_status == false) {
                loadPolynomialsFile(PolynomialsStack);

                if (PolynomialsStack->number_of_polynomials > 0) {
                    printf("Loading input File....\nFile loaded successfully!\n");
                    file_read_status = true;
                    if (PolynomialsStack->number_of_polynomials > 1) {
                        polynomial_more_than_one = true;
                    }
                    break;
                }
                else {
                    file_read_status = false;
                    break;
                }
            }
            else {
                printf("The file has already been read !! Please select another operation.\n");
                break;
            }
        //! Print the polynomials Stack.
        case 2:
            if (file_read_status == false) {
                printf("What exactly are you trying to print ???\n");
                printf("You haven't loaded the input file yet...");
                printf("The input polynomials are not detected yet!\n");
                printf("Please load the input file first.\n");
            }
            else {
                printf("You have %d Polynomials in the PolynomialsStack:\n", PolynomialsStack->number_of_polynomials);
                print_stack_to_screen(PolynomialsStack);
            }
            break;
        //! Adding the input polynomials.
        case 3:
            if (file_read_status == false) {
                printf("What exactly are you trying to add ???\n");
                printf("You haven't loaded the input file yet...");
                printf("The input polynomials are not detected yet!\n");
                printf("Please load the input file first.\n");
            }
            else if (addition_status == true) {
                printf("You have already added the Polynomials in the polynomials Stack!\n");
                printf("The Addition result is:\n");
                printPolynomial(additionResult);
            }
            else if (polynomial_more_than_one == true){
                    ALU(PolynomialsStack, ADDITION);
                    operations_status = true;
                    addition_status = true;
            }
            else {
                printf("you have %d polynomial in the polynomial stack!!\n", PolynomialsStack->number_of_polynomials);
                printf("Cant do the operation!!\n");
            }
            break;
        //! Subtracting the input polynomials.
        case 4:
            if (file_read_status == false) {
                printf("What exactly are you trying to subtract ???\n");
                printf("You haven't loaded the input file yet...");
                printf("The input polynomials are not detected yet!\n");
                printf("Please load the input file first.\n");
            }
            else if (subtraction_status == true) {
                printf("You have already subtracted the Polynomials in the polynomials Stack!\n");
                printf("The Subtraction result is:\n");
                printPolynomial(subtractionResult);
            }
            else if (polynomial_more_than_one == true){
                ALU(PolynomialsStack, SUBTRACTION);
                operations_status = true;
                subtraction_status = true;
            }
            else {
                printf("you have %d polynomial in the polynomial stack!!\n", PolynomialsStack->number_of_polynomials);
                printf("Cant do the operation!!\n");
            }
            break;
        //! Multiplying the input polynomials.
        case 5:
            if (file_read_status == false) {
                printf("What exactly are you trying to multiply ???\n");
                printf("You haven't loaded the input file yet...");
                printf("The input polynomials are not detected yet!\n");
                printf("Please load the input file first.\n");
            }
            else if (multiplication_status == true) {
                printf("You have already multiplied the Polynomials in the polynomials Stack!\n");
                printf("The Multiplication result is:\n");
                printPolynomial(multiplicationResult);
            }
            else if (polynomial_more_than_one == true){
                ALU(PolynomialsStack, MULTIPLICATION);
                operations_status = true;
                multiplication_status = true;
            }
            else {
                printf("you have %d polynomial in the polynomial stack!!\n", PolynomialsStack->number_of_polynomials);
                printf("Cant do the operation!!\n");
            }

            break;
        //! Printing the results stack.
        case 6:
            if (file_read_status == false) {
                printf("What exactly are you trying to print ???\n");
                printf("You didn't even read the input file!\n");
                printf("Please load the input file first and do some operations to the polynomials.\n");
            }
            else if (operations_status == true){
                printf("You have %d Polynomials in the Results Stack:\n", resultsStack->number_of_polynomials);
                print_stack_to_screen(resultsStack);
            }
            else {
                printf("You haven't done any operations yet, the result stack is empty !\n");
            }
            break;
        //! Printing the results to a file name results.txt
        case 7:
            if (file_read_status == false) {
                printf("What exactly are you trying to print ???\n");
                printf("You didn't even read the input file!\n");
                printf("Please load the input file first and do some operations to the polynomials.\n");
            }
            else if (operations_status == true) {
                printf("Printing the results to a file named \"results.txt\".....\n");
                print_results_to_file(resultsStack);
                printf("Results printed successfully !!\n");
            }
            else {
                printf("You haven't done any operations yet, the result stack is empty !\n");
            }

            break;
        //! Terminating the program after freeing all the allocated memory.
        case 8:
            printf("Freeing heap-allocated memory...\n");
            free_stack(PolynomialsStack);
            printf("Polynomials Stack freed successfully !!\n");
            free_stack(resultsStack);
            printf("Results Stack freed successfully !!\n");;
            printf("Thank you for using my calculator!\n");
            program_status = false;
            break;
        default:
            printf("No such operation! Please try again.\n");
        }
    }

    return 1;
}

//! Simply prints the main menu to the user.
void displayMainMenu() {
    printf("1- Load the polynomials file.\n");
    printf("2- Print the polynomials.\n");
    printf("3- Add the polynomials.\n");
    printf("4- Subtract the polynomials.\n");
    printf("5- Multiply the polynomials.\n");
    printf("6- Print the results to the screen.\n");
    printf("7- Print the results to file.\n");
    printf("8- Exit.\n\n");
}

//! Prints the exact file input without any modification.
void printFilePolynomials() {
    // Declaring a pointer to a file.
    FILE* in;
    // Try to open the file name "polynomials.txt" in read mode.
    in = fopen("polynomials.txt", "r");
    // Check if the file opened successfully.
    if (in == NULL) {
        printf("Failed to open file !");
        return;     // Exit the function if the file opening fails.
    }
    // Declaring a character array to act as a buffer to store each line read from file.
    char line[MAX_POLYNOMIAL_SIZE] = "";

    // Read the file line by line and print it, until the end of the file.
    while (fgets(line, MAX_POLYNOMIAL_SIZE, in)) {
        printf("%s", line);
    }
    fclose(in);
}

//! Makes an empty stack and allocates a location for it in the heap memory.
struct PolyStack* makeEmptyStack(struct PolyStack* P) {
    P = (struct PolyStack*)malloc(sizeof(struct PolyStack));
    // Check if the memory allocation fails.
    if (P == NULL) {
        printf("Failed to allocate memory for the Polynomials stack !\n");
        return NULL;
    }
    // Initializing the stack struct elements.
    P->number_of_polynomials = 0;
    P->Top = NULL;
    return P;
}

//! Copies an entire stack.
struct PolyStack* copyStack(struct PolyStack* P1, struct PolyStack* P2) {

    // Making a temporary stack since we only have access for the first element and we want to copy the original stack in the same order.
    struct PolyStack* tempStack = makeEmptyStack(NULL);
    // New stack to store the copied elements (which will be popped from the temp Stack).
    P2 = makeEmptyStack(NULL);

    // Popping the polynomials from the original stack into a temp stack to prepare them for copying.
    while (P1->number_of_polynomials != 0) {
        struct PolyNode* poppedPoly = pop_and_return_poly(P1);
        poppedPoly->next_poly = tempStack->Top;
        tempStack->Top = poppedPoly;
        tempStack->number_of_polynomials++;
    }
    // Move polynomials from temp stack back into the original stack while also allocating memory and making another copy stack (P2).
    while (tempStack->number_of_polynomials != 0) {
        struct PolyNode* tempPoly = pop_and_return_poly(tempStack);
        struct PolyNode* newPoly = NULL;
        // Creating a new poly to push into the copied stack.
        newPoly = (struct PolyNode*)malloc(sizeof(struct PolyNode));
        push(P2, newPoly);

        // Copying the terms of the most recent popped polynomial in the temp stack.
        struct TermNode* termPtr = tempPoly->terms;
        while (termPtr != NULL) {
            insert_term(newPoly, NULL, termPtr->termInfo.coefficient, termPtr->termInfo.exponent);
            termPtr = termPtr->next_term;
        }

        // Restoring the original stack.
        tempPoly->next_poly = P1->Top;
        P1->Top = tempPoly;
        P1->number_of_polynomials++;
    }
    // Freeing the allocated memory for the temp stack.
    free(tempStack);
    return P2;
}

//! Copies an entire polynomial.
struct PolyNode* copyPolynomial(struct PolyNode* poly1, struct PolyNode* Poly2) {
    // Initialize the second poly.
    Poly2 = (struct PolyNode*)malloc(sizeof(struct PolyNode));
    Poly2->number_of_terms = 0;
    Poly2->next_poly = NULL;
    Poly2->terms = NULL;

    struct TermNode* termPtr = poly1->terms;
    // Copy each term from poly1 to poly2.
    while (termPtr != NULL) {
        insert_term(Poly2, NULL, termPtr->termInfo.coefficient, termPtr->termInfo.exponent);
        termPtr = termPtr->next_term;
    }
    return Poly2;
}

//! Simply returns the length of a given string.
int size_of_string(char* str) {
    int counter = 0;
    // Go through each character in the string while incrementing the counter, until facing the null terminator.
    for (int i = 0; str[i] != '\0'; i++) {
        counter++;
    }
    // return the Counter (length of the string).
    return counter;
}

//! Pushes a new polynomial into a given stack.
void push(struct PolyStack* PolynomialsStack, struct PolyNode* Polynomial) {
    // Link the new polynomial and initialize it's terms.
    Polynomial->next_poly = PolynomialsStack->Top;
    Polynomial->number_of_terms = 0;
    Polynomial->terms = NULL;
    // Update the stack.
    PolynomialsStack->Top = Polynomial;
    (PolynomialsStack->number_of_polynomials)++;
}

//! Inserts a term into a polynomial.
void insert_term(struct PolyNode* Polynomial, struct TermNode* term, int co, int exp) {
    term = (struct TermNode*)malloc(sizeof(struct TermNode));
    term->termInfo.coefficient = co;
    term->termInfo.exponent = exp;

    struct TermNode* last = Polynomial->terms;
    if (last == NULL) {
        Polynomial->terms = term;
    }
    else {
        while (last->next_term != NULL) {
            last = last->next_term;
        }
        last->next_term = term;
    }
    term->next_term = NULL;
    (Polynomial->number_of_terms)++;
}

//! Loads the polynomials from the polynomials file into the polynomials stack.
void loadPolynomialsFile(struct PolyStack* PolynomialsStack) {
    // Opening the polynomials.txt file in read mode.
    FILE* input = fopen("polynomials.txt", "r");
    if (input == NULL) {
        printf("Error occurred while accessing the file !!\n");
        printf("Please make sure the file name is polynomials.txt");
        return;
    }
    // A character array that acts as a buffer which holds the file input line by line.
    char line[MAX_POLYNOMIAL_SIZE] = "";

    // Iterating on the polynomials file line by line while processing them and inserting them in the poly stack.
    while (fgets(line, MAX_POLYNOMIAL_SIZE, input) != NULL) {

        // A flag to check if there is a polynomial in this file or if its just a line with wrong input.
        bool poly_found = false;
        // Check if there is a polynomial in the line.
        for (int i = 0; line[i] != '\0'; i++) {
            if ((line[i] > 47 && line[i] < 58) || (line[i] == 'x') || (line[i] == 'X') || (line[i] == '^') || line[i] == '-' || line[i] == '+') {
                poly_found = true;
                break;
            }
        }
        // if no polynomial is found, continue to the next line.
        if (poly_found == false) {
            continue;
        }
        // if a polynomial is found, allocate memory for it, and push it into the polynomials stack, before adding the line terms to it.
        struct PolyNode* p = NULL;
        p = (struct PolyNode*)malloc(sizeof(struct PolyNode));
        push(PolynomialsStack, p);

        int z = 0;
        int length = size_of_string(line);
        // allocating a temp memory which holds the filtered string (with no spaces and wrong characters), to proccess the line correctly.
        char* filtered_string = (char*)malloc(MAX_POLYNOMIAL_SIZE * sizeof(char));
        char* filtered_string_ptr = filtered_string;

        // Loop into the string character by character, and filter the unwanted/ wrong characters.
        while (z < length) {
            if ((line[z] > 47 && line[z] < 58) || (line[z] == 'x') || (line[z] == 'X') || (line[z] == '^') || line[z] == '-' || line[z] == '+') {
                *filtered_string_ptr = line[z];
                z++;
                filtered_string_ptr++;
                continue;
            }
            z++;
        }
        // Terminate the filtered string with a null terminator to loop on it while processing it.
        *filtered_string_ptr = '\0';
        // Reset the pointer at the beginning of the filtered string to start processing it.
        filtered_string_ptr = filtered_string;

        // Process the filtered string(the polynomial), and insert it into a polynomials stack.
        while (*filtered_string_ptr != '\0') {
            struct TermNode* term = NULL;
            int sign = 1;               // default value for sign (Indicates positive).
            int exponent = 0;           // default value for exponent.
            int coefficient = 1;        // default value for coefficient.

            if (*filtered_string_ptr == '-') {
                sign = 0;
                filtered_string_ptr++;
            }
            if (*filtered_string_ptr == '+') {
                filtered_string_ptr++;
            }
            // <58 && > 47 indicated the ASCII code for the numbers (0-9).
            if ((*filtered_string_ptr) > 47 && (*filtered_string_ptr) < 58) {
                // If we find a digit we make an array which holds all the digits to convert them from strings to integers.
                char coeff_Str[MAX_COEFFICIENT_DIGIT_COUNT] = "";
                int i = 0;

                // Add all the digits into the coeff array while updating the filtered string ptr, until it points to something that is not a digit.
                while ((*filtered_string_ptr) > 47 && (*filtered_string_ptr) < 58) {
                    coeff_Str[i] = *filtered_string_ptr;
                    filtered_string_ptr++;
                    i++;
                }

                int coeff_length = size_of_string(coeff_Str);
                coefficient = 0;
                int power = 0;

                // Convert the string into a integer.
                for (int j = (coeff_length - 1); j >= 0; j--) {
                    int current_digit = coeff_Str[j] - 48;
                    coefficient = coefficient + current_digit * POWER(10, power);
                    power++;
                }
            }
            // Check if there is an exponent.
            if ((*filtered_string_ptr) != 'x' && (*filtered_string_ptr) != 'X') {       // No exponent found (No X).
                if (sign == 1) {
                    insert_term(p, term, coefficient, 0);
                }
                else {
                    insert_term(p, term, -1 * coefficient, 0);
                }
            }
            else {                                                               // Exponent found, could be 1 or more.
                filtered_string_ptr++;
                if ((*filtered_string_ptr) != '^') {                             // Exponent = 1.
                    if (sign == 1) {
                        insert_term(p, term, coefficient, 1);
                    }
                    else {
                        insert_term(p, term, -1 * coefficient, 1);
                    }
                }
                else {                                                           // Exponent more than 1.
                    filtered_string_ptr++;
                    int i = 0;
                    char exp_Str[MAX_EXPONENTIAL_DIGIT_COUNT] = "";             // Do the same processing that you did to the coeff to find the exact exponent.

                    while ((*filtered_string_ptr) > 47 && (*filtered_string_ptr) < 58) {
                        exp_Str[i] = *filtered_string_ptr;
                        filtered_string_ptr++;
                        i++;
                    }
                    int exp_length = size_of_string(exp_Str);
                    int power = 0;
                    exponent = 0;

                    for (int j = (exp_length - 1); j >= 0; j--) {
                        int current_digit = exp_Str[j] - 48;
                        exponent = exponent + current_digit * POWER(10, power);
                        power++;
                    }
                    if (sign == 1) {
                        insert_term(p, term, coefficient, exponent);
                    }
                    else {
                        insert_term(p, term, -1 * coefficient, exponent);
                    }
                }
            }
        }
        free(filtered_string);                      // Free the heap memory that's allocated for the string.
        process_Polynomial(p);                     // Proccess the input.
    }
    fclose(input);                                  // Closing the opened file.
}

//! Prints a single polynomial.
void printPolynomial(struct PolyNode* polynomial) {
    struct TermNode* termPtr = polynomial->terms;
    int termCounter = 1;

    while (termPtr != NULL) {

        if (termPtr->termInfo.exponent == 0) {                      // if the term that you want to print is with 0 exponent.
            if (termCounter == 1) {
                printf("%d", termPtr->termInfo.coefficient);        // exponent = 0, first term.
            }
            else {                                                  // exponent = 0, not the first term.
                if (termPtr->termInfo.coefficient > 0) {
                    printf("+%d", termPtr->termInfo.coefficient);   // exponent = 0, not the first term, coefficient > 0.
                }
                else {
                    printf("%d", termPtr->termInfo.coefficient);    // exponent = 0, not the first term, coefficient < 0.
                }
            }
        }
        else if (termPtr->termInfo.exponent == 1) {                 // if the term that you want to print is with exponent = 1.
            if (termCounter == 1) {                                 // exponent = 1, first term.
                if (termPtr->termInfo.coefficient == 1) {
                    printf("x");                                    // exponent = 1, first term, coefficient = 1.
                }
                else if (termPtr->termInfo.coefficient == -1) {
                    printf("-x");                                   // exponent = 1, first term, coefficient = -1.
                }
                else {
                    printf("%dx", termPtr->termInfo.coefficient);   // exponent = 1, first term, coefficient != (-1 or 1).
                }

            }
            else {
                if (termPtr->termInfo.coefficient > 0) {
                    if (termPtr->termInfo.coefficient == 1) {
                        printf("+x");                               // exponent = 1, not first term, coeff = 1.
                    }
                    else {
                        printf("+%dx", termPtr->termInfo.coefficient);  // exponent = 1, not first term, ceoff > 0.
                    }
                }
                else {
                    if (termPtr->termInfo.coefficient == -1) {
                        printf("-x");                               // exponent = 1, not first term, coeff = -1.
                    }
                    else {
                        printf("%dx", termPtr->termInfo.coefficient);   // exponent = 1, not first term, coeff < 0 && coeff != -1.
                    }
                }
            }
        }
        else {                                                       // if the term that you want to insert is with exponent > 1.
            if (termCounter == 1) {
                if (termPtr->termInfo.coefficient == 1) {
                    printf("x^%d", termPtr->termInfo.exponent);     // exponent > 1, first term, coeff = 1.
                }
                else if (termPtr->termInfo.coefficient == -1) {
                    printf("-x^%d", termPtr->termInfo.exponent);    // exponent > 1, first term, coeff = -1.
                }
                else {
                    printf("%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);    // exponent > 1, first term, coeff != (1 or -1).
                }

            }
            else {
                if (termPtr->termInfo.coefficient > 0) {
                    if (termPtr->termInfo.coefficient == 1) {
                        printf("+x^%d", termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff = 1.
                    }
                    else {
                        printf("+%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);   // exponent > 1, not first term, coeff > 0 && coeff != 1.
                    }
                }
                else {
                    if (termPtr->termInfo.coefficient == -1) {
                        printf("-x^%d", termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff = -1.
                    }
                    else {
                        printf("%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff < 0 && coeff != -1.
                    }
                }
            }
        }
        termPtr = termPtr->next_term;
        termCounter++;
    }
}

//! Prints an entire polynomial stack to the screen.
void print_stack_to_screen(struct PolyStack* PolynomialsStack) {
    if (PolynomialsStack->Top == NULL) {
        printf("The Stack is empty !");
        return;
    }

    struct PolyStack* tempStack = makeEmptyStack(NULL);
    struct PolyNode* ptr = PolynomialsStack->Top;
    printf("Popping all the stack nodes into a temporary stack...\n");
    while (ptr != NULL) {
        PolynomialsStack->Top = ptr->next_poly;
        PolynomialsStack->number_of_polynomials--;

        ptr->next_poly = tempStack->Top;
        tempStack->Top = ptr;
        tempStack->number_of_polynomials++;
        ptr = PolynomialsStack->Top;
    }

    ptr = tempStack->Top;
    int counter = 1;
    printf("Pushing them back into the original stack while printing them 1 by 1(To print them in the order from bottom to Top).\n");
    while (ptr != NULL) {
        printf("%d. ", counter);
        printPolynomial(ptr);
        if (ptr == additionResult) {
            printf("\t(%d terms) (Addition Result).\n", ptr->number_of_terms);

        }
        else if (ptr == subtractionResult) {
            printf("\t(%d terms) (Subtraction Result).\n", ptr->number_of_terms);

        }
        else if (ptr == multiplicationResult) {
            printf("\t(%d terms) (Multiplication Result).\n", ptr->number_of_terms);

        }
        else {
            printf("\t(%d terms).\n", ptr->number_of_terms);
        }
        counter++;

        tempStack->Top = ptr->next_poly;
        tempStack->number_of_polynomials--;

        ptr->next_poly = PolynomialsStack->Top;
        PolynomialsStack->Top = ptr;
        PolynomialsStack->number_of_polynomials++;
        ptr = tempStack->Top;
    }
}

//! Prints the results to a file.
void print_results_to_file(struct PolyStack* PolynomialsStack) {
    // Open a file for writing.
    FILE* output = fopen("results.txt", "w");
    // Check if file opened successfully.
    if (output == NULL) {
        printf("Failed to open file !!\n");
        return;
    }

    if (PolynomialsStack->Top == NULL) {
        printf("The polynomials Stack is empty !");
        return;
    }
    // Making a temp stack; to temporarily hold the polynomials while printing them.
    struct PolyStack* tempStack = makeEmptyStack(NULL);
    struct PolyNode* ptr = PolynomialsStack->Top;
    printf("Popping all the stack nodes into a temporary stack...\n");
    while (ptr != NULL) {
        PolynomialsStack->Top = ptr->next_poly;
        PolynomialsStack->number_of_polynomials--;

        ptr->next_poly = tempStack->Top;
        tempStack->Top = ptr;
        tempStack->number_of_polynomials++;
        ptr = PolynomialsStack->Top;
    }

    ptr = tempStack->Top;
    printf("Pushing them back into the original stack while printing them 1 by 1(To print them in the order from bottom to Top).\n");

    while (ptr != NULL) {
        struct TermNode* termPtr = ptr->terms;
        int termCounter = 1;

        while (termPtr != NULL) {

            if (termPtr->termInfo.exponent == 0) {                      // if the term that you want to print is with 0 exponent.
                if (termCounter == 1) {
                    fprintf(output, "%d", termPtr->termInfo.coefficient);       // exponent = 0, first term.
                }
                else {                                                  // exponent = 0, not the first term.
                    if (termPtr->termInfo.coefficient > 0) {
                        fprintf(output, "+%d", termPtr->termInfo.coefficient);  // exponent = 0, not the first term, coefficient > 0.
                    }
                    else {
                        fprintf(output, "%d", termPtr->termInfo.coefficient);   // exponent = 0, not the first term, coefficient < 0.
                    }
                }
            }
            else if (termPtr->termInfo.exponent == 1) {                 // if the term that you want to print is with exponent = 1.
                if (termCounter == 1) {                                 // exponent = 1, first term.
                    if (termPtr->termInfo.coefficient == 1) {
                        fprintf(output, "x");                                    // exponent = 1, first term, coefficient = 1.
                    }
                    else if (termPtr->termInfo.coefficient == -1) {
                        fprintf(output, "-x");                                   // exponent = 1, first term, coefficient = -1.
                    }
                    else {
                        fprintf(output, "%dx", termPtr->termInfo.coefficient);   // exponent = 1, first term, coefficient != (-1 or 1).
                    }

                }
                else {
                    if (termPtr->termInfo.coefficient > 0) {
                        if (termPtr->termInfo.coefficient == 1) {
                            fprintf(output, "+x");                               // exponent = 1, not first term, coeff = 1.
                        }
                        else {
                            fprintf(output, "+%dx", termPtr->termInfo.coefficient);  // exponent = 1, not first term, ceoff > 0.
                        }
                    }
                    else {
                        if (termPtr->termInfo.coefficient == -1) {
                            fprintf(output, "-x");                               // exponent = 1, not first term, coeff = -1.
                        }
                        else {
                            fprintf(output, "%dx", termPtr->termInfo.coefficient);   // exponent = 1, not first term, coeff < 0 && coeff != -1.
                        }
                    }
                }
            }
            else {                                                       // if the term that you want to insert is with exponent > 1.
                if (termCounter == 1) {
                    if (termPtr->termInfo.coefficient == 1) {
                        fprintf(output, "x^%d", termPtr->termInfo.exponent);     // exponent > 1, first term, coeff = 1.
                    }
                    else if (termPtr->termInfo.coefficient == -1) {
                        fprintf(output, "-x^%d", termPtr->termInfo.exponent);    // exponent > 1, first term, coeff = -1.
                    }
                    else {
                        fprintf(output, "%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);    // exponent > 1, first term, coeff != (1 or -1).
                    }

                }
                else {
                    if (termPtr->termInfo.coefficient > 0) {
                        if (termPtr->termInfo.coefficient == 1) {
                            fprintf(output, "+x^%d", termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff = 1.
                        }
                        else {
                            fprintf(output, "+%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);   // exponent > 1, not first term, coeff > 0 && coeff != 1.
                        }
                    }
                    else {
                        if (termPtr->termInfo.coefficient == -1) {
                            fprintf(output, "-x^%d", termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff = -1.
                        }
                        else {
                            fprintf(output, "%dx^%d", termPtr->termInfo.coefficient, termPtr->termInfo.exponent);    // exponent > 1, not first term, coeff < 0 && coeff != -1.
                        }
                    }
                }
            }
            termPtr = termPtr->next_term;
            termCounter++;
        }
        fprintf(output, "\n");

        tempStack->Top = ptr->next_poly;
        tempStack->number_of_polynomials--;

        ptr->next_poly = PolynomialsStack->Top;
        PolynomialsStack->Top = ptr;
        PolynomialsStack->number_of_polynomials++;
        ptr = tempStack->Top;

    }
    fclose(output);         // Close the output file after done printing.
}

//! Deletes a single term from a given polynomial.
void delete_term(struct PolyNode* polynomial, struct TermNode* term) {
    struct TermNode* termPtr = polynomial->terms;
    if (termPtr == term) {                      // if the term is first.
        polynomial->terms = termPtr->next_term;
        free(termPtr);
        polynomial->number_of_terms--;
        return;
    }
    while (termPtr->next_term != term) {        // loop until you find the term.
        termPtr = termPtr->next_term;
    }
    termPtr->next_term = term->next_term;       // link the previous terms then delete it.
    free(term);
    polynomial->number_of_terms--;

}

//! Adds all terms with the same exponent, deletes terms with 0 coefficient, and sorts terms descending according to exponent.
void process_Polynomial(struct PolyNode* Polynomial) {
    if (Polynomial->number_of_terms == 0) {
        printf("The polynomial is empty !\n");
        return;
    }
    else if (Polynomial->number_of_terms == 1) {
        return;
    }
    else {
        struct TermNode* termPtr1 = Polynomial->terms;
        struct TermNode* termPtr2 = Polynomial->terms->next_term;

        // A loop to add all terms with the same exponent Ex:(x ^2 and -3x^2).
        for (termPtr1; termPtr1 != NULL; termPtr1 = termPtr1->next_term) {

            for (termPtr2 = termPtr1->next_term; termPtr2 != NULL; ) {
                if (termPtr1->termInfo.exponent == termPtr2->termInfo.exponent) {
                    termPtr1->termInfo.coefficient = termPtr1->termInfo.coefficient + termPtr2->termInfo.coefficient;
                    struct TermNode* temp = termPtr2->next_term;
                    delete_term(Polynomial, termPtr2);
                    termPtr2 = temp;
                    continue;
                }
                termPtr2 = termPtr2->next_term;
            }
        }

        // A loop to delete all terms with 0 coefficient.
        for (termPtr1 = Polynomial->terms; termPtr1 != NULL;) {
            if (termPtr1->termInfo.coefficient == 0) {
                struct TermNode* temp = termPtr1->next_term;
                delete_term(Polynomial, termPtr1);
                termPtr1 = temp;
                continue;
            }
            termPtr1 = termPtr1->next_term;
        }

        // A loop to sort the terms from biggest to smallest exponent.
        if (Polynomial->number_of_terms > 1) {
            for (termPtr1 = Polynomial->terms; termPtr1->next_term != NULL; termPtr1 = termPtr1->next_term) {
                for (termPtr2 = termPtr1->next_term; termPtr2 != NULL; termPtr2 = termPtr2->next_term) {
                    if (termPtr2->termInfo.exponent > termPtr1->termInfo.exponent) {
                        int temp = termPtr1->termInfo.coefficient;
                        termPtr1->termInfo.coefficient = termPtr2->termInfo.coefficient;
                        termPtr2->termInfo.coefficient = temp;

                        temp = termPtr1->termInfo.exponent;
                        termPtr1->termInfo.exponent = termPtr2->termInfo.exponent;
                        termPtr2->termInfo.exponent = temp;
                    }
                }
            }
        }
    }
}

//! Pops the top polynomial and returns it.
struct PolyNode* pop_and_return_poly(struct PolyStack* PolynomialsStack) {
    if (PolynomialsStack->number_of_polynomials == 0) {
        printf("The stack is empty!\n");
        return NULL;
    }
    // Updates the stack after popping the poly, then returns the popped poly.
    struct PolyNode* polyPtr = PolynomialsStack->Top;
    PolynomialsStack->Top = polyPtr->next_poly;
    PolynomialsStack->number_of_polynomials--;
    polyPtr->next_poly == NULL;
    return polyPtr;
}

//! Arithmetic Logic Unit, Does all the arithmetic functions in this project (+ , - , *).
//! to specify which operation to do pick the OpCode for it (0 for subtraction, 1 for addition, 2 for multiplication).
void ALU(struct PolyStack* PolynomialsStack, int OpCode) {
    if (PolynomialsStack->number_of_polynomials == 0) {
        printf("The stack is empty !\n");
        return;
    }
    else if (PolynomialsStack->number_of_polynomials == 1) {
        printf("You only have one polynomial left in the stack !\n");
        return;
    }
    else {
        //! Copies the polynomial stack in order to preserve the polynomials in the original polynomials Stack.
        struct PolyStack* tempStack = copyStack(PolynomialsStack, NULL);

        //! loop for Adding/Subtracting/Multiplying all the terms in the stack until its empty.
        //! ***** The operations are done to the top 2 elements (TOP, TOP - 1).
        //! ***** This loops keeps doing the needed operation on the polynomials 2 at a time, until there is only 1 poly left in the stack.
        while (tempStack->number_of_polynomials >= 2) {
            // Pops the top 2 nodes to do the operation.
            struct PolyNode* secondPoly = pop_and_return_poly(tempStack);
            struct PolyNode* firstPoly = pop_and_return_poly(tempStack);
            printf("( ");
            printPolynomial(firstPoly);
            printf(" )");
            if (OpCode == SUBTRACTION) {
                printf("-");
            }
            else if (OpCode == ADDITION) {
                printf("+");
            }
            else {
                printf("*");
            }
            printf("( ");
            printPolynomial(secondPoly);
            printf(" )");

            struct TermNode* termPtr1 = firstPoly->terms;
            struct TermNode* termPtr2 = secondPoly->terms;

            // Creates a result polynomial to push it back into the temp stack for the next operation.
            struct PolyNode* result = NULL;
            result = (struct PolyNode*)malloc(sizeof(struct PolyNode));
            result->number_of_terms = 0;
            result->next_poly = NULL;
            result->terms = NULL;

            // if addition or multiplication. (0: subtraction, 1: addition).
            if (OpCode == SUBTRACTION || OpCode == ADDITION) {

                //! loop into all the first poly terms
                for (termPtr1; termPtr1 != NULL;) {
                    bool pairFoundFlag = false;
                    //! loop into all the second poly terms to check if there is a term with the same exponent.
                    for (termPtr2; termPtr2 != NULL; termPtr2 = termPtr2->next_term) {
                        //! if there is a term in the second poly that has the same exponent:
                        //! 1. --> Add the two terms and insert them into the result polynomial.
                        //! 2. --> delete both of the terms from the first and second poly.
                        if (termPtr1->termInfo.exponent == termPtr2->termInfo.exponent) {
                            int coeff;
                            int exp;

                            if (OpCode == ADDITION) {
                                coeff = termPtr1->termInfo.coefficient + termPtr2->termInfo.coefficient;
                                exp = termPtr1->termInfo.exponent;
                            }
                            else if (OpCode == SUBTRACTION) {
                                coeff = termPtr1->termInfo.coefficient - termPtr2->termInfo.coefficient;
                                exp = termPtr2->termInfo.exponent;
                            }
                            insert_term(result, NULL, coeff, exp);

                            struct TermNode* temp = termPtr1->next_term;
                            delete_term(firstPoly, termPtr1);
                            termPtr1 = temp;

                            temp = termPtr2->next_term;
                            delete_term(secondPoly, termPtr2);
                            termPtr2 = temp;

                            pairFoundFlag = true;
                            break;
                        }
                    }
                    //! if after looping through the second polynomial, you still didn't find any term with same exponent as the term in the first poly.
                    //! simply insert the term in the first polynomial into the result polynomial, and delete it from the first polynomial.
                    if (pairFoundFlag == false) {
                        insert_term(result, NULL, termPtr1->termInfo.coefficient, termPtr1->termInfo.exponent);
                        struct TermNode* temp = termPtr1->next_term;
                        delete_term(firstPoly, termPtr1);
                        termPtr1 = temp;
                    }
                }
                //! if there is still some terms in the second polynomial.
                //! simply insert them into the result polynomial.
                if (secondPoly->number_of_terms != 0) {
                    for (termPtr2 = secondPoly->terms; termPtr2 != NULL; ) {

                        if (OpCode == ADDITION) {
                            insert_term(result, NULL, termPtr2->termInfo.coefficient, termPtr2->termInfo.exponent);

                        }
                        else if (OpCode == SUBTRACTION) {
                            insert_term(result, NULL, (-1 * termPtr2->termInfo.coefficient), termPtr2->termInfo.exponent);
                        }

                        struct TermNode* temp = termPtr2->next_term;
                        delete_term(secondPoly, termPtr2);
                        termPtr2 = temp;
                        if (termPtr2 == NULL) {
                            break;
                        }
                    }
                }
            }
            else if (OpCode == MULTIPLICATION) {             // 2 indicates multiplication.
                //! loop through the first polynomial and multiply it with each term in the second poly.
                //! then adds every single multiplication results into the result stack.
                //! multiplication simply adds the exponents and multiplies the coefficients.
                for (termPtr1; termPtr1 != NULL; termPtr1 = termPtr1->next_term) {
                    for (termPtr2 = secondPoly->terms; termPtr2 != NULL; termPtr2 = termPtr2->next_term) {

                        int coefficient = termPtr1->termInfo.coefficient * termPtr2->termInfo.coefficient;
                        int exponent = termPtr1->termInfo.exponent + termPtr2->termInfo.exponent;
                        insert_term(result, NULL, coefficient, exponent);
                    }
                 }
                struct TermNode* termDisposal1 = firstPoly->terms;
                struct TermNode* termDisposal2 = secondPoly->terms;

                //! dispose all the terms in the first poly in the temp stack.
                while (termDisposal1 != NULL) {
                    firstPoly->terms = termDisposal1->next_term;
                    free(termDisposal1);
                    termDisposal1 = firstPoly->terms;
                }

                //! dispose all the terms in the second poly in the temp stack.
                while (termDisposal2 != NULL) {
                    secondPoly->terms = termDisposal2->next_term;
                    free(termDisposal2);
                    termDisposal2 = secondPoly->terms;
                }
            }
            // free the memory allocated for all the temporary polynomials in the temp stack.
            free(firstPoly);
            free(secondPoly);
            // adds all the terms with the same exponent, removes all terms with 0 coefficients, sorts them in  descending order according to exponent.
            process_Polynomial(result);

            printf("=");
            printf("( ");
            printPolynomial(result);
            printf(" )");
            printf("\n");

            // pushes the result back into the temp stack to make it ready for the next operation until the stack is empty.
            tempStack->number_of_polynomials++;
            result->next_poly = tempStack->Top;
            tempStack->Top = result;
        }
        //! Now pushes the final result into the results stack.
        //! Frees the temp stack allocated space.
        struct PolyNode* temp = resultsStack->Top;
        resultsStack->Top = tempStack->Top;
        resultsStack->Top->next_poly = temp;
        resultsStack->number_of_polynomials++;
        if (OpCode == SUBTRACTION) {
            subtractionResult = resultsStack->Top;
            printf("Polynomials subtracted successfully !!\n");

        }
        else if (OpCode == ADDITION) {
            additionResult = resultsStack->Top;
            printf("Polynomials added successfully !!\n");

        }
        else {
            multiplicationResult = resultsStack->Top;
            printf("Polynomials multiplied successfully !!\n");
        }
        free(tempStack);
    }
}

//! simply checks if a given number is even.
bool is_even(int x) {
    return (x % 2) == 0 ? true : false;
}

//! simply calculates the power of a given number (x^n).
int POWER(int x, int n) {
    if (x == 0) {
        return 0;
    }
    else if (n == 0) {
        return 1;
    }
    else if (n == 1) {
        return x;
    }
    else {
        if (is_even(n) == true) {
            return POWER(x * x, n / 2);
        }
        else {
            return POWER(x * x, n / 2) * x;
        }
    }
}

//! Frees all given polynomial terms.
void free_polynomial_terms(struct PolyNode* Polynomial) {
    struct TermNode* termPtr = Polynomial->terms;
    // loop into the polynomial terms and deletes them one by one.
    while (termPtr != NULL) {
        struct TermNode* temp = termPtr->next_term;
        delete_term(Polynomial, termPtr);
        termPtr = temp;
    }
}

//! Frees all given stack terms.
void free_stack(struct PolyStack* Stack) {
    struct PolyNode* polyPtr = Stack->Top;

    // loop into the stack polynomials and deletes them one by one (with the terms).
    while (polyPtr != NULL) {
        free_polynomial_terms(polyPtr);
        struct PolyNode* temp = polyPtr->next_poly;
        Stack->Top = polyPtr->next_poly;
        free(polyPtr);
        polyPtr = temp;
    }
    free(Stack);
}

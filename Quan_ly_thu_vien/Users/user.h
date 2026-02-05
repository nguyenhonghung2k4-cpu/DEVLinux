#ifndef USER_H
#define USER_H

#define MAX_NAME_LEN 50
#define MAX_BORROW 5 /* Maximum number of books a user can borrow at once */

/* Structure definition for a User */
typedef struct {
    int id;                          /* Unique ID of the user */
    char name[MAX_NAME_LEN];         /* Name of the user */
    int borrowedBookIds[MAX_BORROW]; /* Array storing IDs of borrowed books */
    int borrowCount;                 /* Current number of books borrowed */
} User;

/* * Create a new User object by prompting user input.
 * newId: The automatically assigned ID for the new user.
 * Returns: A populated User structure.
 */
User createUserInput(int newId);

/* * Update information of an existing user.
 * u: Pointer to the User to be updated.
 */
void updateUserInfo(User* u);

/* * Print the table header for the user list display.
 */
void printUserHeader();

/* * Print a single user's details, including the list of borrowed book IDs.
 * u: Pointer to the User to display.
 */
void printUserRow(const User* u);

/* * Add a book ID to the user's borrowed list.
 * u: Pointer to the User.
 * bookId: ID of the book to be borrowed.
 * Returns: 1 if successful, 0 if the limit is reached (MAX_BORROW).
 */
int userBorrowBook(User* u, int bookId);

/* * Remove a book ID from the user's borrowed list (Return a book).
 * u: Pointer to the User.
 * bookId: ID of the book to be returned.
 * Returns: 1 if successful, 0 if the book ID was not found in the list.
 */
int userReturnBook(User* u, int bookId);

#endif
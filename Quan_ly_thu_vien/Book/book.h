#ifndef BOOK_H
#define BOOK_H

#define MAX_TITLE_LEN 100
#define MAX_AUTHOR_LEN 50

/* Enum representing the availability status of a book */
typedef enum {
    BOOK_AVAILABLE = 0, /* The book is available for borrowing */
    BOOK_BORROWED = 1   /* The book is currently borrowed */
} BookStatus;

/* Structure definition for a Book */
typedef struct {
    int id;                         /* Unique ID of the book */
    char title[MAX_TITLE_LEN];      /* Title of the book */
    char author[MAX_AUTHOR_LEN];    /* Author of the book */
    BookStatus status;              /* Availability status */
    int borrowerId;                 /* ID of the user borrowing the book (-1 if available) */
} Book;

/* * Create a new Book object by prompting user input.
 * newId: The automatically assigned ID for the new book.
 * Returns: A populated Book structure.
 */
Book createBookInput(int newId);

/* * Update information of an existing book (Title, Author).
 * b: Pointer to the Book to be updated.
 */
void updateBookInfo(Book* b);

/* * Print the table header for the book list display.
 */
void printBookHeader();

/* * Print a single book's details as a formatted table row.
 * b: Pointer to the Book to display.
 */
void printBookRow(const Book* b);

#endif
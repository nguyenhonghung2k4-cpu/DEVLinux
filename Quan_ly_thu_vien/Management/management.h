#ifndef MANAGEMENT_H
#define MANAGEMENT_H

#include "C:\Users\Admin\OneDrive\Documents\C cơ bản\DEV_Linux\Quan_ly_thu_vien\Book\book.h"
#include "C:\Users\Admin\OneDrive\Documents\C cơ bản\DEV_Linux\Quan_ly_thu_vien\Users\user.h"

#define MAX_BOOKS 100
#define MAX_USERS 100

/* * Initialize the system (reset counters and data).
 */
void initSystem();

/* --- BOOK MANAGEMENT FUNCTIONS --- */

/* Handle the process of adding a new book to the library */
void handleAddBook();

/* Handle the process of editing an existing book's info */
void handleEditBook();

/* Handle the process of deleting a book (checks conditions before deleting) */
void handleDeleteBook();

/* Search for books by title or author keyword */
void handleSearchBook();

/* Display all books currently in the system */
void handleShowAllBooks();

/* --- USER MANAGEMENT FUNCTIONS --- */

/* Handle the process of registering a new user */
void handleAddUser();

/* Handle the process of editing an existing user's info */
void handleEditUser();

/* Handle the process of deleting a user (ensures all books are returned first) */
void handleDeleteUser();

/* Display all registered users */
void handleShowAllUsers();

/* --- BORROW / RETURN OPERATIONS --- */

/* Handle the logic for borrowing a book */
void handleBorrowBook();

/* Handle the logic for returning a book */
void handleReturnBook();

#endif
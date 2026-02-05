#include <stdio.h>
#include <string.h>
#include "book.h"
#include "../Ultils/ultils.h"

Book createBookInput(int newId) {
    Book b;
    b.id = newId;
    b.status = BOOK_AVAILABLE;
    b.borrowerId = -1;

    getStringInput("Nhap tua sach: ", b.title, sizeof(b.title));
    getStringInput("Nhap tac gia: ", b.author, sizeof(b.author));

    return b;
}

void updateBookInfo(Book* b) {
    printf("--- Cap nhat sach ID: %d ---\n", b->id);
    getStringInput("Nhap tua sach moi: ", b->title, sizeof(b->title));
    getStringInput("Nhap tac gia moi: ", b->author, sizeof(b->author));
}

void printBookHeader() {
    printf("| %-4s | %-30s | %-20s | %-12s | %-10s |\n", 
           "ID", "Tua Sach", "Tac Gia", "Trang Thai", "Nguoi Muon");
    printf("|%s|\n", "------------------------------------------------------------------------------------------");
}

void printBookRow(const Book* b) {
    char borrowerStr[10];
    if (b->status == BOOK_BORROWED) sprintf(borrowerStr, "%d", b->borrowerId);
    else strcpy(borrowerStr, "-");

    printf("| %-4d | %-30s | %-20s | %-12s | %-10s |\n", 
           b->id, b->title, b->author, 
           b->status == BOOK_BORROWED ? "DA MUON" : "CO SAN",
           borrowerStr);
}
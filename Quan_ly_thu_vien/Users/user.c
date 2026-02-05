#include <stdio.h>
#include "user.h"
#include "../Ultils/ultils.h"

User createUserInput(int newId) {
    User u;
    u.id = newId;
    u.borrowCount = 0;
    for(int i = 0; i < MAX_BORROW; i++) u.borrowedBookIds[i] = 0;
    
    getStringInput("Nhap ten nguoi dung: ", u.name, sizeof(u.name));
    return u;
}

void updateUserInfo(User* u) {
    printf("--- Cap nhat User ID: %d ---\n", u->id);
    getStringInput("Nhap ten moi: ", u->name, sizeof(u->name));
}

void printUserHeader() {
    printf("| %-4s | %-25s | %-10s | %-30s |\n", "ID", "Ho Ten", "Slg Muon", "DS Sach (ID)");
    printf("|%s|\n", "------------------------------------------------------------------------------");
}

void printUserRow(const User* u) {
    char listBook[50] = "";
    char temp[10];
    
    for (int i = 0; i < u->borrowCount; i++) {
        sprintf(temp, "%d ", u->borrowedBookIds[i]);
        /* Nối chuỗi thủ công để tránh dùng thư viện lạ */
        int len = 0;
        while(listBook[len] != '\0') len++;
        int j = 0;
        while(temp[j] != '\0') listBook[len++] = temp[j++];
        listBook[len] = '\0';
    }

    printf("| %-4d | %-25s | %-10d | %-30s |\n", 
            u->id, u->name, u->borrowCount, listBook);
}

int userBorrowBook(User* u, int bookId) {
    if (u->borrowCount >= MAX_BORROW) return 0;
    u->borrowedBookIds[u->borrowCount] = bookId;
    u->borrowCount++;
    return 1;
}

int userReturnBook(User* u, int bookId) {
    int foundIndex = -1;
    for (int i = 0; i < u->borrowCount; i++) {
        if (u->borrowedBookIds[i] == bookId) {
            foundIndex = i;
            break;
        }
    }

    if (foundIndex == -1) return 0;

    /* Dồn mảng để xóa phần tử */
    for (int i = foundIndex; i < u->borrowCount - 1; i++) {
        u->borrowedBookIds[i] = u->borrowedBookIds[i+1];
    }
    u->borrowCount--;
    return 1;
}
#include <stdio.h>
#include <string.h>
#include "management.h"
#include "../Ultils/ultils.h"

Book library[MAX_BOOKS];
User users[MAX_USERS];
int bookCount = 0;
int userCount = 0;

int findBookIndexById(int id) {
    for (int i = 0; i < bookCount; i++) {
        if (library[i].id == id) return i;
    }
    return -1;
}

int findUserIndexById(int id) {
    for (int i = 0; i < userCount; i++) {
        if (users[i].id == id) return i;
    }
    return -1;
}

void initSystem() {
    bookCount = 0;
    userCount = 0;
}

void handleAddBook() {
    if (bookCount >= MAX_BOOKS) {
        printf(">> Loi: Kho sach da day!\n");
        return;
    }
    int newId = (bookCount == 0) ? 100 : library[bookCount - 1].id + 1;
    library[bookCount] = createBookInput(newId);
    bookCount++;
    printf(">> Thanh cong: Da them sach voi ID %d\n", newId);
}

void handleEditBook() {
    int id = getIntInput("Nhap ID sach can sua: ");
    int index = findBookIndexById(id);
    if (index == -1) {
        printf(">> Loi: Khong tim thay sach!\n");
        return;
    }
    updateBookInfo(&library[index]);
    printf(">> Thanh cong: Da cap nhat thong tin sach.\n");
}

void handleDeleteBook() {
    int id = getIntInput("Nhap ID sach can xoa: ");
    int index = findBookIndexById(id);
    if (index == -1) {
        printf(">> Loi: Khong tim thay sach!\n");
        return;
    }
    if (library[index].status == BOOK_BORROWED) {
        printf(">> Loi: Sach dang duoc muon, khong the xoa!\n");
        return;
    }
    for (int i = index; i < bookCount - 1; i++) {
        library[i] = library[i + 1];
    }
    bookCount--;
    printf(">> Thanh cong: Da xoa sach ID %d\n", id);
}

void handleSearchBook() {
    char keyword[100];
    getStringInput("Nhap ten sach hoac tac gia de tim: ", keyword, sizeof(keyword));
    
    printf("\n--- KET QUA TIM KIEM ---\n");
    printBookHeader();
    int found = 0;
    for (int i = 0; i < bookCount; i++) {
        if (strstr(library[i].title, keyword) != NULL || 
            strstr(library[i].author, keyword) != NULL) {
            printBookRow(&library[i]);
            found = 1;
        }
    }
    if (!found) printf("| Khong tim thay ket qua nao |\n");
}

void handleShowAllBooks() {
    printf("\n--- DANH SACH TOAN BO SACH ---\n");
    printBookHeader();
    for (int i = 0; i < bookCount; i++) {
        printBookRow(&library[i]);
    }
}

void handleAddUser() {
    if (userCount >= MAX_USERS) {
        printf(">> Loi: Danh sach nguoi dung da day!\n");
        return;
    }
    int newId = (userCount == 0) ? 1 : users[userCount - 1].id + 1;
    users[userCount] = createUserInput(newId);
    userCount++;
    printf(">> Thanh cong: Da them nguoi dung ID %d\n", newId);
}

void handleEditUser() {
    int id = getIntInput("Nhap ID nguoi dung can sua: ");
    int index = findUserIndexById(id);
    if (index == -1) {
        printf(">> Loi: Khong tim thay nguoi dung!\n");
        return;
    }
    updateUserInfo(&users[index]);
    printf(">> Thanh cong: Da cap nhat thong tin nguoi dung.\n");
}

void handleDeleteUser() {
    int id = getIntInput("Nhap ID nguoi dung can xoa: ");
    int index = findUserIndexById(id);
    if (index == -1) {
        printf(">> Loi: Khong tim thay nguoi dung!\n");
        return;
    }
    if (users[index].borrowCount > 0) {
        printf(">> Loi: Nguoi dung dang muon sach, yeu cau tra het truoc khi xoa!\n");
        return;
    }

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i+1];
    }
    userCount--;
    printf(">> Thanh cong: Da xoa nguoi dung ID %d\n", id);
}

void handleShowAllUsers() {
    printf("\n--- DANH SACH NGUOI DUNG ---\n");
    printUserHeader();
    for (int i = 0; i < userCount; i++) {
        printUserRow(&users[i]);
    }
}

void handleBorrowBook() {
    int userId = getIntInput("Nhap ID nguoi muon: ");
    int uIdx = findUserIndexById(userId);
    if (uIdx == -1) {
        printf(">> Loi: Khong tim thay nguoi dung!\n");
        return;
    }

    int bookId = getIntInput("Nhap ID sach muon muon: ");
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        printf(">> Loi: Khong tim thay sach!\n");
        return;
    }

    if (library[bIdx].status == BOOK_BORROWED) {
        printf(">> Loi: Sach nay da co nguoi khac muon!\n");
        return;
    }

    if (!userBorrowBook(&users[uIdx], bookId)) {
        printf(">> Loi: Nguoi dung da muon toi da so luong sach cho phep!\n");
        return;
    }
    library[bIdx].status = BOOK_BORROWED;
    library[bIdx].borrowerId = userId;
    printf(">> Thanh cong: Muon sach thanh cong!\n");
}

void handleReturnBook() {
    int bookId = getIntInput("Nhap ID sach can tra: ");
    int bIdx = findBookIndexById(bookId);
    if (bIdx == -1) {
        printf(">> Loi: Khong tim thay sach!\n");
        return;
    }

    if (library[bIdx].status == BOOK_AVAILABLE) {
        printf(">> Loi: Sach nay hien dang co trong kho (chua duoc muon)!\n");
        return;
    }
    int userId = library[bIdx].borrowerId;
    int uIdx = findUserIndexById(userId);
    
    if (uIdx != -1) {
        userReturnBook(&users[uIdx], bookId);
    } else {
        printf(">> Canh bao: Khong tim thay thong tin nguoi da muon (Data error).\n");
    }
    library[bIdx].status = BOOK_AVAILABLE;
    library[bIdx].borrowerId = -1;
    printf(">> Thanh cong: Tra sach thanh cong!\n");
}
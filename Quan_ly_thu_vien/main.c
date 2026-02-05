#include <stdio.h>
#include "Management/management.h"
#include "Ultils/ultils.h"

void showMenu() {
    printf("\n=== HE THONG QUAN LY THU VIEN CAI TIEN ===\n");
    printf("1. Quan Ly SACH (Them/Sua/Xoa/Hien Thi)\n");
    printf("2. Quan Ly NGUOI DUNG (Them/Sua/Xoa/Hien Thi)\n");
    printf("3. Tim Kiem Sach\n");
    printf("4. Muon Sach\n");
    printf("5. Tra Sach\n");
    printf("0. Thoat\n");
    printf("==========================================\n");
}

void subMenuBook() {
    printf("\n--- QUAN LY SACH ---\n");
    printf("1. Them sach moi\n");
    printf("2. Sua thong tin sach\n");
    printf("3. Xoa sach\n");
    printf("4. Hien thi tat ca\n");
    
    int choice = getIntInput("Chon chuc nang: ");
    switch(choice) {
        case 1: handleAddBook(); break;
        case 2: handleEditBook(); break;
        case 3: handleDeleteBook(); break;
        case 4: handleShowAllBooks(); break;
        default: printf("Lua chon khong hop le.\n");
    }
}

void subMenuUser() {
    printf("\n--- QUAN LY NGUOI DUNG ---\n");
    printf("1. Them nguoi dung\n");
    printf("2. Sua thong tin\n");
    printf("3. Xoa nguoi dung\n");
    printf("4. Hien thi tat ca\n");
    
    int choice = getIntInput("Chon chuc nang: ");
    switch(choice) {
        case 1: handleAddUser(); break;
        case 2: handleEditUser(); break;
        case 3: handleDeleteUser(); break;
        case 4: handleShowAllUsers(); break;
        default: printf("Lua chon khong hop le.\n");
    }
}

int main() {
    initSystem();
    int choice;

    while (1) {
        showMenu();
        choice = getIntInput("Lua chon cua ban: ");

        switch (choice) {
            case 1: subMenuBook(); break;
            case 2: subMenuUser(); break;
            case 3: handleSearchBook(); break;
            case 4: handleBorrowBook(); break;
            case 5: handleReturnBook(); break;
            case 0: 
                printf("Tam biet!\n");
                return 0;
            default: 
                printf("Lua chon khong hop le! Vui long chon lai.\n");
        }
    }
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- 1.1 Định nghĩa cấu trúc Node ---
typedef struct TaskNode {
    char task_description[50];
    struct TaskNode* next;
} TaskNode_t;

TaskNode_t *queue_head = NULL;
TaskNode_t *queue_tail = NULL;

// --- 1.2 Triển khai các hàm quản lý hàng đợi ---
void queue_add_task(const char* description) {
    TaskNode_t* newNode = (TaskNode_t*)malloc(sizeof(TaskNode_t));
    if (!newNode) {
        printf("Loi: Khong du bo nho!\n");
        return;
    }
    
    strncpy(newNode->task_description, description, 49);
    newNode->task_description[49] = '\0'; // Đảm bảo kết thúc chuỗi
    newNode->next = NULL;

    if (queue_tail == NULL) { // Hàng đợi đang rỗng
        queue_head = queue_tail = newNode;
    } else {
        queue_tail->next = newNode;
        queue_tail = newNode;
    }
    printf("Da them tac vu: %s\n", description);
}

TaskNode_t* queue_get_next_task(void) {
    if (queue_head == NULL) return NULL; // Hàng đợi rỗng

    TaskNode_t* temp = queue_head;
    queue_head = queue_head->next;

    if (queue_head == NULL) { // Nếu lấy ra node cuối cùng
        queue_tail = NULL;
    }
    return temp;
}

void print_task_queue(void) {
    TaskNode_t* current = queue_head;
    printf("\n--- Hang doi tac vu hien tai ---\n");
    if (!current) printf("(Trong)\n");
    while (current) {
        printf("- %s\n", current->task_description);
        current = current->next;
    }
    printf("-------------------------------\n");
}
// --- 2.1 Định nghĩa cấu trúc Node ---
typedef struct HistoryNode {
    char log_entry[50];
    struct HistoryNode* next;
    struct HistoryNode* prev;
} HistoryNode_t;

HistoryNode_t* history_head = NULL;

// --- 2.2 Triển khai các hàm quản lý nhật ký ---
void history_log_activity(const char* entry) {
    HistoryNode_t* newNode = (HistoryNode_t*)malloc(sizeof(HistoryNode_t));
    if (!newNode) return;

    strncpy(newNode->log_entry, entry, 49);
    newNode->log_entry[49] = '\0';
    newNode->prev = NULL;
    newNode->next = history_head;

    if (history_head != NULL) {
        history_head->prev = newNode;
    }
    history_head = newNode; // Cập nhật head mới
}

void history_navigate(void) {
    if (history_head == NULL) {
        printf("Nhat ky trong!\n");
        return;
    }

    HistoryNode_t* current = history_head;
    char choice;
    
    printf("\n--- Che do xem nhat ky (nhap q de thoat)---\n");
    while (1) {
        printf("Dang xem: [%s]\n", current->log_entry);
        printf("Lenh (n: old, p: new, q: quit): ");
        scanf(" %c", &choice);

        if (choice == 'n') { // Next node (đi sâu vào quá khứ do chèn ở đầu)
            if (current->next) current = current->next;
            else printf(">> Ban dang o cuoi (old)\n");
        } else if (choice == 'p') { // Previous node (quay lại hiện tại)
            if (current->prev) current = current->prev;
            else printf(">> Ban dang o dau (new)\n");
        } else if (choice == 'q') {
            printf("Quit\n");
            break;
        } else {
            printf(">>Lenh khong hop le.\n");
        }
    }
}
void free_all_memory() {
    // Dọn dẹp Task Queue
    TaskNode_t* current_task = queue_head;
    while (current_task != NULL) {
        TaskNode_t* temp = current_task;
        current_task = current_task->next;
        free(temp);
    }

    // Dọn dẹp Activity Log
    HistoryNode_t* current_history = history_head;
    while (current_history != NULL) {
        HistoryNode_t* temp = current_history;
        current_history = current_history->next;
        free(temp);
    }
    printf("Da don dep toan bo bo nho!\n");
}

int main() {
    char command[20];
    char desc[50];

    printf("=== He thong quan ly tac vu va nhat ky ===\n");
    printf("Cac lenh: add <mo ta>, run, history, list, exit\n");

    while (1) {
        printf("\n> ");
        scanf("%s", command);

        if (strcmp(command, "add") == 0) {
            scanf(" %[^\n]", desc); // Đọc toàn bộ chuỗi có dấu cách phía sau
            queue_add_task(desc);
        } 
        else if (strcmp(command, "run") == 0) {
            TaskNode_t* task = queue_get_next_task();
            if (task) {
                printf("Dang thuc thi: %s\n", task->task_description);
                
                // Ghi vào nhật ký bằng DLL
                char log[60];
                snprintf(log, sizeof(log), "Hoan thanh: %s", task->task_description);
                history_log_activity(log);

                // Quan trọng: Giải phóng bộ nhớ của SLL node sau khi xử lý xong
                free(task); 
            } else {
                printf("Khong co tac vu nao trong hang doi de chay.\n");
            }
        } 
        else if (strcmp(command, "history") == 0) {
            history_navigate();
        } 
        else if (strcmp(command, "list") == 0) {
            print_task_queue();
        } 
        else if (strcmp(command, "exit") == 0) {
            printf("Dang thoat he thong...\n");
            free_all_memory(); // Giải phóng phần bộ nhớ còn lại
            break;
        } 
        else {
            printf("Lenh khong hop le. Vui long thu lai\n");
            // Clear input buffer nếu người dùng nhập sai định dạng
            int c;
            while ((c = getchar()) != '\n' && c != EOF) { }
        }
    }

    return 0;
}
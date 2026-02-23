#include <stdio.h>
#include "logger.h"

int main() {
   
    if (!logger_init("application.log", LOG_INFO)) {
        fprintf(stderr, "Khong the khoi tao logger.\n");
        return 1;
    }

    
    log_message(LOG_INFO, "Start");
    
    int user_id = 404;
    log_message(LOG_WARNING, "Khong tim thay du lieu cho user co ID = %d", user_id);
  
    log_message(LOG_ERROR, "Khong the ket noi den database: %s", "Timeout connection");

    logger_set_level(LOG_DEBUG);
    log_message(LOG_INFO, "Da thay doi muc log toi thieu xuong LOG_DEBUG.");
    log_message(LOG_DEBUG, "Con tro dang o dia chi %p", (void*)&user_id);

    log_message(LOG_DEBUG, "Tien trinh quet bo nho da hoan tat.");

    log_message(LOG_INFO, "Chuong trinh ket thuc.");
    logger_close();

    return 0;
}
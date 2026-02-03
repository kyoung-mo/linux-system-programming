#define _POSIX_C_SOURCE 200809L // dprintf 사용을 위한 매크로
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

void write_log_simple(const char *msg) {
    int fd = open("system.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) return;

    time_t now = time(NULL);
    struct tm t;
    localtime_r(&now, &t);

    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &t);

    // ★ 핵심: write() 대신 printf처럼 사용 가능
    dprintf(fd, "[%s] %s\n", time_str, msg);

    close(fd);
}

int main() {
    write_log_simple("[INFO] System Started");
    write_log_simple("[WARN] Memory usage high");
    return 0;
}
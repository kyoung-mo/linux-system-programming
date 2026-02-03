#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

void write_log(const char *msg) {
    // O_APPEND: 쓰기 시 무조건 파일 끝에 붙임 (동시성 보장)
    // 0644: 소유자 RW, 그룹/기타 R
    int fd = open("system.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) {
        perror("log open fail");
        return;
    }
    
    // 실제로는 timestamp 등을 붙여서 write함
    write(fd, msg, strlen(msg));
    write(fd, "\n", 1);
    
    close(fd);
}
void write_log_with_time(const char *msg) {
    int fd = open("system.log", O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (fd == -1) return;

    // 1. 현재 시간 구하기
    time_t now = time(NULL);
    struct tm t;
    localtime_r(&now, &t); // Thread-safe한 버전 사용 권장

    // 2. 시간 포맷팅 (예: 2026-01-31 14:00:00)
    char time_str[64];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", &t);

    // 3. 최종 로그 문자열 만들기 (시간 + 메시지 + 개행)
    char log_buf[1024];
    // snprintf: 버퍼 오버플로우 방지 (안전함)
    int len = snprintf(log_buf, sizeof(log_buf), "[%s] %s\n", time_str, msg);

    // 4. 한번에 쓰기 (Atomic write 효과)
    if (len > 0) {
        write(fd, log_buf, len);
    }
    
    close(fd);
}

int main() {
    write_log_with_time("[INFO] System Started");
    write_log_with_time("[WARN] Memory usage high");
    return 0;
}
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

void write_log(const char *msg) {
    // O_APPEND: 쓰기 시 무조건 파일 끝에 붙임 (동시성 보장)
    // 0644: 소유자 RW, 그룹/기타 R
    int fd = open("system.log", O_WRONLY | O_CREAT | O_APPEND, 0666);
    if (fd == -1) {
        perror("log open fail");
        return;
    }

    FILE *fp =fopen("log.txt", "a");
    
    // 실제로는 timestamp 등을 붙여서 write함
    while(1){
        //write(fd, msg, strlen(msg));
        fp =fopen("log.txt", "a");
        if(fp){
            fprintf(fp, "log messge\n");
            fflush(fp);
        }
        fclose(fp);
        sleep(1);

    }
    write(fd, msg, strlen(msg));
    //write(fd, "\n", 1);
    
    close(fd);
    
}

int main() {
    write_log("[INFO] System Started");
    write_log("[WARN] Memory usage high");
    return 0;
}
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h> // dprintf 사용시 필요할 수 있음

#define PID_FILE "/var/run/myapp.pid"

int main() {
    // 1. PID 파일 열기 (O_EXCL: 이미 있으면 실패)
    int fd = open(PID_FILE, O_WRONLY | O_CREAT | O_EXCL, 0644);
    
    if (fd == -1) {
        if (errno == EEXIST) {
            fprintf(stderr, "[Error] 프로그램이 이미 실행 중입니다! (PID 파일 존재)\\n");
            exit(1);
        }
        perror("open failed"); // 권한 문제 등 다른 에러
        exit(1);
    }

    // 2. 내 PID 기록
    dprintf(fd, "%d\\n", getpid());
    
    // 3. 실행 상태 유지 (테스트를 위해 무한 대기)
    printf("프로그램 시작됨. (PID: %d)\\n", getpid());
    printf("종료하려면 'kill %d' 또는 Ctrl+C를 누르세요.\\n", getpid());
    
    sleep(1);

    // (참고) 강제 종료 시 이 부분은 실행 안 됨 -> 파일이 남음 (단점)

    if (unlink(PID_FILE)==-1){
        perror("unlink failed");
    }
    close(fd);
    return 0;
}
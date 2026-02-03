#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void my_handler(int signo) {
    printf("\n[Handler] 시그널 %d번 처리 시작 (3초 소요)...\n", signo);
    printf("[Handler] 이 동안에는 Ctrl+\\ (SIGQUIT)을 눌러도 대기합니다.\n");
    
    for (int i = 0; i < 3; i++) {
        printf("... 처리 중 %d\n", i + 1);
        sleep(1);
    }
    printf("[Handler] 처리 완료.\n");

    siginfo_t info;
    info.si_pid=0;

    
}

int main() {
    struct sigaction act;

    // 1. 핸들러 함수 지정
    act.sa_handler = my_handler;

    // 2. 마스크 설정 (핸들러 실행 중 막을 시그널)
    sigemptyset(&act.sa_mask);
    sigaddset(&act.sa_mask, SIGQUIT); // SIGINT 처리 중엔 SIGQUIT을 블록함!

    // 3. 플래그 설정
    // SA_RESTART: 시그널 처리 후 중단된 시스템 콜(read, write 등)을 자동 재시작
    act.sa_flags = SA_RESTART; 

    // 4. 등록
    if (sigaction(SIGINT, &act, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("PID: %d\n", getpid());
    printf("Ctrl+C를 눌러보세요. 핸들러 실행 중에 Ctrl+\\도 눌러보세요.\n");

    while (1) {
        printf("Main Loop...\n");
        sleep(1);
    }
    return 0;
}
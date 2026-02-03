#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// SA_SIGINFO 플래그를 사용할 때의 핸들러 형식
void detailed_handler(int sig, siginfo_t *info, void *ucontext) {
    printf("\n[Signal Received] 번호: %d\n", sig);
    
    // 1. 누가 보냈는가?
    printf(" - 보낸 프로세스 PID: %d\n", info->si_pid);
    printf(" - 보낸 사용자 UID: %u\n", info->si_uid);

    // 2. 왜 보냈는가? (si_code 분석)
    printf(" - 발생 원인 코드: %d ", info->si_code);
    
    if (info->si_code == SI_USER) {
        printf("(사용자가 kill이나 raise로 직접 전송)\n");
    } else if (info->si_code == SI_KERNEL) {
        printf("(커널에서 전송)\n");
    } else {
        printf("(기타 사유)\n");
    }
}

int main() {
    struct sigaction sa;

    // 구조체 초기화
    sa.sa_sigaction = detailed_handler; // 상세 정보를 받는 핸들러 연결
    sigemptyset(&sa.sa_mask);           // 핸들러 실행 중 블록할 시그널 없음
    sa.sa_flags = SA_SIGINFO;           // 상세 정보 사용 플래그 설정

    // SIGINT(Ctrl+C)에 대해 sigaction 설정
    if (sigaction(SIGINT, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("현재 프로세스 PID: %d\n", getpid());
    printf("Ctrl+C를 누르거나, 다른 터미널에서 'kill -2 %d'를 입력하세요.\n", getpid());

    // 시그널 대기
    while (1) {
        sleep(1);
    }

    return 0;
}
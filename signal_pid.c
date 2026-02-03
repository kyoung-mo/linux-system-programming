#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 핸들러에서 메모리 할당 시도 (절대 금지 행위)
void handler(int signo) {
    // 여기서 malloc이 메인이 잡고 있는 '힙 락'을 기다리다 멈춤
    printf("handler\n");
    void *ptr = malloc(1024); 
    free(ptr);
}

int main() {
    signal(SIGINT, handler);

    printf("Running... (이 코드는 곧 멈춥니다)\n");

    // 자식 프로세스가 시그널 난사
    pid_t pid = getpid();
    if (fork() == 0) {
        while(1) {
            kill(pid, SIGINT);
            usleep(100); // 0.1ms 간격 폭격
        }
    }

    // 메인 루프: 쉴 새 없이 메모리 할당/해제 반복 (락을 계속 잡았다 풀었다 함)
    while(1) {
        void *p = malloc(1024);
        // [데드락 포인트] 
        printf("while\n");
        // malloc이 내부 락을 잡고, 아직 리턴하기 전에 시그널이 오면 -> 사망
        free(p);
    }
    return 0;
}
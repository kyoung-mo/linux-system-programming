#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>

// 시그널 핸들러 함수 (User defined)
void my_handler(int signo) {
    printf("\n[Signal] %d번 시그널을 받았습니다! 죽지 않아요.\n", signo);
    // 보통 여기서 자원 정리나 플래그 설정을 함
}

int main() {
    // 1. 핸들러 등록 (SIGINT 발생 시 my_handler 실행)
    if (signal(SIGINT, my_handler) == SIG_ERR) {
        perror("signal error");
        exit(1);
    }

    // 2. SIGQUIT는 무시하도록 설정 (Ctrl + \)
   for (int i = 0; i < 64; i++)
   {
    if(i!=9)signal(i, my_handler);
   }
   
    

    printf("Running... (Ctrl+C를 눌러보세요. Ctrl+\\는 무시됩니다.)\n");

    while (1) {
        printf(".");
        fflush(stdout);
        sleep(1);
    }
    return 0;
}
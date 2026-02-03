#include <stdio.h>
#include <unistd.h>
#include <signal.h>


void printf_SIG(sigset_t sig){
    int count=1;
    for (int i = 1; i <= 64; i++)
    {
        if(sigismember(&sig, i)==1){
            printf("1");
        }else printf("0");
        if((count%8)==0)printf(" ");
        count++;
    }
    printf("\n");
    
}


int main() {
    sigset_t new_set, old_set;

    // 1. 집합 초기화 및 SIGINT(2번) 추가
    printf_SIG(old_set);

    sigemptyset(&new_set);    
    sigaddset(&new_set, SIGINT);
    printf_SIG(new_set);

    printf("[Start] 중요 작업 시작 전 (Ctrl+C 가능)\n");
    sleep(3);

    printf("[Start] 마스킹처리됨 (Ctrl+C 안됨)\n");
    sigprocmask(0, NULL,&old_set);
    printf_SIG(old_set);

    // 2. 블록 설정 (이제부터 SIGINT는 Pending 큐에 쌓이고 전달 안 됨)
    // old_set에 이전 상태를 백업해둠
    sigprocmask(SIG_BLOCK, &new_set, &old_set); //old_set => 0

    printf_SIG(old_set);
    
    sigprocmask(0, NULL,&old_set); //=> 1

    printf_SIG(old_set);

    printf("\n[Critical Section] 중요 데이터 기록 중... (Ctrl+C 눌러도 안 죽음)\n");
    for(int i=0; i<5; i++) {
        printf("Writing data... %d/5\n", i+1);
        sleep(1); 
    }
    printf("[Critical Section] 완료.\n");

    // 3. 블록 해제 (백업해둔 상태로 복구)
    // 이 시점에 아까 눌렀던 Ctrl+C가 있다면 즉시 배달되어 프로세스 종료됨
    sigprocmask(SIG_SETMASK, &old_set, NULL);
    printf_SIG(old_set);
    printf("\n[End] 작업 끝. (여기까지 출력되면 Ctrl+C 안 누른 것)\n");
    sleep(3);

    return 0;
}
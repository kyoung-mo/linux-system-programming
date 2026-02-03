#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <pthread.h> // 뮤텍스 사용

// 1. 자원을 보호하는 자물쇠 (Mutex)
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void handler(int signo) {
    printf("[Handler] 시그널 수신! 락 획득 시도 중...\n");
    
    // 3. 여기서 멈춤 (DEADLOCK)
    // Main이 이미 락을 가지고 있는데, Handler가 끝나야 Main이 락을 품.
    // 하지만 Handler는 락을 얻어야 끝남. -> 무한 대기
    pthread_mutex_lock(&lock); 
    
    printf("[Handler] 락 획득 성공! (이 메시지는 절대 안 보임)\n");
    pthread_mutex_unlock(&lock);
}

int main() {
    signal(SIGINT, handler);

    printf("[Main] 시작: 락을 겁니다.\n");
    
    // 1. 메인이 락을 잠금
    pthread_mutex_lock(&lock);
    
    printf("[Main] 락 획득함. 이제 시그널을 스스로 보냄 (자살골).\n");
    
    // 2. 락을 쥔 상태에서 시그널 발생 (Ctrl+C를 코드로 누름)
    // 이 순간 하던 일을 멈추고 handler로 점프함
    raise(SIGINT); 

    // 4. 핸들러가 끝나야 여기로 돌아오는데, 핸들러가 멈춰서 못 돌아옴.
    printf("[Main] 락 해제 (이 메시지도 절대 안 보임)\n");
    pthread_mutex_unlock(&lock);

    return 0;
}
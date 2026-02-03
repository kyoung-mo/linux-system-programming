# Linux System Programming

리눅스 시스템 프로그래밍 실습 코드

## 📝 파일 목록

### Signal Handling (시그널 처리)
- `signal.c` - 기본 시그널 처리
- `sig_action.c` - sigaction 사용
- `sig_action_detailed.c` - 상세 시그널 정보
- `signal_lock.c` - 시그널 블로킹
- `signal_pid.c` - PID와 시그널
- `sigset.c` - 시그널 집합 연산

### File I/O (파일 입출력)
- `file_log.c` - 기본 파일 로깅
- `file_log_dprintf.c` - dprintf 사용
- `file_log_snprintf.c` - snprintf 사용
- `dup2.c` - 파일 디스크립터 복제

### Miscellaneous (기타)
- `aslr_check.c` - ASLR 동작 확인
- `pid_lock.c` - PID 파일 잠금
- `main.c` - 메인 예제

## 🔧 컴파일 및 실행
```bash
# 기본 컴파일
gcc program.c -o program
./program

# 디버그 모드
gcc -g program.c -o program
gdb ./program

# 메모리 체크
valgrind --leak-check=full ./program
```

## 📚 주요 개념

### 시그널 처리
```c
// 기본 방법
signal(SIGINT, handler);

// 권장 방법
struct sigaction sa;
sa.sa_handler = handler;
sigaction(SIGINT, &sa, NULL);
```

### 파일 입출력
```c
int fd = open("file.txt", O_WRONLY | O_CREAT, 0644);
write(fd, buffer, size);
close(fd);
```

## 👨‍💻 Author
구영모 (kyoung-mo)

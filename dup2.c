#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main() {
    int fd = open("daemon.out", O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if (fd == -1) {
        perror("open");
        return 1;
    }

    // 화면(1)으로 나갈 출력을 파일(fd)로 바꿔치기
    // 이제 1번 fd는 파일(fd)을 가리킴
    if (dup2(fd, STDOUT_FILENO) == -1) {
        perror("dup2");
        return 1;
    }
    
    // 원본 fd는 필요 없으니 닫음 (복제본이 1번에 살아있음)
    close(fd);

    // printf는 stdout(1번)에 쓰지만, 실제로는 파일에 저장됨
    printf("This message goes to the file, not the screen.\n");
    printf("Redirect success!\n");

    return 0;
}
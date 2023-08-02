#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock <0) {
        perror("socket");
        return 1;
    }

    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(80);
    addr.sin_addr.s_addr = inet_addr("0.0.0.0");


    int ret_b = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
    if (ret_b < 0){
        perror("bind");
        return 1;
    }


    int ret_l = listen(sock, SOMAXCONN);
    if (ret_l < 0) {
        perror("listen");
        return 1;
    }

    while(1) {

        int clisock = accept(sock, NULL, NULL);
        if (clisock < 0) {
            perror("accept");
            return 1;
        }

        char buf[1024] = {0};


        int read_size = read(clisock, buf, sizeof(buf));
        if (read_size <0) {
            perror("read");
            return 1;
        }

        char *res;
        if(strstr(buf, "GET / HTTP/1.1")) {
            res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<html><h1>helloworld</h1></html>\r\n\r\n";
        }
        else if(strstr(buf, "GET /close HTTP/1.1")){
            break;
        }


        //sudo ./test
        //fuser -k 80/tcp

        else if(strstr(buf, "GET /3week HTTP/1.1")){ //fopen 이용  http://3.36.111.77/
            //res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML><html><head><meta charset='UTF-8'><title> 스터디 html 정리 1주차 </title></head><body><h1>하계 방학 스터디 1주차 html 단어정리</h1><h2>1.1 RDP정의와 공격</h2><p><b>RDP (Remote Desktop Protocol)</b></p><p><b>원격 데스크톱 프로토콜(RDP)</b>은 Microsoft에서 개발한 사유 프로토콜이며, 다른 컴퓨터에 GUI를 제공하는 프로토콜이다.</p><P>기본적으로 TCP 포트 3389를 사용한다.</P><p>원격으로 컴퓨터를 제어 가능하다는 점이 해커들의 공격에 있어 취약점을 가지고, 기본적으로 사용되는 포트값을 통해 쉽게 공격받는다는 단점을 가진다.</p></body></html>\r\n\r\n";
            
            res = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML><html><head><meta charset='UTF-8'><title> 스터디 html 정리 3주차 - 1 </title></head><body><h1>하계 방학 스터디 3주차 html 단어정리 - 1</h1><h2>1. GO 언어</h2><p><b>2009년 11월 구글에서 최초로 발표, 이후 2012년 3월에 정식 발표된 프로그래밍 언어</b></p><p>Go 언어는 컴파일 언어지만 컴파일러의 컴파일 속도가 매우 빨라 인터프리터 언어처럼 쓸 수 있다는 점이 있다</p><p>장점으로는 매우 빠른 컴파일 속도로, 인터프리터의 빠른 속도와, 컴파일 언어의 실행 시 퍼포먼스를 둘 다 챙길 수 있다</p><p>그리고 GoRoutine 이라는 비동기 메커니즘을 제공하는데 이 고루틴은 각각의 고루틴을 병렬로 동작하여, 이벤트 처리 및 병렬 프로그래밍을 가능하게 함, 심지어 고루틴은 멀티스레드 매커니즘임에도 불구하고, 자체적인 스케줄러에 의해 관리되는 경량 스레드이고, OS에서 관리하는 경량 스레드보다 더 경량이다</p><p>그러나 단점으로는 바이트코드를 생성하는 언어가 아니므로, 바이너리만 배포할 경우 해당 타깃 머신에 맞춰서 각각 컴파일해야 한다. 그렇게 하지 않고서 다중 플랫폼을 지원하려면 소스 코드째로 배포해야 한다.</p><p>GO 언어는 'GO'라는 이름으로 검색하기엔 쓰이는 단어가 존재해서 보통 Golang 으로 검색하거나 발음한다</p><p>GO 언어 사용자들을 고퍼(Gopher) 이라고 하며, 이러한 고퍼들을 위한 연례행사인 고퍼콘(GopherCon)이 세계 각국에서 매년 열림</p><h2>2. RUST 언어</h2><p><b>러스트 재단에서 개발되고 있는 메모리 안전성과 성능 및 편의성에 중점을 둔 프로그래밍 언어</b></p><p>가비지 컬렉터 없이 메모리 안전성을 제공하는 대표적인 언어로, C++의 대체재로써 등장했다.</p><p>이 언어는 모질라 재단에서 2010년 7월 7일 처음 발표했으며, 2015년 5월 15일 안정 버전이 정식 발표되었다.</p><p>Rust 언어는 현대적인 시스템 프로그래밍 언어로 C/C++과 동등한 수준의 속도를 유지하면서 안전성&동시성을 향상시키는 것을 목표로 설계되었다.</p><p>이 언어의 특징으로는 안전한 메모리를 관리하기 위해, 무분별한 참조를 막는 제약이 존재하고, 안전성과 성능을 고려하기 위해 소유권(ownership)과, 수명 파라메터(lifetime parameter)라는 개념이 존재한다.</p><ul><li><p>소유권(ownership) : 객체의 생성과 소멸을 관리하기 위한 개념</p></li><li><p>수명 파라메터(lifetime parameter) : 컴파일러가 참조자의 유효성을 검증할 수 있도록 하기 위한 개념</p></li></ul><p>그리고 모든 변수의 가변성을 명확하게 컴파일 타임에 구분한다는 특징이 있다.</p><p>또, 비동기 프로그래밍을 지원하고 있다.</p><p>추가로 C++, C#, Java 등 대중적인 정적 타입 프로그래밍 언어들에서 흔히 제공되는 일반화 프로그래밍 (Generic Programming) 패러다임을, 제네릭이라는 기능으로 제공한다.</p><p>개발자들 사이에서 배우고 싶은 언어로 상위권에 랭크할 정도로 많은 관심을 받고 있다.</p><h2>3. gdb</h2><p><b>GDB(GNU Debugger)는 GNU 소프트웨어 시스템을 위한 기본 디버거</b></p><p>1988년 리처드 스톨만이 처음 작성하였고, 컴퓨터 프로그램의 실행을 추적하고 수정할 수 있는 많은 기능들을 제공한다.</p><p>이러한 기능들은 매우 많기 때문에 축약한다면</p><ul><li><p>프로그램을 시작, 프로그램의 동작에 영향을 줄 수 있는 것을 지정</p></li><li><p>지정된 조건에서 프로그램 중지</p></li><li><p>프로그램이 중지 되었을 떄, 어떤 일이 벌어졌는 지 확인</p></li><li><p>프로그램의 내용을 변경하여 버그를 수정 및 다른 버그에 대해 알아보는 실험을 계속 할 수 있음</p></li></ul><p>이렇게 4가지로 요약이 가능하다.</p>\r\n\r\n";
        }

        else {
            res = "HTTP/1.1 404 Not Found\r\nContent-Type: text/html\r\n\r\n<html><h1>404 Not Found</h1></html>\r\n\r\n";
        }
        write(clisock, res, strlen(res));

        close(clisock);
    }

    close(sock);
    printf("Server closed\n");

    return 0;
}

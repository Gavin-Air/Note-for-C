#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <conio.h>
#include <stdio.h>
#include <WinSock2.h>
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	if (WSAStartup(sockVersion, &wsadata)) {
		printf("WSAStartup failed \n");
		return -1;
	}
	SOCKET cilent = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
	sin.sin_port = htons(8086);
	if (connect(cilent, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR) {
		closesocket(cilent);
		printf("Connecting error.");
		return -1;
	}
	char send_data[] = "114514 1919810 666";
	char* rev_data = (char*)calloc(256, sizeof(char));
	recv(cilent, rev_data, 256, 0);
	printf("%s\n", rev_data);
	send(cilent, send_data, strlen(send_data), 0);
	closesocket(cilent);
	WSACleanup();
	printf("Press any key to exit.");
	_getch();
	return 0;
}
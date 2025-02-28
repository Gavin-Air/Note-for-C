#define _CRT_SECURE_NO_WARNINGS
#define _WINSOCK_DEPRECATED_NO_WARNINGS

#pragma comment(lib,"ws2_32.lib")
#include <stdio.h>
#include <WinSock2.h>
int main()
{
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsadata;
	//std::cout << WSAStartup(sockVersion, &wsadata);
	if (WSAStartup(sockVersion, &wsadata)) {
		printf("WSAStartup failed. \n");
		return -1;
	} //Windows下特有的初始化，没啥理解的意义。
	SOCKET server_listen = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_listen == INVALID_SOCKET) {
		printf("Socket failed. \n");
		return -1;
	}
	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = PF_INET;
	sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); 
	sin.sin_port = htons(8086);
	if (bind(server_listen, (sockaddr*)&sin, sizeof(sin)) == SOCKET_ERROR || listen(server_listen, 6) == SOCKET_ERROR) {
		printf("Socket bind or listen failed.\n");
		closesocket(server_listen);
		WSACleanup();
		return -1;
	} //注意，这里a||b会先执行a，若a成立则不执行b，恰好符合我们程序的需求。
	SOCKADDR_IN sa; //用SOCKADDR也行
	int sa_len = sizeof(sa);
	memset(&sa, 0, sa_len);
	char* send_data = (char*)calloc(256, sizeof(char));
	char* rev_data = (char*)calloc(256, sizeof(char));
	SOCKET server; //会话用SOCKET
	for (int i = 8; i >= 0; --i) { //这里理论上来说是无限循环，这里为了测试就让他只能接受8次。
		server = accept(server_listen, (sockaddr*)&sa, &sa_len);
		sprintf(send_data, "Hi, how can I help with?\nHere are %d seats left.", i);
		if (send(server, send_data, strlen(send_data), 0) == SOCKET_ERROR) {
			closesocket(server);
			continue;
		} //注意端口号一定要用无符号数输出
		printf("Cilent comes from %s:%hu.\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
		recv(server, rev_data, 256, 0);
		printf("%s\n\n", rev_data);
		closesocket(server);
	}
	closesocket(server_listen);
	WSACleanup();
	return 0;
}
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
	} //Windows�����еĳ�ʼ����ûɶ�������塣
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
	} //ע�⣬����a||b����ִ��a����a������ִ��b��ǡ�÷������ǳ��������
	SOCKADDR_IN sa; //��SOCKADDRҲ��
	int sa_len = sizeof(sa);
	memset(&sa, 0, sa_len);
	char* send_data = (char*)calloc(256, sizeof(char));
	char* rev_data = (char*)calloc(256, sizeof(char));
	SOCKET server; //�Ự��SOCKET
	for (int i = 8; i >= 0; --i) { //������������˵������ѭ��������Ϊ�˲��Ծ�����ֻ�ܽ���8�Ρ�
		server = accept(server_listen, (sockaddr*)&sa, &sa_len);
		sprintf(send_data, "Hi, how can I help with?\nHere are %d seats left.", i);
		if (send(server, send_data, strlen(send_data), 0) == SOCKET_ERROR) {
			closesocket(server);
			continue;
		} //ע��˿ں�һ��Ҫ���޷��������
		printf("Cilent comes from %s:%hu.\n", inet_ntoa(sa.sin_addr), ntohs(sa.sin_port));
		recv(server, rev_data, 256, 0);
		printf("%s\n\n", rev_data);
		closesocket(server);
	}
	closesocket(server_listen);
	WSACleanup();
	return 0;
}
#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>
#include <locale.h>

#include "Prototype.h"
#include "Distinguish.h"

//���M�֐�
BOOL send(HWND hEditAddr, HWND hEditMsg) {
    WCHAR editAdd[2048];
    WCHAR editMsg[2048];
    GetWindowText(hEditAddr, editAdd, 2048);
    GetWindowText(hEditMsg, editMsg, 2048);
    // �\�P�b�g�ʐMwinsock�̗����グ
    // wsaData�̓G���[�擾���Ɏg�p����
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);

    // socket�쐬
    // socket�͒ʐM�̏o����� ������ʂ��ăf�[�^�̂���������
    // socket(�A�h���X�t�@�~��, �\�P�b�g�^�C�v, �v���g�R��)
    SOCKET sock;
    sock = socket(AF_INET, SOCK_DGRAM, 0);

    char inputAddr[2048] = { '\0' };
    char inputMsg[2048] = { '\1' };

    size_t inputMsgLen;
    errno_t errMsg = 0;
    setlocale(LC_ALL, "japanese");
    errMsg = wcstombs_s(&inputMsgLen, inputMsg, 256, editMsg, 256);

    size_t inputAddrLen;
    errno_t errAddr = 0;

    setlocale(LC_ALL, "japanese");
    errAddr = wcstombs_s(&inputAddrLen, inputAddr, 256, editAdd, 256);

    // �A�h���X���i�[
    struct sockaddr_in addr;
    // IPv4
    addr.sin_family = AF_INET;
    // �ʐM�|�[�g�ԍ��ݒ�
    addr.sin_port = htons(12345);
    // ���M�A�h���X����͂����l�ɐݒ�
    addr.sin_addr.S_un.S_addr = inet_addr(inputAddr);

    // ���M
    // sendto(�\�P�b�g, ���M����f�[�^, �f�[�^�̃o�C�g��, �t���O, �A�h���X���, �A�h���X���̃T�C�Y);
    sendto(sock, inputMsg, sizeof(inputMsg), 0, (struct sockaddr*)&addr, sizeof(addr));

    return TRUE;
}
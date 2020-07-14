#pragma comment(lib, "ws2_32.lib")

#include <Windows.h>
#include <locale.h>

#include "Prototype.h"
#include "Distinguish.h"

//送信関数
BOOL send(HWND hEditAddr, HWND hEditMsg) {
    WCHAR editAdd[2048];
    WCHAR editMsg[2048];
    GetWindowText(hEditAddr, editAdd, 2048);
    GetWindowText(hEditMsg, editMsg, 2048);
    // ソケット通信winsockの立ち上げ
    // wsaDataはエラー取得等に使用する
    WSAData wsaData;
    WSAStartup(MAKEWORD(2, 0), &wsaData);

    // socket作成
    // socketは通信の出入り口 ここを通してデータのやり取りをする
    // socket(アドレスファミリ, ソケットタイプ, プロトコル)
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

    // アドレス等格納
    struct sockaddr_in addr;
    // IPv4
    addr.sin_family = AF_INET;
    // 通信ポート番号設定
    addr.sin_port = htons(12345);
    // 送信アドレスを入力した値に設定
    addr.sin_addr.S_un.S_addr = inet_addr(inputAddr);

    // 送信
    // sendto(ソケット, 送信するデータ, データのバイト数, フラグ, アドレス情報, アドレス情報のサイズ);
    sendto(sock, inputMsg, sizeof(inputMsg), 0, (struct sockaddr*)&addr, sizeof(addr));

    return TRUE;
}
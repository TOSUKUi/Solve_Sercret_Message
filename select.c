int sock1, sock2;
struct sockaddr_in addr1, addr2;
fd_set fds, readfds;
char buf[2048];

/* ファイルディスクリプタの最大値を計算します。selectで使います */
int maxfd;

/* 受信ソケットを2つ作ります */
sock1 = socket(AF_INET, SOCK_DGRAM, 0);
sock2 = socket(AF_INET, SOCK_DGRAM, 0);

addr1.sin_family = AF_INET;
addr2.sin_family = AF_INET;

addr1.sin_addr.s_addr = inet_addr("127.0.0.1");
addr2.sin_addr.s_addr = inet_addr("127.0.0.1");

/* 2つの別々のポートで待つために別のポート番号をそれぞれ設定します */
addr1.sin_port = htons(11111);
addr2.sin_port = htons(22222);

/* 2つの別々のポートで待つようにbindします */
bind(sock1, (struct sockaddr *)&addr1, sizeof(addr1));
bind(sock2, (struct sockaddr *)&addr2, sizeof(addr2));

/* fd_setの初期化します */
FD_ZERO(&readfds);

/* selectで待つ読み込みソケットとしてsock1を登録します */
FD_SET(sock1, &readfds);
/* selectで待つ読み込みソケットとしてsock2を登録します */
FD_SET(sock2, &readfds);

/* selectで監視するファイルディスクリプタの最大値を計算します */
if (sock1 > sock2) {
  maxfd = sock1;
 } else {
  maxfd = sock2;
 }

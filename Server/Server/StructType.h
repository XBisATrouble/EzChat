//定义结构体类型

typedef struct
{
	int nType; //为0
	char cID[10];//账号ID
	char cPWD[10];//密码
}LOGIN;

typedef struct
{
	int nType; //为1
	char RevID[10];//接收者的ID
	char SendID[10];//发送者的ID
	char SendMsg[512];//发送的信息
}DATECHAT;
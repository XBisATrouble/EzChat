//����ṹ������

typedef struct
{
	int nType; //Ϊ0
	char cID[10];//�˺�ID
	char cPWD[10];//����
}LOGIN;

typedef struct
{
	int nType; //Ϊ1
	char RevID[10];//�����ߵ�ID
	char SendID[10];//�����ߵ�ID
	char SendMsg[512];//���͵���Ϣ
}DATECHAT;
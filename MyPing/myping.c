/*
 * @FileName: myping.c
 * @Author: wzj
 * @Brief: 
 *  
 *	easy ping, from ibm developer  
 *  
 *  
 *  
 * @History: 
 * 
 * 
 * 
 * @Date: 2012年01月31日星期二23:30:20
 * 
 */ 
#include<stdio.h>
#include<signal.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netinet/ip.h>
#include<netinet/ip_icmp.h>
#include<netdb.h>
#include<setjmp.h>
#include<errno.h>

#define PACKET_SIZE		(4096)
#define MAX_WAIT_TIME	(5)
#define MAX_NO_PACKETS	(3)

char sendpacket[PACKET_SIZE];
char recvpacket[PACKET_SIZE];
int sockfd, datalen = 56;
int nsend = 0, nreceived = 0;
struct sockaddr_in dest_addr;
pid_t pid;
struct sockaddr_in from;
struct timeval tvrecv;

//发送icmp报文
void send_packet(void);
//设置icmp报头
int pack(int pack_no);
//计算校验和
unsigned short cal_chksum(unsigned short *addr, int len);
//接受所有ICMP报文
void recv_packet();
//解析收到的报文
int unpack(char* buf, int len);
//计算时间差
void tv_sub(struct timeval *out, struct timeval *in);
//进行统计
void statistics(int signo);

int main(int argc, char *argv[])
{
	struct hostent *host;
	struct protoent *protocol;
	unsigned long inaddr = 0l;
	int waittime = MAX_WAIT_TIME;
	int size = 50*1024;
	
	if(argc < 2)
	{
		printf("usage: %s hostname/IP address\n", argv[0]);
		exit(1);
	}

	if((protocol = getprotobyname("icmp")) == NULL)
	{
		perror("getprotobyname");
		exit(1);
	}
	//生成ICMP的原始套接字，只有root才有权限
	//bug ... 注意，运算符号优先级，< 与 =号
	if((sockfd = socket(AF_INET, SOCK_RAW, protocol->p_proto)) < 0)
	{
		perror("socket error");
		exit(1);
	}
	//收回root权限
	setuid(getuid());
	/*扩大套接字接受缓冲区到50k，减小接受缓冲区溢出的可能，
	如果无意中ping了一个广播地址，或者多播地址，会引来大量应答*/
	setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &size, sizeof(size));
	bzero(&dest_addr, sizeof(dest_addr));
	dest_addr.sin_family = AF_INET;
	//判断是主机名还是ip地址
	if(inaddr = inet_addr(argv[1]) == INADDR_NONE)
	{
		if((host = gethostbyname(argv[1])) == NULL)
		{
			perror("gethostbyname error");
			exit(1);
		}
		memcpy((char*)&dest_addr.sin_addr, host->h_addr, host->h_length);
	} else {//是ip地址
		memcpy((char*)&dest_addr.sin_addr, (char*)&inaddr, sizeof(inaddr));
	}

	//获取main的进程id用于设置icmp的标志符号
	pid = getpid();
	printf("PING %s(%s): %d bytes data in ICMP packets.\n", argv[1],
			inet_ntoa(dest_addr.sin_addr), datalen);
	send_packet();	//发送icmp报文
	printf("...");
	recv_packet();	//接收icmp报文
	statistics(SIGALRM);//进行统计
	
	return 0;
}
//发送三个icmp报文
void send_packet()
{
	int packetsize;

	while(nsend < MAX_NO_PACKETS)
	{
		nsend++;
		packetsize = pack(nsend); //设置ICMP抱头
		if (sendto(sockfd, sendpacket, packetsize,0,
					(struct sockaddr *)&dest_addr, sizeof(dest_addr)) < 0)
		{
			perror("sendto error");
			continue;
		}
		sleep(1);
	}
}
//设置icmp报头
int pack(int pack_no)
{
	int i, packsize;
	struct icmp *icmp;
	struct timeval *tval;

	icmp = (struct icmp*)sendpacket;
	icmp->icmp_type = ICMP_ECHO;
	icmp->icmp_code = 0;
	icmp->icmp_cksum = 0;
	icmp->icmp_seq = pack_no;
	icmp->icmp_id = pid;
	packsize = 8 + datalen;
	tval = (struct timeval*) icmp->icmp_data;
	gettimeofday(tval, NULL); //记录发送时间
	icmp->icmp_cksum = cal_chksum((unsigned short*)icmp, packsize);

	return packsize;
}
//计算校验和
unsigned short cal_chksum(unsigned short *addr, int len) 
{
	int nleft = len;
	int sum = 0;
	unsigned short *w = addr;
	unsigned short answer = 0;

	if(addr == NULL)
	{
		printf("addr == NULL");
	}

	//把ICMP报头二进制数据以2字节为单位累加起来
	while(nleft > 1)
	{
		sum += *w;
		w++;
		nleft -= 2;
	}
	//如果有奇数个字节会剩下最后一个字节，
	//把最后一个字节视为一个2字节数据的搞字节，
	//这个2字节数据的低字节为0。
	if (nleft == 1)
	{
		*(unsigned char*)(&answer) = *(unsigned char*) w; 
		sum += answer;
	}
	sum = (sum >> 16) + (sum & 0xffff);
	sum += (sum >> 16);
	answer = ~sum;

	return answer;
}
//接受所有报文
void recv_packet()
{
	int n, fromlen;
	extern int errno;
	signal(SIGALRM, statistics);
	fromlen = sizeof(from);

	while ( nreceived < nsend)
	{	//之前的时钟会被刷新。
		alarm(MAX_WAIT_TIME);
		if ((n = recvfrom(sockfd, recvpacket, sizeof(recvpacket), 0, \
				(struct sockaddr *)&from, &fromlen)) < 0)
		{
			if (errno == EINTR)
				continue;
			perror("recvfrom error");
			continue;
		}
		gettimeofday(&tvrecv, NULL); //记录接受时间
		if(unpack(recvpacket, n) == -1)
			continue;
		nreceived++;
	}
}
//解析收到的报文
//剥离ICMP报头
int unpack(char *buf, int len)
{
	int i, iphdrlen;
	struct ip *ip;
	struct icmp *icmp;
	struct timeval *tvsend;
	double rtt;

	ip = (struct ip*) buf;
	iphdrlen = ip->ip_hl << 2; 	//求ip报头长度， 即ip报头的长度标志*4
	icmp = (struct icmp *)(buf + iphdrlen);	//越过ip报头，指向icmp报头
	len -= iphdrlen;			//icmp + icmp 数据
	if (len < 8) 	//小于icmp报头长度不合理
	{
		printf("ICMP packets\'s length is less than 8\n");
		return -1;
	}
	//确保接受的使我所发送的icmp回应
	if ((icmp->icmp_type == ICMP_ECHOREPLY) && (icmp->icmp_id == pid))
	{
		//回应一个时间戳?不是，是发送什么数据，返回什么数据
		tvsend = (struct timeval *)icmp->icmp_data;
		tv_sub(&tvrecv, tvsend); //接收和发送的时间差
		rtt= tvrecv.tv_sec*1000 + tvrecv.tv_usec/1000;	//毫秒为单位
		//显示相关信息
		printf("%d byte from %s: icmp_seq=%u ttl=%d rtt=%.3fms\n", \
				len,
				inet_ntoa(from.sin_addr),
				icmp->icmp_seq,
				ip->ip_ttl,
				rtt);
	}
	else 
		return -1;
}

//计算时间差
void tv_sub(struct timeval *out, struct timeval *in)
{
	if ((out->tv_usec -= in->tv_usec) < 0)
	{
		--out->tv_sec;
		out->tv_usec += 1000000;
	}
	out->tv_sec -= in->tv_sec;
}
//中断?...
void statistics(int signo)
{
	printf("\n----------------PING statistics----------------\n");
	printf("%d packets transmitted. %d received, %%%d lost\n", nsend, nreceived, (nsend-nreceived)/nsend*100);
	close(sockfd);
	exit(1);
}

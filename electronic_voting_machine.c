#include<reg51.h> 
#define lcdport P2 
sbit rs=P3^0;
sbit rw=P3^1; 
sbit en=P3^2; 
sbit start=P1^0; 
sbit stop=P1^5;
sbit party1=P1^1;	//Candidate 1
sbit party2=P1^2;		//Candidate 2 
sbit party3=P1^3;	//Candidate 3
sbit party4=P1^4;	//Candidate 4

void lcdcmd(unsigned char); 
void lcdint();
void lcddata(unsigned char); 
void lcdstring(unsigned char *); 
void delay(unsigned int);
void longdelay(unsigned int); 
void display_vote(unsigned int);
void display_percent(unsigned int); 
void count();
void result(); 
void check(); 
void check1();
unsigned int vote1,vote2,vote3,vote4 ; 
char vote_no[4] ;

void main()
{
lcdport=0x00;
party1=party2=party3=party4=0;
vote1=vote2=vote3=vote4=0; 
start=stop=0;
lcdcmd(0x01);  
lcdint(); 
lcdstring("Press start"); 
lcdcmd(0xc0);
 


lcdstring("To initiate");	//declaring P2 as output port while(1)
{
if (start==1)
{
lcdcmd(0x84); lcdcmd(0x01); lcdstring("Welcome!!"); longdelay(200); lcdcmd(0x01); lcdstring("Press any key"); lcdcmd(0xc0); lcdstring("to vote"); longdelay(200); lcdcmd(0x01); lcdstring("BJP"); delay(500);  lcdcmd(0x84); lcdstring("CNG"); delay(500);  lcdcmd(0x88); lcdstring("AAP"); delay(500); lcdcmd(0x8C); lcdstring("JDU");
count(); lcdcmd(0x01);
lcdcmd(0x80); lcdstring("Thank you");
longdelay(300); check();
}
}

}
void check()
{
if(party1==0&&party2==0&&party3==0&&party4==0)
{
if(stop!=0)
{
while(1)
{
 


result();
}
}
}
}
void result()
{
int max=0,flag=0; lcdcmd(0x01); lcdstring("BJP"); delay(500); lcdcmd(0x84); lcdstring("CNG"); delay(500); lcdcmd(0x88); lcdstring("AAP"); delay(500);; lcdcmd(0x8C); lcdstring("JDU"); lcdcmd(0xc0); display_vote(vote1); lcdcmd(0xc4); display_vote(vote2); lcdcmd(0xc8); display_vote(vote3); lcdcmd(0xcc); display_vote(vote4); if(vote1>max)
{
max=vote1;
}
if(vote2>max)
{
max=vote2;
}
if(vote3>max)
{
max=vote3;
}
if(vote4>max)
{
max=vote4;
}
 


 



 
longdelay(500);
if((vote1 == max) && (vote2 != max) && (vote3 != max) && (vote4 !=max))

{
flag = 1; lcdcmd(0x01); lcdcmd(0x80); lcdstring("BJP"); lcdcmd(0xc5); lcdstring("Wins"); longdelay(200); lcdcmd(0x01); lcdcmd(0x80);
lcdstring("no. of votes won"); lcdcmd(0xc0); display_vote(vote1); display_percent(vote1); longdelay(500);
 



 
}
if((vote2 == max) && (vote1 != max) && (vote3 != max) && (vote4 !=max))

{
flag = 1; lcdcmd(0x01); lcdcmd(0x80); lcdstring("CONG"); lcdcmd(0xc5); lcdstring("Wins"); longdelay(200); lcdcmd(0x01); lcdcmd(0x80);
lcdstring("no. of votes won"); lcdcmd(0xc0); display_vote(vote2); display_percent(vote2); longdelay(500);
 



 
}
if((vote3 == max) && (vote2 != max) && (vote1 != max) && (vote4 !=max))

{
flag = 1; lcdcmd(0x01); lcdcmd(0x80);
 


lcdstring("AAP"); lcdcmd(0xc5); lcdstring("Wins"); longdelay(200); lcdcmd(0x01); lcdcmd(0x80);
lcdstring("no. of votes won"); lcdcmd(0xc0); display_vote(vote3); display_percent(vote3); longdelay(500);
}
 


 
if((vote4 == max) && (vote2 != max) && (vote1 != max) && (vote3 !=max))

{
flag = 1; lcdcmd(0x01); lcdcmd(0x80); lcdstring("JDU"); lcdcmd(0xc5); lcdstring("Wins"); longdelay(200); lcdcmd(0x01); lcdcmd(0x80);
lcdstring("no. of votes won"); lcdcmd(0xc0); display_vote(vote4); display_percent(vote4); longdelay(500);
 
}
if(flag==0)
{
lcdcmd(0x01); lcdcmd(0x80); lcdstring("clash between"); lcdcmd(0xc0); 
	if(vote1==max)
{
lcdstring("BJP,");
}
if(vote2==max)
{
lcdstring("CONG,");
 


}
if(vote3==max)
{
lcdstring("AAP,");
}
if(vote4==max)
{
lcdstring("JDU");
}
longdelay(200); lcdcmd(0x01); lcdcmd(0x80);
lcdstring("no. of votes won"); lcdcmd(0xc0); display_vote(max); display_percent(max); longdelay(500);
}
}
void display_vote(unsigned int vote) //Function to read 0-9 character values
{
int k,p; for(k=0;k<=2;k++)
{
vote_no[k]=vote%10; vote=vote/10;
}
for(p=2;p>=0;p--)
{
lcddata(vote_no[p]+48);
}
}
void display_percent(unsigned int vote)
{
int i;
int per1; int p; int sum;
char per[2];
sum=vote1+vote2+vote3+vote4; per1=(vote*100/sum); 
	for(i=0;i<=2;i++)
{
 


per[i]=per1%10; per1=per1/10;
}
lcdcmd(0xc4); for(p=2;p>=0;p--)
{
lcddata(per[p]+48);
}
lcdcmd(0xc7); lcdstring("percent");
}
void count() //count voice
{
while(party1==0&&party2==0&&party3==0&&party4==0); if (party1==1)
{
lcdcmd(0x01); lcdcmd(0x80);
vote1 = vote1+1; lcdstring("VOTED:BJP"); longdelay(300);
}
if (party2==1)
{
lcdcmd(0x01); lcdcmd(0x80); vote2 = vote2+1;
lcdstring("VOTED:CONG"); longdelay(300);
}
if (party3==1)
{
lcdcmd(0x01); lcdcmd(0x80);
vote3 = vote3+1; lcdstring("VOTED:AAP"); longdelay(300);
}
if (party4==1)
{
lcdcmd(0x01); lcdcmd(0x80); vote4 = vote4+1;
 


lcdstring("VOTED:JDU"); longdelay(300);
}
}

void delay(unsigned int x)
{
unsigned int i; for(i=0;i<x;i++);
}

void longdelay(unsigned int u)
{
unsigned int i,j; for(i=0;i<u;i++) for(j=0;j<1275;j++);
}

void lcdint()
{
lcdcmd(0x38); delay(500); lcdcmd(0x01); delay(500); lcdcmd(0x0c); delay(500); lcdcmd(0x80); delay(500); lcdcmd(0x0e); delay(500);
}
void lcdcmd(char value)
{
lcdport = value; rw=0;
rs=0; en=1;
delay(500); en=0;
}
void lcdstring(char *p)
{
 while(*p!='\0')
 


{
lcddata(*p); 
	delay(2000); 
	p++;
}
}
void lcddata(unsigned char value)
{
lcdport = value; rs=1;
rw=0; en=1; delay(500); en=0;
}

#include<stdio.h>
#include<sqlite3.h>
#include<stdlib.h>
#include<string.h>
char flag[100];

static int checkTable_Callback(void *unnecessary,int noc,char **val,char **lab){
	printf("Count(*) %s\t=>%s\n",lab[0],val[0]);
	return  0;
}
static int callback(void *NotUsed,int argc,char **argv,char **azColName)
{
	int i;
	for(i=0;i<argc;i++)
	{
		printf("%s=%s\n",azColName[i],argv[i] ? argv[i]:"NULL");
	}
	printf("\n");
	return(0);
}
static int callback2(void *data,int argc,char **argv,char **azColName)
{
	int i;
	printf("%s:",(const char*)data);
	for(i=0;i<argc;i++)
	{
	printf("%s=%s\n",azColName[i],argv[i] ? argv[i]:"NULL");
	}
	printf("\n");
	return(0);
}
sqlite3 *db;
void createtable()
{
	char *zErrMsg,*zErrMsgs/*,*zErrMsgss*/=0; // pointer to print error message
 	/*CREATE SQL STATEMENT*/
 	char *sql="CREATE TABLE LIBRARYRECORD("\
	"STUDENTID INT PRIMARY KEY NOT NULL,"\
	"STUDENTNAME TEXT NOT NULL,"\
	"NOOFDAYS INT NOT NULL,"\
	"PENALTY INT,"\
	"MOREBOOKS TEXT);";
	char *sr="CREATE TABLE STUDENTRECORD("\
	"INDEXNO INT PRIMARY KEY NOT NULL,"\
	"STUDENTID INT NOT NULL,"\
	"BOOKNAME TEXT NOT NULL,"\
	"BOOKID INT NOT NULL,"\
	"NOOFBOOKS INT,"\
	"MOREBOOKS TEXT);";
	/*char *s="CREATE TABLE FINALRECORD("\
	"STUDENTID INT PRIMARY KEY NOT NULL,"\
	"STUDENTNAME TEXT NOT NULL,"\
	"NOOFDAYS INT NOT NULL,"\
	"PENALTY INT,"\
	"BOOKNAME TEXT NOT NULL,"\
	"BOOKID INT NOT NULL,"\
	"NOOFBOOKS INT,"\
	"MOREBOOKS TEXT);";*/
	/*EXECUTE SQL STATEMENT*/
	int rc=sqlite3_exec(db,sql,callback,0,&zErrMsg);
	int rcs=sqlite3_exec(db,sr,callback,0,&zErrMsgs);
	//int rcss=sqlite3_exec(db,s,callback,0,&zErrMsgss);
	if((rc && rcs /*&& rcss*/)!=SQLITE_OK)
	{
	printf("SQL ERROR:%s\n",zErrMsg);
	printf("SQL ERROR:%s\n",zErrMsgs);
	//printf("SQL ERROR:%s\n",zErrMsgss);
	//sqlite3_free(zErrMsgss);
	sqlite3_free(zErrMsg);
	sqlite3_free(zErrMsgs);
	}
	else
	{
		printf("TABLE CREATED SUCCESSFULLY\n");
	}
}
void insertintolibrary()
{
	char *zErrmsg,*zErrmsgs=0;
	int rc6,rc61;
	char sql6[1000],sql61[1000];
	char studentname[100];
	int studentid,noofdays,penalty;
	printf("ENTER STUDENTID\n");
	scanf("%d",&studentid);
	printf("ENTER STUDENTNAME\n");
	scanf("%s",studentname);
	printf("ENTER NOOFDAYS\n");
	scanf("%d",&noofdays);
	//printf("ENTER NOOFBOOKS\n");
	//scanf("%d",&noofbooks);
	sprintf(sql6, "INSERT INTO LIBRARYRECORD(STUDENTID,STUDENTNAME,NOOFDAYS) VALUES(%d,'%s',%d)",studentid,studentname,noofdays);
	//sprintf(sql6, "INSERT INTO FINALRECORD(STUDENTID,STUDENTNAME,NOOFDAYS) VALUES(%d,'%s',%d)",studentid,studentname,noofdays);
	rc6=sqlite3_exec(db,sql6,callback,0,&zErrmsg);
	     if(rc6!=SQLITE_OK)
	     {
			printf("SQL ERROR:%s\n",zErrmsg);
			sqlite3_free(zErrmsg);
	     }	
	     else
	     {
			printf("RECORD INSERTED SUCCESSFULLY\n");
	     }
}
void insertintostudent()
{
	char *zErrmsgs=0;
	int rc61;
	char sql61[1000];
	char studentname[100],bookname[100];
	int studentid,bookid,indexno;
	printf("ENTER STUDENTID\n");
	scanf("%d",&studentid);
	printf("ENTER STUDENTNAME\n");
	scanf("%s",studentname);
	printf("ENTER BOOKNAME\n");
	scanf("%s",bookname);
	printf("ENTER BOOKID\n");
	scanf("%d",&bookid);
	//printf("ENTER NOOFBOOKS\n");
	//scanf("%d",&noofbooks);
	printf("ENTER INDEX NO\n");
	scanf("%d",&indexno);
	sprintf(sql61, "INSERT INTO STUDENTRECORD(INDEXNO,STUDENTID,BOOKNAME,BOOKID) VALUES(%d,%d,'%s',%d)",indexno,studentid,bookname,bookid);
	//sprintf(sql61, "INSERT INTO FINALRECORD(INDEXNO,STUDENTID,BOOKNAME,BOOKID) VALUES(%d,%d,'%s',%d)",indexno,studentid,bookname,bookid);
	rc61=sqlite3_exec(db,sql61,callback,0,&zErrmsgs);
	     if(rc61!=SQLITE_OK)
	     {
			printf("SQL ERROR:%s\n",zErrmsgs);
			sqlite3_free(zErrmsgs);
	     }	
	     else
	     {
			printf("RECORD INSERTED SUCCESSFULLY\n");
	     }
}
void tablecreated()
{
	char *zErr,*zErrs=0;
	char *sql5,*sql51;
	int rc5,rc51;
	const char* data="callback2 function called";
	const char* data1="callback2 function called";
	sql5="SELECT * FROM LIBRARYRECORD";
	sql51="SELECT * FROM STUDENTRECORD";
	rc5 =sqlite3_exec(db,sql5,callback2,(void*)data,&zErr);	
	rc51=sqlite3_exec(db,sql51,callback2,(void*)data1,&zErrs);
	if((rc5 && rc51)!=SQLITE_OK)
	{
		printf("SQL ERROR:%s\n",zErr);
		sqlite3_free(zErr);
		printf("SQL ERROR:%s\n",zErrs);
		sqlite3_free(zErrs);
	}
	else
	{
		printf("TABLE CREATED SUCCESSFULLY\n");
	}
}
void penalty()
{
	char *zmsg=0;
	char *sql1;
	int rc1;
	const char* data="callback2 function called";
	sql1="UPDATE LIBRARYRECORD set PENALTY=0 where NOOFDAYS<=7;"\
     	     "UPDATE LIBRARYRECORD set PENALTY=30 where NOOFDAYS>7;"\
             "UPDATE LIBRARYRECORD set MOREBOOKS='YES' where PENALTY==0;"\
	     "UPDATE LIBRARYRECORD set MOREBOOKS='NO' where PENALTY>0;"\
             "SELECT * FROM LIBRARYRECORD";
	     rc1 =sqlite3_exec(db,sql1,callback2,(void*)data,&zmsg);
	     if(rc1!=SQLITE_OK)
	     {
			printf("SQL ERROR:%s\n",zmsg);
			sqlite3_free(zmsg);
	     }
	     else
             {
			printf("TABLE updated SUCCESSFULLY\n");
             }
}
void noofbooks()
{
	char *sql2;
	char *zErrM=0;
	int rc3;
	const char* data="callback2 function called";
	printf("%s",flag);
	sql2="SELECT count(*) FROM STUDENTRECORD where STUDENTID='flag';";
	     //"INSERT INTO STUDENTRECORD SELECT STUDENTRECORD NOOFBOOKS COUNT (*) FROM where STUDENTID=flag;"\
	    /* "UPDATE STUDENTRECORD set MOREBOOKS='NO' where NOOFBOOKS>3;"\*/
	     //"SELECT * FROM STUDENTRECORD"; 
	rc3 =sqlite3_exec(db,sql2,checkTable_Callback,0,NULL);
	if(rc3!=SQLITE_OK)
	{
		printf("SQL ERROR:%s\n",zErrM);
		sqlite3_free(zErrM);
	}
	else
	{
	printf("TABLE updated SUCCESSFULLY\n");
	}
}
int main(int argc,char* argv[])
{
	 int rc2;
	 int choice=0;
	 /* opens database*/
	 rc2=sqlite3_open("libraryproject3.db",&db);
	 if(rc2)
	 {
		   printf("CANT OPEN DATABASE:%s\n",sqlite3_errmsg(db));
		   return(0);
	 }
	 else
	 {
		  printf("OPENED DATABASE\n");
	 }
	createtable();
	printf("DO YOU WANT TO PERFORM OPERATIONS -1 TO EXIT\n");
	scanf("%d",&choice);
	while(choice!=-1)
	{	switch(choice)
		{
			case 1:
				insertintolibrary();
				break;
			case 2:
		  		insertintostudent();
				break;
			case 3:
				tablecreated();
				break;
			case 4:
				penalty();
				break;
			case 5:
				printf("ENTER STUDENT RECORD TO BE CHECKED\n");
				scanf("%s",flag);
				noofbooks();
				break;
		}
		scanf("%d",&choice);
	}	
	sqlite3_close(db);
	return(0);
}


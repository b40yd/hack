#include <stdio.h>
#include <malloc.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>


#define NAME_LEN 20
#define MAIL_LEN 32

#define ERROR(str,err)				\
     do{ printf (str);exit(err);}while(0);

typedef struct HFG
{
     char *name;
     int age;
     char *email;
}hfg ,*hfg_p;

int showinfo(int n);
char show_option_info(void);
char show_options(char n,hfg *p);
int add_data(hfg *p);
int add_name(hfg *p);
int add_age(hfg *p);
int add_email(hfg *p);
int data_write(hfg *p);
int ask_todo(hfg *p,int (*func)(hfg *));
int data_show(hfg *p);
void *hfg_malloc(hfg * p);
void hfg_free(hfg *p);
void search_data(void);
void delete_data(void);

int main(int argc, char *argv[])
{
     hfg *h = NULL;
     char n;
     //char m[20];
     h = (hfg*)hfg_malloc(h);
     showinfo(1);
     show_option_info();
     while((n = tolower(getchar())) != 'q'){
	  if(n == '\n')
	       continue;
	  show_options(n,h);
	  show_option_info();
       
     }	
     hfg_free(h);	
     return 0;
}

void *hfg_malloc(hfg *p){
     p = (hfg *)malloc(sizeof(hfg));
     assert( p!= NULL );
     
     p->name = (char *)malloc(NAME_LEN);
     assert( p->name != NULL );
     
     p->email = (char *)malloc(MAIL_LEN);
     assert( p->email != NULL );

     return p;
}

void hfg_free(hfg * p){
     free(p->email);
     p->email = NULL;

     free(p->name);
     p->name = NULL;

     free(p);
     p = NULL;
}

char show_option_info(void){
  printf ("Please choice options:\n");
  printf ("A : add data options.\t D : delete data options.\n");
  printf ("S : search data options. Q : quit.\n");
  return 1;
}

int add_data(hfg *p){
     int ret = 0;
     
     ret = add_name(p);
     if(ret)
	  ERROR("add_name: alloc mem error!\n",ret);

     ret = add_age(p);
     if(ret)
	  ERROR("add_age: age range error!\n",ret);

     ret = add_email(p);
     if(ret)
	  ERROR("add_email: alloc mem error!\n",ret);
     
     data_show(p);
     ask_todo(p,data_write);

     return 0;
}

int data_show(hfg *p){
     printf ("This is your data:\n");
     printf ("Name: %s",p->name);
     printf ("Age: %d\n",p->age);
     printf ("Email: %s",p->email);
     return 0;
}

int ask_todo(hfg *p,int (func)(hfg *)){
     char sure[4];
     do{
	  printf("sure?(yes/no): ");
	  fscanf(stdin,"%s",sure);
     }while(strcmp(sure,"yes") != 0&&
	    strcmp(sure,"no") != 0);

     return (!strcmp(sure,"yes")) ? func(p) : 0;
}

int data_write(hfg *p){
     FILE *fp = fopen("database.db","aw+");
     if (fp == NULL)
	  ERROR("data_write: file open error!\n",-111);
     //if (sizeof(hfg) !=
     //fwrite(p,sizeof(hfg),1,fp);//)
     fprintf(fp,"Name : %sAge: %d \nEmail: %s",
	     p->name,p->age,p->email);
//ERROR("data_write: file write error!\n",-112);
     fclose(fp);
     return 0;
}

int add_name(hfg *p){
     //char name[NAME_LEN];
     char ch;

     printf ("Please enter member name:");
     while( (ch=fgetc(stdin)) != '\n')
	  ungetc(ch,stdin);

     fgets(p->name ,NAME_LEN,stdin);
     //puts(p->name);
     
     return p->name? 0 : -1;
}

int add_age(hfg *p){
     printf("input your age:");
     fscanf (stdin,"%d",&p->age);
     return (p->age>=18&&p->age<=50)?
	  0:-2;
}

int add_email(hfg *p){
     char ch;
     
     printf ("Please enter email:");
     while( (ch=fgetc(stdin)) != '\n')
	  ungetc(ch,stdin);
     
     fgets(p->email,MAIL_LEN,stdin);
     puts(p->email);
     return p->email ? 0 : -3;
}

/** 
 * show_options functions call function.
 * 
 * @param n 
 * 
 * @call function
 */

char show_options(char n, hfg *p){
     switch(n){
     case 'a':
       //showinfo(1);
	  add_data(p);
	  break;
     default:
	  showinfo(0);break;
	  
     }
}

/** 
 * showinfo functions display message!
 * accept 1 parameter
 * @display message
 */

int showinfo(int n){
     if (1 == n)
     {
	  printf ("Welcome to HFG user statistics table.\n");
	  printf ("Please select you operation options\n");
	  printf ("Version 0.01\n");
     }else if(2 == n){
	  printf ("Thanks!\n");
	  printf ("Bye!\n");
     }else{
	  printf ("Sorry! you enter wrong!\n");
     }
}

/*
 * search_data function will search the insered data from database.db
 * accpet 1 parameter
 * @return a array.
 */
void search_data(void){

}

void delete_data(void){

}
//1、建立数据库
//2、用户输入接口
//3、查询功能
//4、存储数据库


/*
names : KWIZERA ALFRED 23317
        MUGIRANEZA JEANNE D'ARC 23320 
        KANIMBA EDDY 23419 
        
        
         hello sir this is the class project of our group , this project is called NGIRANKUGIRE System  which would help in administration to know if the entered 
individual has been given food or not by only entering his ID it would also help to record people who should be given food 


        
        */








#include<stdio.h>
#include<string.h>

 main() {



    	printf("\n\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");
        printf("    Welcome to NGIRANKUGIRE System ");
        printf("\n\n   \xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\xcd\n");




int q;
do
    {
          printf("\n1. enter a household\n2. dashboard\n3. search\n4. exit\n");
         scanf("%d",&q);
         switch(q)
       {
        case 1:
           enterahousehold();
            break;
        case 2:
           dashboard();
            break;
        case 3:
           search();
            break;
        case 4:
            printf("bye bye!!!!");
            break;
        default:
            printf("wrong choice, try again!!");
       }


    } while(q!=4);

}

struct citizens
{
    int id;
    char fname[30];
    char sname[30];
    char dis[30];
    char sec[30];
    int num;

};

void enterahousehold()
{
    struct citizens cit;
    FILE *p;
    p=fopen("citizens.txt","a");
    printf("ENTER ID NUMBER:");
    scanf("%d",&cit.id);
    printf("ENTER FIRST NAME:");
    scanf("%s",cit.fname);
    printf("ENTER SECOND NAME:");
    scanf("%s",cit.sname);
    printf("ENTER DISTRICT:");
    scanf("%s",cit.dis);
    printf("ENTER SECTOR:");
    scanf("%s",cit.sec);
    printf("ENTEr NUMBER OF PEOPLE:");
    scanf("%d",&cit.num);
    fprintf(p,"%d %s %s %s %s %d\n",cit.id,cit.fname,cit.sname,cit.dis,cit.sec,cit.num);
    fclose(p);

}

 void dashboard()
 {
    struct citizens cit;
    FILE *e;
    e=fopen("citizens.txt","r");
    printf("ID    FIRST NAME   LAST NAME   DISTRICT   SECTOR   NUM\n--    ----------   ---------   --------   ------   ----------------\n");
    while(!feof(e))
    {
        fscanf(e,"%d %s %s %s %s %d\n",&cit.id,cit.fname,cit.sname,cit.dis,cit.sec,&cit.num);
        printf("%d\t%s\t%s\t%s\t%s\t%d\n",cit.id,cit.fname,cit.sname,cit.dis,cit.sec,cit.num);
    }

    fclose(e);

 }

 void search()

 {

    struct citizens cit;
    int no;
    FILE *p;
    p=fopen("citizens.txt","r");
    printf(" enter the citizen ID: ");
    scanf("%d",&no);
    while(!feof(p))

    {
     fscanf(p,"%d %s %s %s %s %d\n",&cit.id,cit.fname,cit.sname,cit.dis,cit.sec,&cit.num);
     if(cit.id==no)
           {
               printf("the household names are %s %s he lives in %s district %s sector and have %d people at home and has been given food ", cit.fname,cit.sname,cit.dis,cit.sec,cit.num);
               return;
           }
    }

    printf("the citizen has not been given food");
    fclose(p);









 }
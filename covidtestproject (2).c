#include<stdio.h>
#include<string.h>
#include <conio.h>
int i=0;
void record();
void displayprov();
void search();
void createuser();
int login();
void statistics();
void dispbydate();
struct covid
{
    char fname[20];
    char lname[20];
    char province[20];
    char district[20];
    char sector[20];
    char cell[20];
    char a[20];
    char nbr[18];
    char status[3];
}rec;
main()
{
    int p,t;
    char c,r[20];
    p=login();
    if(p==0)
    {
        printf("\n\n\t\t\t\t\t TOO MUCH ATTEMPTS!!!!!!!!!\n");
        return;
    }
    printf("\n\n\t\t\t\t\t******************************\n\t\t\t\t\t** WELCOME TO COVID TESTING **\n\t\t\t\t\t******************************\n\nENTER THE DATE OF TODAY\(DD/MM/YY\):");
    scanf("%s",rec.a);
    printf("\n");
    do{
    printf("\nCHOOSE A SERVICE:\n1.RECORD\n2.DISPLAY DATA\n3.SEARCH BY NAME\n4.STATISTICS\n5.CREATE NEW USER\n6.QUIT\nENTER A NUMBER OF YOUR CHOICE:");
    scanf("%s",r);
    c=r[0];
    switch(c){
    case '1': record();
            break;
    case '2': displayprov();
            break;
    case '3': search();
            break;
    case '4': statistics();
            break;
    case '5': createuser();
            break;
    case '6': printf("\n");
            break;
    case '\n': t=0;
    default: printf("\nYOUR CHOICE IS INCORRECT!!!");
             break;
    }
    }while(c!='6');
    printf("BYE, HAVE A GOOD DAY!!!");
}
void statistics()
{
    FILE *v;
    char prov[20];
    char dist[20];
    char sec[20];
    char cell[20];
    char c[20];
    char w[20];
    int u,negative=0,positive=0;
    float percentage;
    v=fopen("covidtest.txt","r");
    printf("\n\t\t\t\t\t\tSTATISTICS MODE!!!\n\t\t\t\t\t\t===============\n\nENTER START DATE\(DD/MM/YY\) OR SKIP\(N\):");
    scanf("%s",c);
    strcpy(c,strupr(c));
    int t=0;
    if(strcmp(c,"N")!=0)
    {
        printf("ENTER END DATE\(DD/MM/YY\) OR SKIP\(N\):");
        scanf("%s",w);
        strcpy(w,strupr(w));
        if(strcmp(w,"N")==0)
        {
            t=1;
        }
    }
    else
    {
        t=2;
    }
    printf("\nENTER PROVINCE TO CHECK STATISTICS OR SKIP\(N\):");
    scanf("%s",prov);
    strcpy(prov,strupr(prov));
    if(strcmp(prov,"N")!=0){
    printf("\nENTER DISTRICT TO CHECK STATISTICS OR SKIP\(N\):");
    scanf("%s",dist);
    strcpy(dist,strupr(dist));
    if(strcmp(dist,"N")!=0){
    printf("\nENTER SECTOR TO CHECK STATISTICS OR SKIP\(N\):");
    scanf("%s",sec);
    strcpy(sec,strupr(sec));
    if(strcmp(sec,"N")!=0){
    printf("\nENTER CELL TO CHECK STATISTICS OR SKIP\(N\):");
    scanf("%s",cell);
    strcpy(cell,strupr(cell));
    if(strcmp(cell,"N")!=0)
    {
        if(t==1)
        printf("\n\t\t\tSTATISTICS ON %s IN %s, %s, %s, %s\n\t\t\t==========================================================\n\n",c,prov,dist,sec,cell);
        else if(t==0)
        printf("\n\t\t\tSTATISTICS FROM %s TO %s IN %s, %s, %s, %s\n\t\t\t==========================================================================\n\n",c,w,prov,dist,sec,cell);
        else if(t==2)
        printf("\n\t\t\tOVERALL STATISTICS SO FAR IN %s, %s, %s, %s\n\t\t\t===========================================================\n\n",prov,dist,sec,cell);
        while(!feof(v))
        {

            fscanf(v,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==0&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==2&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
            {
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            i++;
            percentage=(float)positive*100/(negative+positive);
        }
        printf("\nALL CASES ARE %d\nPOSITIVE CASES ARE %d\nNEGATIVE CASES ARE %d\nHENCE %.1f%% TESTED ARE POSITIVE\n",negative+positive,positive,negative,percentage);
    }
    else
    {
        if(t==1)
        printf("\n\t\t\tSTATISTICS ON %s IN %s, %s, %s\n\t\t\t===================================================\n\n",c,prov,dist,sec);
        else if(t==0)
        printf("\n\t\t\tSTATISTICS FROM %s TO %s IN %s, %s, %s\n\t\t\t===================================================================\n\n",c,w,prov,dist,sec);
        else if(t==2)
        printf("\n\t\t\tOVERALL STATISTICS SO FAR IN %s, %s, %s\n\t\t\t====================================================\n\n",prov,dist,sec);
        while(!feof(v))
        {
            fscanf(v,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==0&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==2&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
            {
                if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            i++;
            percentage=(float)positive*100/(negative+positive);
        }
        printf("\nALL CASES ARE %d\nPOSITIVE CASES ARE %d\nNEGATIVE CASES ARE %d\nHENCE %.1f%% TESTED ARE POSITIVE\n",negative+positive,positive,negative,percentage);
    }
    }
    else
    {
        if(t==1)
        printf("\n\t\t\tSTATISTICS ON %s IN %s, %s\n\t\t\t=========================================\n\n",c,prov,dist);
        else if(t==0)
        printf("\n\t\t\tSTATISTICS FROM %s TO %s IN %s, %s\n\t\t\t=========================================================\n\n",c,w,prov,dist);
        else if(t==2)
        printf("\n\t\t\tOVERALL STATISTICS SO FAR IN %s, %s\n\t\t\t==========================================\n\n",prov,dist);
        while(!feof(v))
        {
            fscanf(v,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==0&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==2&&strstr(rec.province,prov)&&strstr(rec.district,dist))
            {
                if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            i++;
            percentage=(float)positive*100/(negative+positive);
        }
        printf("\nALL CASES ARE %d\nPOSITIVE CASES ARE %d\nNEGATIVE CASES ARE %d\nHENCE %.1f%% TESTED ARE POSITIVE\n",negative+positive,positive,negative,percentage);
    }
    }
    else
    {
        if(t==1)
        printf("\n\t\t\tSTATISTICS ON %s IN %s\n\t\t\t=================================\n\n",c,prov);
        else if(t==0)
        printf("\n\t\t\tSTATISTICS FROM %s TO %s IN %s\n\t\t\t=================================================\n\n",c,w,prov);
        else if(t==2)
        printf("\n\t\t\tOVERALL STATISTICS SO FAR IN %s\n\t\t\t==================================\n\n",prov);
        while(!feof(v))
        {
            fscanf(v,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==0&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov))
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==2&&strstr(rec.province,prov))
            {
                if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            i++;
            percentage=(float)positive*100/(negative+positive);
        }
        printf("\nALL CASES ARE %d\nPOSITIVE CASES ARE %d\nNEGATIVE CASES ARE %d\nHENCE %.1f%% TESTED ARE POSITIVE\n",negative+positive,positive,negative,percentage);
    }
    }
    else
    {
        if(t==1)
        printf("\n\t\t\tSTATISTICS ON %s\n\t\t\t=======================\n\n",c);
        else if(t==0)
        printf("\n\t\t\tSTATISTICS FROM %s TO %s\n\t\t\t=======================================\n\n",c,w);
        else if(t==2)
        printf("\n\t\t\tOVERALL STATISTICS SO FAR\n\t\t\t========================\n\n");
        while(!feof(v))
        {
            fscanf(v,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&strcmp(rec.a,c)==0)
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==0&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0)
			{
			    if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            else if(t==2)
            {
                if(strcmp(rec.status,"NEG")==0)
                {
                    negative=negative+1;
                }
                else if(strcmp(rec.status,"POS")==0)
                {
                    positive=positive+1;
                }
            }
            i++;
            percentage=(float)positive*100/(negative+positive);
        }
        printf("\nALL CASES ARE %d\nPOSITIVE CASES ARE %d\nNEGATIVE CASES ARE %d\nHENCE %.2f%% TESTED ARE POSITIVE\n",negative+positive,positive,negative,percentage);
    }
fclose(v);
return;
}
int login()
{
    char username[20];
    char password[20];
    char pass[20], ch;
    int z=4,login=0,i, j;;
    FILE *k;
    printf("\t\t\t\t\t\tLOGIN FORM\n\t\t\t\t\t\t==========\n\n");
    do{
        k=fopen("login.txt","r");
        printf("\t\t\t\t\t      USERNAME:");
        scanf("%s",username);
        printf("\t\t\t\t\t      PASSWORD:");
        for(i = 0;i < 20;i++)
        {
            ch = getch();
            if(ch == 13)
            break;
            pass[i] = ch;
            ch = '*' ;
            printf("%c", ch);
        }
        password[i] = '\0';
        for(j = 0;j < i;j++)
        password[j]=pass[j];
        while(!feof(k))
        {
            fscanf(k,"%s\t%s\n",rec.fname,rec.lname);
            if(strcmp(rec.fname,username)==0&&strcmp(rec.lname,password)==0)
            {
                login=1;
            }
        }
        if(z==0)
        {
            return 0;
        }
        if(login!=1)
        {
            printf("\n\n\t\t\t\t\t   WRONG USERNAME OR PASSWORD!!!!!\n\n\t\t\t\t\tTRY AGAIN.......%d ATTEMPTS LEFT!!!!!\n\n",z);
            z=z-1;
        }
        else
        {
            printf("\n\n\t\t\t\t\t  LOGIN SUCCESSFULL!!!!!!\n");
            return 1;
        }
      }while(login!=1);
      fclose(k);
}
void createuser()
{
    FILE *u;
    char cmfpwd[20],pass[20],ch;
    int i,j,m=0;
    u=fopen("login.txt","a");
    printf("\t\t\t\t\t\tSIGNUP FORM\n\t\t\t\t\t\t===========\n\n");
    do{
    if(m>0)printf("\n\n\t\t\t\t\tPASSWORD DON'T MATCH!!!....TRY AGAIN...\n\n");
    printf("\t\t\t\t\t   ENTER USERNAME:");
    scanf("%s",rec.fname);
    printf("\t\t\t\t\t   ENTER PASSWORD:");
    for(i = 0;i < 20;i++)
    {
        ch = getch();
        if(ch == 13)
        break;
        pass[i] = ch;
        ch = '*' ;
        printf("%c", ch);
    }
    rec.lname[i] = '\0';
    for(j = 0;j < i;j++)
    rec.lname[j]=pass[j];
    printf("\n\t\t\t\t\t   CONFIRM PASSWORD:");
    for(i = 0;i < 20;i++)
    {
        ch = getch();
        if(ch == 13)
        break;
        pass[i] = ch;
        ch = '*' ;
        printf("%c", ch);
    }
    cmfpwd[i] = '\0';
    for(j = 0;j < i;j++)
    cmfpwd[j]=pass[j];
    m++;
    }while(strcmp(cmfpwd,rec.lname)!=0&&rec.lname!=NULL);
    fprintf(u,"%s\t%s\n",rec.fname,rec.lname);
    fclose(u);
    printf("\n\n\t\t\t\t\t  SIGNUP SUCCESSFULL!!!!\n\n");
}
void record()
{
    printf("\n\t\t\t\t\t\tRECORD MODE!!!\n\t\t\t\t\t\t==============\n\nENTER FIRST NAME:");
    scanf("%s",rec.fname);
    printf("ENTER LAST NAME:");
    scanf("%s",rec.lname);
    printf("ENTER NATIONAL ID:");
    scanf("%s",rec.nbr);
    printf("ENTER PROVINCE:");
    scanf("%s",rec.province);
    printf("ENTER DISTRICT:");
    scanf("%s",rec.district);
    printf("ENTER SECTOR:");
    scanf("%s",rec.sector);
    printf("ENTER CELL:");
    scanf("%s",rec.cell);
    printf("ENTER TEST RESULT\(POS/NEG\):");
    scanf("%s",rec.status);
    FILE *q;
    q=fopen("covidtest.txt","a");
    fprintf(q,"%s\n%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,strupr(rec.fname),strupr(rec.lname),strupr(rec.province),strupr(rec.district),strupr(rec.sector),strupr(rec.cell),rec.nbr,strupr(rec.status));
    fclose(q);
    return;
}
void displayprov()
{
    FILE *d;
    char prov[20];
    char dist[20];
    char sec[20];
    char cell[20];
    char c[20];
    char w[20];
    int u;
    d=fopen("covidtest.txt","r");
    printf("\n\t\t\t\t\t\tDISPLAY MODE!!!\n\t\t\t\t\t\t===============\n\nENTER START DATE\(DD/MM/YY\) OR SKIP\(N\):");
    scanf("%s",c);
    strcpy(c,strupr(c));
    int t=0;
    if(strcmp(c,"N")!=0)
    {
        printf("ENTER END DATE\(DD/MM/YY\) OR SKIP\(N\):");
        scanf("%s",w);
        strcpy(w,strupr(w));
        if(strcmp(w,"N")==0)
        {
            t=1;
        }
    }
    else
    {
        t=2;
    }
    printf("\nENTER PROVINCE TO CHECK TEST RESULTS OR SKIP\(N\):");
    scanf("%s",prov);
    strcpy(prov,strupr(prov));
    if(strcmp(prov,"N")!=0){
    printf("\nENTER DISTRICT TO CHECK TEST RESULTS OR SKIP\(N\):");
    scanf("%s",dist);
    strcpy(dist,strupr(dist));
    if(strcmp(dist,"N")!=0){
    printf("\nENTER SECTOR TO CHECK TEST RESULTS OR SKIP\(N\):");
    scanf("%s",sec);
    strcpy(sec,strupr(sec));
    if(strcmp(sec,"N")!=0){
    printf("\nENTER CELL TO CHECK TEST RESULTS OR SKIP\(N\):");
    scanf("%s",cell);
    strcpy(cell,strupr(cell));
    if(strcmp(cell,"N")!=0)
    {
        printf("\nCHOOSE FROM BELOW:\n1.ALL CASES\n2.POSITIVE CASES\n3.NEGATIVE CASES\n4.EXIT\nENTER YOUR CHOICE:");
        scanf("%d",&u);
        if(u==4)
        return;
        else if(t==1&&u==1)
        printf("\n\t\t\tALL CASES ON %s IN %s, %s, %s, %s\n\t\t\t==========================================================\n\n",c,prov,dist,sec,cell);
        else if(t==1&&u==2)
        printf("\n\t\t\tPOSITIVE CASES ON %s IN %s, %s, %s, %s\n\t\t\t===============================================================\n\n",c,prov,dist,sec,cell);
        else if(t==1&&u==3)
        printf("\n\t\t\tNEGATIVE CASES ON %s IN %s, %s, %s, %s\n\t\t\t===============================================================\n\n",c,prov,dist,sec,cell);
        else if(t==0&&u==1)
        printf("\n\t\t\tALL CASES FROM %s TO %s IN %s, %s, %s, %s\n\t\t\t==========================================================================\n\n",c,w,prov,dist,sec,cell);
        else if(t==0&&u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM %s TO %s IN %s, %s, %s, %s\n\t\t\t===============================================================================\n\n",c,w,prov,dist,sec,cell);
        else if(t==0&&u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM %s TO %s IN %s, %s, %s, %s\n\t\t\t===============================================================================\n\n",c,w,prov,dist,sec,cell);
        else if(u==1)
        printf("\n\t\t\tALL CASES FROM ALL DATES IN %s, %s, %s, %s\n\t\t\t===========================================================\n\n",prov,dist,sec,cell);
        else if(u==2)
        printf("\n\t\t\t\t\t\tPOSITIVE CASES FROM ALL DATES IN %s, %s, %s, %s\n\t\t\t================================================================\n\n",prov,dist,sec,cell);
        else if(u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM ALL DATES IN %s, %s, %s, %s\n\t\t\t================================================================\n\n",prov,dist,sec,cell);
        int j=0;
        while(!feof(d))
        {

            fscanf(d,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&u==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==1&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==1&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==2&&strcmp(rec.status,"NEG")&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==3&&strcmp(rec.status,"POS")&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec)&&strstr(rec.cell,cell))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            i++;
        }
            printf("\n%d CASES RETURNED!!!!\n",j);
    }
    else
    {
        printf("\nCHOOSE FROM BELOW:\n1.ALL CASES\n2.POSITIVE CASES\n3.NEGATIVE CASES\n4.EXIT\nENTER YOUR CHOICE:");
        scanf("%d",&u);
        if(u==4)
        return;
        else if(t==1&&u==1)
        printf("\n\t\t\tALL CASES ON %s IN %s, %s, %s\n\t\t\t===================================================\n\n",c,prov,dist,sec);
        else if(t==1&&u==2)
        printf("\n\t\t\tPOSITIVE CASES ON %s IN %s, %s, %s\n\t\t\t========================================================\n\n",c,prov,dist,sec);
        else if(t==1&&u==3)
        printf("\n\t\t\tNEGATIVE CASES ON %s IN %s, %s, %s\n\t\t\t========================================================\n\n",c,prov,dist,sec);
        else if(t==0&&u==1)
        printf("\n\t\t\tALL CASES FROM %s TO %s IN %s, %s, %s\n\t\t\t===================================================================\n\n",c,w,prov,dist,sec);
        else if(t==0&&u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM %s TO %s IN %s, %s, %s\n\t\t\t========================================================================\n\n",c,w,prov,dist,sec);
        else if(t==0&&u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM %s TO %s IN %s, %s, %s\n\t\t\t========================================================================\n\n",c,w,prov,dist,sec);
        else if(u==1)
        printf("\n\t\t\tALL CASES FROM ALL DATES IN %s, %s, %s\n\t\t\t====================================================\n\n",prov,dist,sec);
        else if(u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM ALL DATES IN %s, %s, %s\n\t\t\t=========================================================\n\n",prov,dist,sec);
        else if(u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM ALL DATES IN %s, %s, %s\n\t\t\t=========================================================\n\n",prov,dist,sec);
        int j=0;
        while(!feof(d))
        {
            fscanf(d,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&u==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==1&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==1&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==2&&strcmp(rec.status,"NEG")&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==3&&strcmp(rec.status,"POS")&&strstr(rec.province,prov)&&strstr(rec.district,dist)&&strstr(rec.sector,sec))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            i++;
        }
        printf("\n%d CASES RETURNED!!!!\n",j);
    }
    }
    else
    {
        printf("\nCHOOSE FROM BELOW:\n1.ALL CASES\n2.POSITIVE CASES\n3.NEGATIVE CASES\n4.EXIT\nENTER YOUR CHOICE:");
        scanf("%d",&u);
        if(u==4)
        return;
        else if(t==1&&u==1)
        printf("\n\t\t\tALL CASES ON %s IN %s, %s\n\t\t\t=========================================\n\n",c,prov,dist);
        else if(t==1&&u==2)
        printf("\n\t\t\tPOSITIVE CASES ON %s IN %s, %s\n\t\t\t==============================================\n\n",c,prov,dist);
        else if(t==1&&u==3)
        printf("\n\t\t\tNEGATIVE CASES ON %s IN %s, %s\n\t\t\t==============================================\n\n",c,prov,dist);
        else if(t==0&&u==1)
        printf("\n\t\t\tALL CASES FROM %s TO %s IN %s, %s\n\t\t\t=========================================================\n\n",c,w,prov,dist);
        else if(t==0&&u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM %s TO %s IN %s, %s\n\t\t\t==============================================================\n\n",c,w,prov,dist);
        else if(t==0&&u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM %s TO %s IN %s, %s\n\t\t\t==============================================================\n\n",c,w,prov,dist);
        else if(u==1)
        printf("\n\t\t\tALL CASES FROM ALL DATES IN %s, %s\n\t\t\t==========================================\n\n",prov,dist);
        else if(u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM ALL DATES IN %s, %s\n\t\t\t===============================================\n\n",prov,dist);
        else if(u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM ALL DATES IN %s, %s\n\t\t\t===============================================\n\n",prov,dist);
        int j=0;
        while(!feof(d))
        {
            fscanf(d,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&u==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==1&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov)&&strstr(rec.district,dist))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==1&&strstr(rec.province,prov)&&strstr(rec.district,dist))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==2&&strcmp(rec.status,"NEG")&&strstr(rec.province,prov)&&strstr(rec.district,dist))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==3&&strcmp(rec.status,"POS")&&strstr(rec.province,prov)&&strstr(rec.district,dist))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            i++;
        }
        printf("\n%d CASES RETURNED!!!!\n",j);
    }
    }
    else
    {
        printf("\nCHOOSE FROM BELOW:\n1.ALL CASES\n2.POSITIVE CASES\n3.NEGATIVE CASES\n4.EXIT\nENTER YOUR CHOICE:");
        scanf("%d",&u);
        if(u==4)
        return;
        else if(t==1&&u==1)
        printf("\n\t\t\tALL CASES ON %s IN %s\n\t\t\t=================================\n\n",c,prov);
        else if(t==1&&u==2)
        printf("\n\t\t\tPOSITIVE CASES ON %s IN %s\n\t\t\t======================================\n\n",c,prov);
        else if(t==1&&u==3)
        printf("\n\t\t\tNEGATIVE CASES ON %s IN %s\n\t\t\t======================================\n\n",c,prov);
        else if(t==0&&u==1)
        printf("\n\t\t\tALL CASES FROM %s TO %s IN %s\n\t\t\t=================================================\n\n",c,w,prov);
        else if(t==0&&u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM %s TO %s IN %s\n\t\t\t======================================================\n\n",c,w,prov);
        else if(t==0&&u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM %s TO %s IN %s\n\t\t\t======================================================\n\n",c,w,prov);
        else if(u==1)
        printf("\n\t\t\tALL CASES FROM ALL DATES IN %s\n\t\t\t==================================\n\n",prov);
        else if(u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM ALL DATES IN %s\n\t\t\t=======================================\n\n",prov);
        else if(u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM ALL DATES IN %s\n\t\t\t=======================================\n\n",prov);
        int j=0;
        while(!feof(d))
        {
            fscanf(d,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&u==1&&strcmp(rec.a,c)==0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)==0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==1&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0&&strstr(rec.province,prov))
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==1&&strstr(rec.province,prov))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==2&&strcmp(rec.status,"NEG")&&strstr(rec.province,prov))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==3&&strcmp(rec.status,"POS")&&strstr(rec.province,prov))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            i++;
        }
        printf("\n%d CASES RETURNED!!!!\n",j);
    }
    }
    else
    {
       printf("\nCHOOSE FROM BELOW:\n1.ALL CASES\n2.POSITIVE CASES\n3.NEGATIVE CASES\n4.EXIT\nENTER YOUR CHOICE:");
        scanf("%d",&u);
        if(u==4)
        return;
        else if(t==1&&u==1)
        printf("\n\t\t\tALL CASES ON %s\n\t\t\t=======================\n\n",c);
        else if(t==1&&u==2)
        printf("\n\t\t\tPOSITIVE CASES ON %s\n\t\t\t============================\n\n",c);
        else if(t==1&&u==3)
        printf("\n\t\t\tNEGATIVE CASES ON %s\n\t\t\t============================\n\n",c);
        else if(t==0&&u==1)
        printf("\n\t\t\tALL CASES FROM %s TO %s\n\t\t\t=======================================\n\n",c,w);
        else if(t==0&&u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM %s TO %s\n\t\t\t============================================\n\n",c,w);
        else if(t==0&&u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM %s TO %s\n\t\t\t============================================\n\n",c,w);
        else if(u==1)
        printf("\n\t\t\tALL CASES FROM ALL DATES\n\t\t\t========================\n\n");
        else if(u==2)
        printf("\n\t\t\tPOSITIVE CASES FROM ALL DATES\n\t\t\t=============================\n\n");
        else if(u==3)
        printf("\n\t\t\tNEGATIVE CASES FROM ALL DATES\n\t\t\t=============================\n\n");
        int j=0;
        while(!feof(d))
        {
            fscanf(d,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            if(t==1&&u==1&&strcmp(rec.a,c)==0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)==0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==1&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)==0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==1&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==2&&strcmp(rec.status,"NEG")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==0&&u==3&&strcmp(rec.status,"POS")&&strcmp(rec.a,c)>=0&&strcmp(rec.a,w)<=0)
			{
			    j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==1)
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==2&&strcmp(rec.status,"NEG"))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            else if(t==2&&u==3&&strcmp(rec.status,"POS"))
            {
                j++;
			    printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
            i++;
        }
        printf("\n%d CASES RETURNED!!!!\n",j);
    }
fclose(d);
return;
}
void search()
{
    FILE *h;
    char name[40];
    h=fopen("covidtest.txt","r");
    printf("\nSEARCHING BY NAME MODE!!!\n\nENTER NAME:");
    scanf("%s",name);
    strcpy(name,strupr(name));
    int n=0;
    while(!feof(h))
    {
            fscanf(h,"%s\n%s\%s\t%s\t%s\t%s\t%s\t%s\t%s\n",rec.a,rec.fname,rec.lname,rec.province,rec.district,rec.sector,rec.cell,rec.nbr,rec.status);
            int l=strstr(rec.fname,name),m=strstr(rec.lname,name);
            if(l||m)
            {
                n++;
                printf("\nFULL NAMES:%s %s\nNATIONAL ID:%s\nLOCATION:%s, %s, %s, %s\nTEST RESULT:%s\n",rec.fname,rec.lname,rec.nbr,rec.province,rec.district,rec.sector,rec.cell,rec.status);
            }
    }
    printf("\n%d CASES RETURNED!!!!\n",n);
}

#include<stdio.h>
#include<string.h>
#include<time.h>
#include<windows.h>
void gotoxy(int x, int y)
{
    COORD c;
    c.X=x;
    c.Y=y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),c);
}
struct Books
{
    int id;
    char book_name[50], author_name[50];
    int quantity;

};
struct Given
{
    int num;
    char given_name[50], student_name[50],given_date[20];
};
struct STUDENT
{
    char S_name[50],S_id[10],S_subject[20];
};
struct S
{
    char s[100];
};
struct Books bookList[100];
struct Given givenList[100];
struct STUDENT studentList[100];
struct S TIME[100];
int nog;
int nob;
int nos;
void Readfile()
{
    FILE* lm=fopen("project.txt","r");
    int i=0;
    while(fscanf(lm, "%d ",&bookList[i].id)==1)
    {
        fscanf(lm, " %[^\n]", bookList[i].book_name);
        fscanf(lm, " %[^\n]", bookList[i].author_name);
        fscanf(lm, "%d\n", &bookList[i].quantity);
        i++;
    }
    nob=i;
}
void ReadGivens()
{
    FILE* lg=fopen("issued books.txt","r");

    int g=0;
    while(fscanf(lg, "%d ",&givenList[g].num)==1)
    {
        fscanf(lg, " %[^\n]", givenList[g].given_name);
        fscanf(lg, " %[^\n]", givenList[g].student_name);
        fscanf(lg, " %[^\n]", givenList[g].given_date);
        g++;
    }
    nog=g;
}
void ReadStudent()
{
    FILE* ls=fopen("student.txt","r");
    if(ls == 0)
    {
        ls = fopen("student.txt", "w");
    }
    int s=0;
    while(fscanf(ls, " %[^\n]",studentList[s].S_name)==1)
    {
        fscanf(ls, " %[^\n]", studentList[s].S_id);
        fscanf(ls, " %[^\n]", studentList[s].S_subject);
        s++;
    }
    nos=s;
    fclose(ls);
}

void ShowBooks(struct Books bookList[100], int nob){
     printf("\e[1mid\t | Book name |  \tAuthor name | \tQuantity\e[m\n");
        for(int i=0; i<nob; i++)
        {
            bookList[i].id=i+1;
            printf("\n%2d|", bookList[i].id);
            printf("%17s|", bookList[i].book_name);
            printf("%17s|", bookList[i].author_name);
            printf("%10d", bookList[i].quantity);
        }
}

void PrintBookDetails(FILE* lm, struct Books bookList[100], int nob){
    for(int i=0; i<nob; i++)
        {
            fprintf(lm, "\n%d\n", bookList[i].id);
            fprintf(lm, "%s\n", bookList[i].book_name);
            fprintf(lm, "%s\n", bookList[i].author_name);
            fprintf(lm, "%d\n", bookList[i].quantity);
        }
}

int main()
{
    FILE* lm=fopen("project.txt","r");

    if(lm == 0)
    {
        lm = fopen("project.txt", "w");
    }
    fclose(lm);

    while(1)
    {
        int m;
        printf("***************************************************************\e[1mWELCOME TO OUR LIBRARY\e[m***********************************************************************\n");
        printf("\e[1m1: View Books\n");
        printf("2: Add Books\n");
        printf("3: Display Books By auther\n");
        printf("4: Issue Books\n"); //TODO: Can issue already issued books
        printf("5: Add Student\n");
        printf("6: View Student Info\n");
        printf("7: Issued books\n");
        printf("8: Return book\n");
        printf("9: Exit\n");
        printf("Enter choice: ");
        scanf("%d", &m);
        printf("\n");

        if(m==9)
            break;
        else if(m==1)
        {
            system("cls");
            Readfile();
            if(nob==0)
                printf("*********\e[1mThere are no books now\e[m**********\n\n");
            else
            {
                ShowBooks(bookList, nob);
                printf("\n\n");
            }

        }
        else if(m==2)
        {
            system("cls");
            ///add books
            ///read the file in array
            Readfile();
            /// input new book
            struct Books book;
            int found=0;
            printf("Enter Book name: ");
            scanf(" %[^\n]", book.book_name);
            printf("Enter Author name: ");
            scanf(" %[^\n]", book.author_name);
            printf("Enter book quantity: ");
            scanf("%d", &book.quantity);
            for(int i=0; i<nob; i++)
            {
                found=0;
                if(stricmp(book.book_name, bookList[i].book_name)==0)
                {
                    bookList[i].quantity+=book.quantity;
                    found=1;
                    break;
                }
            }
            printf("\n");
            if(found==0)
            {
                bookList[nob]=book;
                bookList[nob].id=bookList[nob-1].id+1;
                nob++;
            }
            ///write new array into the file
            lm=fopen("project.txt","w");
            PrintBookDetails(lm, bookList, nob);
            printf("++++++\e[1mBook Is Successfully Added\e[m+++++++\n\n");
            fclose(lm);

        }
        else if(m==3)
        {
             system("cls");
            /// Display Books By auther

            Readfile();
            char NAME[50];
            printf("Enter author name: ");
            scanf(" %[^\n]", NAME);
            int f=0;
            int i=0;
            printf("\e[1mBook name\t   Quantity\e[m\n");
            while(i<nob)
            {
                if(stricmp(NAME, bookList[i].author_name)==0)
                {
                    f=1;
                    printf("%-15s ", bookList[i].book_name);
                    printf("   %d\n", bookList[i].quantity);
                }
                i++;
            }
            if(f==0)
                printf("--------\e[1mBook not found or cheak for spelling mistakes\e[m---------\n\n");
            printf("\n");
        }
        else if(m==4)
        {
             system("cls");
            ///issue books
            Readfile();
            if(nob==0)
                printf("*********\e[1mThere are no books now\e[m**********\n\n");
            else
            {
                gotoxy(60,0);
                printf("\e[1mid\t      Book name      Author name       Quantity\e[m");
                gotoxy(60,1);
                for(int i=0; i<nob; i++)
                {
                    gotoxy(60,i+2);
                    bookList[i].id=i+1;
                    printf("%2d", bookList[i].id);
                    printf("%17s", bookList[i].book_name);
                    printf("%17s", bookList[i].author_name);
                    printf("%15d", bookList[i].quantity);
                    gotoxy(60,i+3);
                }
                gotoxy(0,0);




            ReadStudent();

            ///choose book
            int B_id;
            char A_scholar[10];
            int k=0;

            printf("Enter book id: ");
            scanf("%d", &B_id);
            if(B_id>nob){
                printf("xxxxxx\e[1mBook id was not found\e[mxxxxxx\n");
            }
            else{
            printf("Enter scholar's id: ");
            scanf(" %[^\n]", A_scholar);
            ///delete book from file

            lm=fopen("project.txt","w");
            int pos=-1,pos2=-1;
            for(int j=0; j<nos; j++)
            {
                k=0;
                if(stricmp(A_scholar,studentList[j].S_id)==0)
                {
                    k=1;
                    pos2=j;
                    break;
                }
            }

            if(k==1)
            {
                ///issuing date to issued books
                time_t now=time(NULL);
                struct tm *issue_time=localtime(&now);
                strftime(TIME[nog].s,100,"%x %I:%M",issue_time);

                ///adding to issued list

                FILE* lg=fopen("issued books.txt","a");
                fprintf(lg, "%d\n", nog);
                fprintf(lg, "%s\n", bookList[B_id-1].book_name);
                fprintf(lg, "%s\n", studentList[pos2].S_name);
                fprintf(lg, "%s\n",TIME[nog].s);
                nog++;

                printf("---------\e[1mBook is Successfully Issued\e[m---------\n\n");

                ///decreasing that book quantity
                --bookList[B_id-1].quantity;
                ///sorting books after when its out of stock
                if(bookList[B_id-1].quantity==0)
                {
                    for(int i=B_id-1; i<nob-1; i++)
                    {

                        bookList[i]=bookList[i+1];
                    }
                    nob--;
                }

                fclose(lg);
            }
            else
                printf("xxxxxx\e[1mStudent id was not found\e[mxxxxxx\n");

            for(int i=0; i<nob; i++)
            {
                fprintf(lm, "\n%d\n", bookList[i].id);
                fprintf(lm, "%s\n", bookList[i].book_name);
                fprintf(lm, "%s\n", bookList[i].author_name);
                fprintf(lm, "%d\n", bookList[i].quantity);
            }
            fclose(lm);
            gotoxy(0,nob+4);
            }
            }
        }
        else if(m==5)
        {
             system("cls");
            ///Add Student

            ReadStudent();
            /// input new student
            struct STUDENT scholar;

            printf("Enter Student name: ");
            scanf(" %[^\n]", scholar.S_name);
            printf("Enter Student Id: ");
            scanf(" %[^\n]", scholar.S_id);
            printf("Enter Program Name: ");
            scanf(" %[^\n]", scholar.S_subject);
            printf("\n");

            studentList[nos]=scholar;
            nos++;
            ///write new array into the file
            FILE* ls=fopen("student.txt","w");

            for(int s=0; s<nos; s++)
            {

                fprintf(ls, "%s\n", studentList[s].S_name);
                fprintf(ls, "%s\n", studentList[s].S_id);
                fprintf(ls, "%s\n", studentList[s].S_subject);
            }
            printf("++++++\e[1mNew Student Added\e[m+++++++\n\n");
            fclose(ls);

        }
        else if(m==6)
        {
             system("cls");
            ///view student

            ReadStudent();
            if(nos==0)
                printf("**********\e[1mThere are no students\e[m************\n\n");
            else
            {
                printf("\e[1mid\t      Student Name\t Subject\e[m\n\n");
                for(int s=0; s<nos; s++)
                {
                    printf("%s", studentList[s].S_id);
                    printf("%19s", studentList[s].S_name);
                    printf("\t %s\n", studentList[s].S_subject);
                }
                printf("\n");
            }

        }
        else if(m==7)
        {
             system("cls");

            FILE* lg=fopen("issued books.txt","r");
            if(lg == 0)
            {
                lg = fopen("issued books.txt", "w");
            }
            fclose(lg);
            ReadGivens();
            if(nog==0)
                printf("...........\e[1mNo Books Issued Yet\e[m..........\n\n");
            else
            {
                printf("\e[1mNO.\t  Issued book\t\t Student name\t\tMM/DD/YY\e[m\n");
                for(int g=0; g<nog; g++)
                {
                    givenList[g].num=g+1;
                    printf("\n%d", givenList[g].num);
                    printf("%20s", givenList[g].given_name);
                    printf("%24s", givenList[g].student_name);
                    printf("%25s", givenList[g].given_date);

                }
                printf("\n\n");
            }

        }
        else
        {
            ///return book
             system("cls");
              FILE* lg=fopen("issued books.txt","r");
            if(lg == 0)
            {
                lg = fopen("issued books.txt", "w");
            }
            fclose(lg);
            ReadGivens();
            if(nog==0)
                printf("...........\e[1mNo Books Issued Yet\e[m..........\n\n");
            else
            {
                gotoxy(60,0);
                printf("\e[1mNO.\t      Issued book\t     Student name\t          MM/DD/YY\e[m");
                for(int g=0; g<nog; g++)
                {
                    gotoxy(60,g+1);
                    givenList[g].num=g+1;
                    printf("%d", givenList[g].num);
                    printf("%20s", givenList[g].given_name);
                    printf("%24s", givenList[g].student_name);
                    printf("%25s", givenList[g].given_date);
                    gotoxy(60,g+2);

                }

            gotoxy(0,0);

            int G_id;
            int r=0;
            Readfile();

            printf("Enter Book id: ");
            scanf("%d", &G_id);

            ///search the item in the booklist
            for(int i=0; i<nob; i++)
            {
                r=0;
                if(stricmp(bookList[i].book_name,givenList[G_id-1].given_name)==0)
                {

                    ++bookList[i].quantity;
                    r=1;
                    break;
                }

            }
            ///increasing that books quantity if its found
            if(r==1)
            {

                lm=fopen("project.txt","w");
                for(int i=0; i<nob; i++)
                {
                    fprintf(lm, "\n%d\n", bookList[i].id);
                    fprintf(lm, "%s\n", bookList[i].book_name);
                    fprintf(lm, "%s\n", bookList[i].author_name);
                    fprintf(lm, "%d\n", bookList[i].quantity);
                }

            }
            else
            {
                ///adding that book if its not found
                bookList[nob].id=nob;
                printf("Enter author name: ");
                scanf(" %[^\n]",bookList[nob].author_name);
                bookList[nob].quantity=1;
                nob++;
                lm=fopen("project.txt","w");
                for(int i=0; i<nob; i++)
                {
                    fprintf(lm, "\n%d\n", bookList[i].id);
                    fprintf(lm, "%s\n", bookList[i].book_name);
                    fprintf(lm, "%s\n", bookList[i].author_name);
                    fprintf(lm, "%d\n", bookList[i].quantity);
                }


            }
            fclose(lm);
            ///searching in the givenlist to delete from issued list

            for(int j=G_id-1; j<nog-1; j++)
            {
                givenList[j]=givenList[j+1];

            }
            nog--;
             lg=fopen("issued books.txt","w");
            for(int g=0; g<nog; g++)
            {
                givenList[g].num=g+1;
                fprintf(lg, "\n%d\n", givenList[g].num);
                fprintf(lg, "%s\n", givenList[g].given_name);
                fprintf(lg, "%s\n", givenList[g].student_name);
                fprintf(lg, "%s\n",givenList[g].given_date);
            }
            fclose(lg);
            printf("**********\e[1mBook Returned Successfully\e[m**********\n\n");
            gotoxy(0,nog+5);
            }

        }

    }
    return 0;
}


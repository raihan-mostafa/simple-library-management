#include <stdio.h>
#include <string.h>
int main()
{
    char s[10000],username[1000],pwd[1000],profile[1000],role[1000],key[1000];
    scanf("%[^\n]", s);
    int len=strlen(s),i,j,count=0;

    for(i=0; i<len; i++)
    {
        if(s[i-1]=='=')
        {
            j=0;

            while(s[i]!='&' && i<len)
            {
                if(count==0)
                {
                    username[j]=s[i];
                }
                if(count==1)
                {
                    pwd[j]=s[i];
                }
                if(count==2)
                {
                    profile[j]=s[i];
                }

                if(count==3)
                {
                    role[j]=s[i];
                }
                if(count==4)
                {
                    key[j]=s[i];
                }
                j++;
                i++;
            }
            if(count==0)
                username[j]='\0';
            else if(count==1)
                pwd[j]='\0';
            else if(count==2)
                profile[j]='\0';
            else if(count==3)
                role[j]='\0';
            else
                key[j]='\0';
            count++;
            if(count==5)
                break;
        }

    }
    printf("username: %s\npwd: %s\nprofile: %s\nrole: %s\nkey: %s",username,pwd,profile,role,key);
}

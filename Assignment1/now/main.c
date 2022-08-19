#include <unistd.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>

#include<stdlib.h>


int LINE_NUM=10;
int ORDER=1;
char source[30]="./sample.txt";

int main(int argc,char **argv)
{
    int ch;
    char path[30]={"/dev/tty"};
    opterr=0;
    while((ch=getopt(argc,argv,"n:d:L"))!=-1)
    {
        switch (ch)
        {
        case 'n':
            LINE_NUM= atoi(optarg);
            break;
        case 'd':
            strcpy(path,optarg);
            strcat(path,"a.txt");
            break;

        case 'L':
            ORDER= 0;
            break;
        default:
            
            break;
        }
    }
    if(optopt!=0)
    {
        
    }
    if(optind<argc)
        strcpy(source,argv[optind]);
    int src=open(source,O_RDONLY);
    int dst=open(path,O_RDWR|O_CREAT,S_IREAD|S_IWRITE);
    // char **array=(char ** )malloc(sizeof(char)*LINE_NUM*60); //设置一行60个字符
    if(ORDER)  //顺序
    {
        int i=0;
        char array[60];
        while(i<LINE_NUM)
        {
            int len;
            if((len=read(src,array,60*sizeof(char)))!=0)
            {
                for(int j=0;j<len;++j)
                {
                    write(dst,&array[j],1);
                    if(array[j]=='\n')
                    {
                        ++i;
                        if(i==LINE_NUM)
                        {
                            break;
                        }
                    }
                    
                    
                }
            }
            else 
            {
                char warn[]={"file is end\n"};
                // write(dst,warn,sizeof(warn));
            }
            if(i!=LINE_NUM)++i;
        }
    }
    else
    {
        char array[100][60];
        int len;
        char temp[60],buf[60];
        int size;
        int length=0;
        while((len=read(src,buf,60*sizeof(char)))!=0)
        {
            // printf("%s\n",buf);
            
            for(int i=0;i<len;++i)
            {
                temp[length]=buf[i];
                length++;
                
                if(buf[i]=='\n')
                {
                    temp[length]='\0';
                    // printf("%d %s ",size,temp);
                    strcpy(array[size],temp);
                    length=0;
                    // bzero(temp,60);
                    size++;
                    
                }
            }
        }
        if(length!=0)
        {
           
            temp[length++]='\0';
            strcpy(array[size++],temp);   
        }

        for(int i=0;i<LINE_NUM;++i)
        {
            if(i==size)
                break;
            char t[60];
            
            strcpy(t,array[size-LINE_NUM-1+i]);
      
            write(dst,t,strlen(t)*sizeof(char));
        }
        
    }
    
    close(src);
    close(dst);
    // free(array);

}
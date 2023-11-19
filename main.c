#include <stdio.h>

#define ROWW 8  // width of a row in bytes
#define PADBC 4 // left pad of bytecounter

int test()
{
	return 0;
}

int main(int argc, int *argv[]){

     FILE *fp = stdin;

     if(argc > 1){
     	char *filename = argv[1];
     	fp = fopen(filename, "rb");
     	if(fp==NULL){
               printf("could not open '%s'\n", filename);
               return 1;
     	}
     }

     unsigned char buff[ROWW+1];
     buff[ROWW] = '\0';
     long count = 0;
	int l;

read:
	while(l = fread(buff,1,ROWW,fp))
	{
          printf("%0*li ", PADBC, count);
          int i;
          for(i=0;i<l;i++) {
               printf("%02X ", buff[i]);
               if(!isgraph(buff[i]) && buff[i] != ' '){
                    buff[i]='.';
               }
		}
          for(;i<ROWW;i++) { // not enough bytes to fill the row
               printf("   ");
               buff[i]=' ';
          }
     	printf("%s\n",buff);
          count += l;
     }
	if(!feof(fp)){
		goto read;
	}

     fclose(fp);
     return 0;
}
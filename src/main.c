#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include "mylib.h"

int main(int argc, char *argv[]) {
  int opt, prec, filedsc;
  float arg1, arg2;
  int operation,exp;
  double result;
  char ch[200];
  prec = 3;
  while ((opt = getopt(argc, argv, "asmdq:wp:")) != -1) {
     switch (opt) {
     case 'p':
         prec = atoi(optarg);
         break;
     case 'a':
     case 's':
     case 'm':
     case 'd':
         if (argc < 4) {
           fprintf(stderr, "Needs two numbers\n");
           exit(EXIT_FAILURE);
         }
         arg1 = atof(argv[1]);
         arg2 = atof(argv[2]);
         operation = opt;
         break;
     case 'w':
         if (argc < 4) {
           fprintf(stderr, "Needs two numbers\n");
           exit(EXIT_FAILURE);
         }
         arg1 = atof(argv[1]);
         exp = atoi(argv[2]);
         operation = opt;
         break;
     case 'q':
         arg1 = atof(optarg);
         operation = opt;
         break;
     default: /* '?' */
         fprintf(stderr, "Usage: %s [-t nsecs] [-n] name\n",
                 argv[0]);
         exit(EXIT_FAILURE);
     }
  }

  filedsc = open("./history",O_RDWR|O_APPEND|O_CREAT,00666);
  switch (operation) {
    case 'a':
      result = add(arg1,arg2);
      printf("%.*f\n",prec,result);
      write(filedsc,argv[argc-2],strlen(argv[argc-2]));
      write(filedsc," + ",3);
      write(filedsc,argv[argc-1],strlen(argv[argc-1]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
    case 's':
      result=sub(arg1,arg2);
      printf("%.*f\n",prec,result);
      write(filedsc,argv[argc-2],strlen(argv[argc-2]));
      write(filedsc," - ",3);
      write(filedsc,argv[argc-1],strlen(argv[argc-1]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
    case 'm':
      result=mul(arg1,arg2);
      printf("%.*f\n",prec,result);
      write(filedsc,argv[argc-2],strlen(argv[argc-2]));
      write(filedsc," * ",3);
      write(filedsc,argv[argc-1],strlen(argv[argc-1]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
    case 'd':
      result=divid(arg1,arg2);
      printf("%.*f\n",prec,result );
      write(filedsc,argv[argc-2],strlen(argv[argc-2]));
      write(filedsc," / ",3);
      write(filedsc,argv[argc-1],strlen(argv[argc-1]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
    case 'w':
      result=power(arg1,exp);
      printf("%.*f\n",prec,result );
      write(filedsc,argv[argc-2],strlen(argv[argc-2]));
      write(filedsc," ^ ",3);
      write(filedsc,argv[argc-1],strlen(argv[argc-1]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
    case 'q':
      result=sr(arg1);
      printf("%.*f\n",prec,result );
      write(filedsc,"sqrt ",5);
      write(filedsc,argv[2],strlen(argv[2]));
      write(filedsc," = ",3);
      sprintf(ch,"%.*f",prec,result);
      write(filedsc,ch,strlen(ch));
      write(filedsc,"\n",2);
      break;
  }
  close(filedsc);
  exit(EXIT_SUCCESS);
}

#include <stdio.h>
#include <string.h>

int str2number(char* buf, int* num)
{
  int state = 0;	// 状態(0は初期状態）
  int ret = 0;		// 1 受理, 0 非受理(文法エラー)
  int number = 0;	// 解釈した数字
  int i;

  for (i = 0; buf[i] != 0; i++) {
    char c = buf[i];
    if (state == 0) {		// S0
      if (c == '0') {
        state = 1;
        ret = 10;
        number = 0;
      }
      else if (c >= '1' && c <= '9') {
        state = 2;
        ret = 10;
        number = (int)(c - '0');
      }
      else {
        ret = 0;
        break;
      }
    }
    else if (state == 1) {	// S1
      ret = 0;
      break;
    }
    else if (state == 2) {	// S2 
      if (c >= '0' && c <= '9') {
    		number = number * 10 + (c - '0');
      }
      else {
        ret = 0;
        break;
      }
    }
    else {
      ret = 0;
      break;
    }
  }
  *num = number;
  return ret;
}

int main(void)
{
  char buf[BUFSIZ];
  char* s;
  printf("> ");
  s = fgets(buf, BUFSIZ-1, stdin) ;
  while (s != NULL) {
    int num = 0;
    int ret;

    buf[(unsigned)strlen(buf)-1] = '\0';

    ret = str2number(buf, &num);
    switch (ret) {
      case 10:
        printf("10進数: %d\n", num);
        break;
      default:
        printf("文法エラー\n");
    }
    printf("> ");
    s = fgets(buf, BUFSIZ-1, stdin) ;
  }
  return 0;
}

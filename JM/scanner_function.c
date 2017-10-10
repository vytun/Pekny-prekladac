#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <ctype.h>

#include "scanner.h"
#include "err_code.h"

void ClearLast(SBuffer *buffer);

bool IsOperator(SBuffer* buffer){

  for (int i = 0; i < OP_COUNT; i++){

    if(strcmp(buffer->str,operatory[i]) == 0)return true;
  }
  return false;
}

bool IsKey(SBuffer* buffer){

  ClearLast(buffer);

  int len1 = strlen(buffer->str);

  for (int i = 0; i < KEY_COUNT; i++){
    int len2 = strlen(key_pole[i]);

    if(len1 != len2) continue;

    for (int j = 0; j < len2; j++){
      if(tolower(buffer->str[j]) != tolower(key_pole[i][j]))break;
      return true;
    }

  }
  return false;
}

int InitBuffer(SBuffer* buffer){

  if((buffer->str = malloc (sizeof(char))) == NULL) return ERR_INT;

  buffer->len = 0;
  buffer->str[0] = '\0';

  return OK;

}

int AddBuffer(SBuffer* buffer, char c){

  buffer->len++;

  if((buffer->str = (char*) realloc(buffer->str,(buffer->len + 1) *sizeof(char))) == NULL) return ERR_INT;

  buffer->str[buffer->len-1] = c;
	buffer->str[buffer->len] = '\0';

  return OK;

}

void ClearLast(SBuffer* buffer){
  buffer->len--;
  buffer->str[buffer->len] = '\0';
}

void ClearBuffer(SBuffer* buffer){
  buffer->str[0] = '\0';
  buffer->len = 0;

}


void FreeBuffer(SBuffer* buffer){
  free(buffer->str);
}

/*
* je treba podivat se na stderr protoze mam stdout
* pokusit se zbavit globalniho bufferu
* zjistit jestli je potreba konec radku
* poresit nemezerovani
*/



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#include "scanner.h"
#include "err_code.h"


void vypis(Stoken t){
    printf("%d, %s\n", t.type, t.string_value);
}


void Scan(SBuffer *buffer){


  int c;
  int ret_val;


  Stoken token;


  SStav stav = INIT;


  if((ret_val = InitBuffer(buffer)) != 0) printf("%d\n", ret_val);


  while((c = getchar()) != EOF){
    switch(stav){

      case INIT:
      //printf("%s\n","init" );
        if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

        if(c == ' ' | c == '\n'){
          stav = INIT;
          ClearBuffer(buffer);
        }
        else if(c == '!') stav = STRING_S;
        else if(c == '\'') stav = L_COMM;
        else if(c == '/') stav = SLASH;
        else if(c == '_') stav = ID;
        else if(isdigit(c)) stav = NUM;
        else if(isalpha(c)) stav = KEY_W;
        else if(IsOperator(buffer)) stav = OPERATOR;
        else if(c == ';'){
          token.type = T_strednik;
          token.string_value = ";";
          ClearBuffer(buffer);
        }
        else if(c == '\n');
        else printf("%s %d\n", "chyba:", ERR_LEX );
      break;

      case STRING_S:
      //printf("%s\n","strings" );
        if (c == '\"') {
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;
        }

        else{
          printf("%s %d\n", "chyba:", ERR_LEX );
          stav = INIT;
          ClearBuffer(buffer);
        }

      break;
      case STRING:
      //printf("%s\n","string" );
        if(c == '\\'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = ESCAPE;
        }

        else if (c == '\"') {
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          token.type = T_string;
          token.string_value = buffer->str;
          vypis(token);
          stav = INIT;
          ClearBuffer(buffer);

        }

        else{
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
        }
      break;

      case NUM:
      //printf("%s\n","num" );
        if(isdigit(c)){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
        }
        else if(c == '.'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = DOUBLE;
        }
        else if(c == 'e' || c == 'E'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = EXP;
        }
        else{
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

          token.type = T_int;
          token.string_value = buffer->str;
          stav = INIT;

          vypis(token);
          ClearBuffer(buffer);
        }
      break;

      case DOUBLE:
      //printf("%s\n","double" );
        if(isdigit(c)){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
        }
        else if(c == 'e' || c == 'E'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = EXP;
        }
        else{
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

          token.type = T_double;
          token.string_value = buffer->str;
          stav = INIT;

          vypis(token);
          ClearBuffer(buffer);
        }
      break;

      case EXP:
      //printf("%s\n","exp" );
        if(c == '+' || c == '-'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

        }
        else if(isdigit(c)){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

        }
        else{

          token.type = T_double;
          token.string_value = buffer->str;
          stav = INIT;

          vypis(token);
          ClearBuffer(buffer);
        }
      break;

      case KEY_W:
      //printf("%s\n", "key" );

        if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

        if(c == ' ' || c == '\n'){
          if(IsKey(buffer)){
            token.type = T_key;
            token.string_value = buffer->str;
            stav = INIT;

            vypis(token);
            ClearBuffer(buffer);
          }

          else{
            token.type = T_id;
            token.string_value = buffer->str;
            stav = INIT;

            vypis(token);
            ClearBuffer(buffer);
          }
        }
      break;

      case ID:
      //printf("%s\n", "id" );

        if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

        if(c == ' ' || c == '\n'){
            token.type = T_id;
            token.string_value = buffer->str;
            stav = INIT;

            vypis(token);
            ClearBuffer(buffer);
        }
      break;

      case L_COMM:
      //printf("%s\n","lcomm" );
        if(c == '\n'){
          stav = INIT;
          token.type = T_Lcomment;
          token.string_value = buffer->str;
          vypis(token);
          ClearBuffer(buffer);
        }

        else{
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
        }
      break;

      case B_COMM:
      //printf("%s\n","bcom" );
        if (c == '\''){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = B_COMM_END;
        }
        else{
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
        }
      break;

      case B_COMM_END:
      //printf("%s\n","bcommend" );
        if(c == '/'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          token.type = T_Bcomment;
          token.string_value = buffer->str;
          vypis(token);
          stav = INIT;
          ClearBuffer(buffer);
        }
      break;

      case OPERATOR:
      //printf("%s\n","operator" );
        if(c == '>' || c == '='){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          token.type = T_operator;
          token.string_value = buffer->str;
          stav = INIT;
          vypis(token);
          ClearBuffer(buffer);
        }
        else{
          token.type = T_operator;
          token.string_value = buffer->str;
          stav = INIT;
          vypis(token);
          ClearBuffer(buffer);
        }
      break;

      case ESCAPE:
      //printf("%s\n","escape" );
        if(c == 'n'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;

        }
        else if(c == '\\'){
          stav = STRING;

        }
        else if(c == '\''){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;

        }
        else if(c == '\"'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;

        }
        else if(c == '?'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;
        }
        else if(c == 't'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;

        }
        else if(c == 'b'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;

        }
        else if(c == 'r'){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = STRING;
        }
        else if(isdigit(c)){
          ClearBuffer(buffer);
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = ASCII;
        }
      break;

      case SLASH:
      //printf("%s\n","slash" );
        if(c == '\''){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = B_COMM;
        }

        //popremyslet kdyz nebude mezera
        else{
          token.type = T_operator;
          token.string_value = buffer->str;
          vypis(token);
          ClearBuffer(buffer);
        }
      break;

      case ASCII:
      //printf("%s\n","ascii" );
        if(isdigit(c)){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);
          stav = ASCII_END;
        }
      break;

      case ASCII_END:
      //printf("%s\n","asciiend" );
        if (isdigit(c)){
          if ((ret_val = AddBuffer(buffer,c)) != 0) printf("%d\n", ret_val);

          token.type = T_escape;
          token.string_value = buffer->str;
          stav = STRING;

          vypis(token);
          ClearBuffer(buffer);
        }
      break;


    }// end switch
  }// end while

  FreeBuffer(buffer);
}


void main(){
  SBuffer b,*buffer;
  buffer = &b;

      Scan(buffer);

      /*
      buffer->str = "else";
      printf("%d\n",IsKey(buffer));
      buffer->str = "ELSE";
      printf("%d\n",IsKey(buffer));
      buffer->str = "eLsE";
      printf("%d\n",IsKey(buffer));
      */


}

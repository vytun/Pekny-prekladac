#include <stdbool.h>


#define OP_COUNT 11
#define KEY_COUNT 35


typedef enum type{

  //datove typy
  T_int = 0,
  T_double = 1,
  T_string = 2,
  T_id = 3,
  T_operator = 4,
  T_Lcomment = 5,
  T_Bcomment = 6,
  T_escape = 7,
  T_key = 8,
  T_strednik = 9
} Dtype;



typedef enum stavy{
  INIT,
  ID,
  STRING_S,STRING,
  NUM,
  DOUBLE,
  EXP,
  KEY_W,
  KEY,
  L_COMM,
  B_COMM,
  B_COMM_END,
  OPERATOR,
  ESCAPE,
  INT,
  SLASH,
  ASCII,ASCII_END


} SStav;




typedef struct struct_token{
  Dtype type;

  union{
    int int_value;
    double double_value;
    char* string_value;
  };

} Stoken;


typedef struct struct_buffer{
  char* str;
  int len;
} SBuffer;


static char* key_pole[KEY_COUNT] = {

  //klicova slova
  "As",
  "Asc",
  "Declare",
  "Dim",
  "Do",
  "Double",
  "Else",
  "End",
  "Chr",
  "Function",
  "If",
  "Input",
  "Integer",
  "Length",
  "Loop",
  "Print",
  "Return",
  "Scope",
  "String",
  "SubStr",
  "Then",
  "While",

  // rezervovana slova

  "And",
  "Boolean",
  "Continue",
  "Elseif",
  "Exit",
  "False",
  "For",
  "Next",
  "Not",
  "Or",
  "Shared",
  "Static",
  "True"

};

static char* operatory[OP_COUNT]={
  "*",
  "/",
  "\\",
  "+",
  "-",
  "=",
  "<>",
  "<",
  "<=",
  ">",
  ">="

};



bool IsOperator(SBuffer* buffer);
int InitBuffer(SBuffer* buffer);
int AddBuffer( SBuffer* buffer, char c);
void ClearBuffer(SBuffer* buffer);
void FreeBuffer(SBuffer* buffer);
bool IsKey(SBuffer* buffer);




SBuffer buffer;

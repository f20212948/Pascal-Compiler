%{
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
     
    #define MAX_SYMBOLS 1000
     
    int yylex();
    int yyerror(const char *msg);
    extern FILE *yyin;
     
    typedef struct symbol {
    char name[100];
    char type[100];
    int assigned;
    int isArray;
    struct symbol* next;
	} symbol;
     
    symbol symtab[MAX_SYMBOLS];
    int symtab_len = 0;
    char* current_type = "";
    int flag=1;
    int is_array = 0; 
    symbol* lookup(char* name) {
        for(int i = 0; i < symtab_len; i++) {
            if(strcmp(symtab[i].name, name) == 0) {
                return &symtab[i];
            }
        }
        return NULL;
    }


    typedef struct quadruple {
        char op[100];
        char arg1[100];
        char arg2[100];
        char result[100];
    } quadruple;
         
    quadruple quad[1000];
    int quad_len = 0;
    int temp_var_counter = 0;
        
    


    

symbol* insert(char* name) {
    symbol* s = lookup(name);
    if(s != NULL) {
        printf("Error: Duplicate declaration of variable %s\n", name);
        flag=0;
        //exit(1);
    } else {
        s = malloc(sizeof(symbol));
        strcpy(s->name, name);
        s->assigned = 0;
        symtab[symtab_len] = *s;
        symtab_len++;
        return &symtab[symtab_len-1];
    }
}

void emit(char* op, char* arg1, char* arg2, char* result) {
        strcpy(quad[quad_len].op, op);
        strcpy(quad[quad_len].arg1, arg1);
        strcpy(quad[quad_len].arg2, arg2);
        strcpy(quad[quad_len].result, result);
        quad_len++;
    }


char* create_temp_var() {
        char* temp_var = malloc(20);
        sprintf(temp_var, "t%d", temp_var_counter++);
        //insert(temp_var);
        return temp_var;
    }
int temp_label_counter = 1;
char* create_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "IFLabel:%d", temp_label_counter++);
        return temp_label;
    }

char* currLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "IFLabel:%d", temp_label_counter-1);
    return temp_label;
}

int wtemp_label_counter = 1;
char* wcreate_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "Whilelabel:%d", wtemp_label_counter++);
        return temp_label;
    }

char* wcurrLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "WhileLabel:%d", wtemp_label_counter-1);
    return temp_label;
}


int fortemp_label_counter = 1;
char* forcreate_temp_label() {
        char* temp_label = malloc(50);
        sprintf(temp_label, "Forlabel:%d", fortemp_label_counter++);
        return temp_label;
    }

char* forcurrLabel(){
    char* temp_label = malloc(50);
    sprintf(temp_label, "ForLabel:%d", fortemp_label_counter-1);
    return temp_label;
}


void assign_type(symbol* list, char* type) {
    symbol* s = list;
    while(s != NULL) {
        strcpy(s->type, type);
        //symtab_len++;
        s = s->next;
    }
}
void setArray(symbol* s, int isArr){
    symbol* sym = s;
        sym->isArray = isArr;
        sym->assigned = 1;
}

     
    void assign(char* name) {
        symbol* s = lookup(name);
        if(s == NULL) {
            printf("Error: Undeclared variable %s\n", name);
            flag=0;
            //exit(1);
        } else {
            s->assigned = 1;
        }
    }
     
    void check_expr_type(symbol* s1, symbol* s2) {
    if(s1 != NULL && s2 != NULL) {
        if(s1->name[0]=='t' || s2->name[0]=='t')
            return;
       // printf("TYPE: %s %s\n", s1->type, s2->type);
        if(strcmp(s1->type, s2->type) != 0) {
            printf("Error: Type mismatch in arithmetic operation between %s and %s\n", s1->name, s2->name);
            flag=0;
            //exit(1);
        }
    } 
}
typedef struct assign_stmt {
    symbol* var;
    symbol* expr;
} assign_stmt; 
void check_assign_type(assign_stmt* stmt) {
    if(stmt->var != NULL && stmt->expr != NULL) {
        //printf("TYPE: %s %s\n", stmt->var->type, stmt->expr->type);
        check_expr_type(stmt->var, stmt->expr);
    }
}

void check_assigned(char* name) {
        symbol* s = lookup(name);
        if(s != NULL && s->assigned == 0) {
            printf("Error: Variable %s used before assignment\n", name);
            flag=0;
            //exit(1);
        }
        else if(s == NULL){
            printf("Error: Undeclared variable %s\n", name);
            flag=0;
        }
    }
    %}
%union
{
        int ival;
        double rval;
        char* sval;
        struct symbol* sym;
        struct quadruple* quad;
}
     
%token PROG_ID INT REAL BOOL VAR CHAR TO DOWNTO IF ELSE WHILE FOR THEN DO ARRAY OF AND OR NOT BEG END READ WRITE 
           PLUS MINUS MULTIPLY DIVIDE MOD EQUAL ASSIGN LT GT LTE GTE NE SEMICOLON COLON COMMA DOT LP RP LB RB
%token <ival> NUM
%token <sval> STRING ID RANGE
%token <rval> REALNUM
%type <sval> t type  
%type <quad> stmt_list stmt Block io_stmt varlis   
%type <sym> varlist f T e relop expression if_stmt else_part while_stmt for_stmt assign_stmt
%left NOT
%left AND
%left  OR
%%
                                        //flag = 1;
    prog: PROG_ID SEMICOLON v Block DOT {}
        ;
    v : VAR va
        | ;
    va: va varlist COLON type SEMICOLON {current_type = $4; assign_type($2, current_type); if(is_array){ setArray($2,is_array);
                                                                                                  } is_array=0;} 
    | varlist COLON type SEMICOLON {current_type = $3; assign_type($1, current_type); if(is_array){ setArray($1,is_array);
                                                                                                  } is_array=0; }; 
    type: t { strcpy($$, $1); }
        | ARRAY RANGE OF t { strcpy($$ , $4); is_array = 1;}
    t: INT {strcpy($$, "INT");}
        | REAL {strcpy($$ ,"REAL");}
        | BOOL  {strcpy($$ ,"BOOL");}
        | CHAR {strcpy($$, "CHAR");}
    varlist: varlist COMMA ID { $$ = insert($3); $$->next = $1; }
    | ID { $$ = insert($1); }; 
    stmt_list: stmt_list stmt    
        |
        ;
    stmt: Block 
        | assign_stmt SEMICOLON
        | if_stmt SEMICOLON
        | for_stmt SEMICOLON
        | while_stmt SEMICOLON
        | io_stmt SEMICOLON
        ;
    Block: BEG stmt_list END
        ;
    io_stmt: READ LP ID RP{  assign($3); } 
        | READ LP ID LB e RB RP{ assign($3); }
        | WRITE LP STRING RP
        | WRITE LP varlis RP;
    varlis: varlis COMMA ID { check_assigned($3); }
            | ID {check_assigned($1); }   
    if_stmt: IF expression THEN { emit("ifFalse", "IfCondition", "GOTO", create_temp_label()); } stmt else_part;
    else_part: ELSE { 
        
        emit(currLabel(), ":", "ElseCode", "-");
        }
        stmt 
    | { emit(currLabel(), ":", "doNothing", "-"); }
    
    while_stmt: WHILE expression DO {
        emit(wcreate_temp_label(), ":", "WhileCode", "-");
        emit("ifFalse", "Condition", "GOTO", wcreate_temp_label());
    } 
    stmt{
        wtemp_label_counter--;
        emit("GOTO", "WhileCode", "", wcurrLabel());
        wtemp_label_counter++;

        emit(wcurrLabel(), ":", "done", "-");

    };
    for_stmt: FOR ID ASSIGN  e TO e DO  { assign($2);
        emit(forcreate_temp_label(), ":", "ForCode", "-");
        char* temp12 = malloc(20);
        sprintf(temp12 , "%s", $2);
        char* temp13 = malloc(20);
        strcpy(temp13, "If ");
        strcat(temp13, temp12);
        emit(temp13, "OutOfRange", "GOTO", forcreate_temp_label());
    } stmt{
        fortemp_label_counter--;
        char* temp12 = malloc(20);
        strcpy(temp12, $2);
        emit("+", temp12 , "1" , temp12);
        emit("GOTO", "ForCode", "", forcurrLabel());
        fortemp_label_counter++;
        emit(forcurrLabel(), ":", "done", "-");
    };
        | FOR ID ASSIGN e DOWNTO e DO stmt { assign($2);}
    assign_stmt: ID ASSIGN e { assign($1); symbol* s=lookup($1); if(s->type!=NULL) check_expr_type(s, $3);
                emit(":=", $3->name, "", $1); 
        }
        |ID ASSIGN relop {symbol* xyz=malloc(sizeof(symbol)); strcpy(xyz->type,"BOOL"); symbol* s=lookup($1); check_expr_type(s, xyz); assign($1);
                         emit(":=", $3->name, "", s->name); }
        |ID LB e RB ASSIGN e { assign($1); }
    expression: expression LT e 
        | expression GT e 
        | expression LTE e 
        | expression GTE e 
        | expression NE e 
        | expression EQUAL e 
        | expression AND e 
        | expression OR e 
        | NOT e 
        | e { $$ = $1; }    
    relop: e LT e {strcpy($$->name, create_temp_var());
                    emit("<", $1->name, $3->name, $$->name); }
        | e GT e {strcpy($$->name, create_temp_var());
                    emit(">", $1->name, $3->name, $$->name); }
        | e LTE e {strcpy($$->name, create_temp_var());
                    emit("<=", $1->name, $3->name, $$->name); }
        | e GTE e {strcpy($$->name, create_temp_var());
                    emit(">=", $1->name, $3->name, $$->name); }
        | e NE e {strcpy($$->name, create_temp_var());
                    emit("<>", $1->name, $3->name, $$->name); }
        | e EQUAL e {strcpy($$->name, create_temp_var());
                    emit("=", $1->name, $3->name, $$->name); }
        | e AND e {strcpy($$->name, create_temp_var());
                    emit("AND", $1->name, $3->name, $$->name); }
        | e OR e {strcpy($$->name, create_temp_var());
                    emit("OR", $1->name, $3->name, $$->name); }
        | NOT e {strcpy($$->name, create_temp_var());
                    emit("NOT", $2->name, "", $$->name); }  
    e: e PLUS T { $$ = malloc(sizeof(symbol)); 
                        strcpy($$->type, $3->type); 
                    char* temp = create_temp_var();
                    
                    insert(temp);
                    symbol* s = lookup(temp);
                    strcpy(s->type, "INT");
                    strcpy($$->name, s->name);
                    emit("+", $1->name, $3->name, $$->name); 
                        }
        | e MINUS T { $$ = malloc(sizeof(symbol)); 
                    strcpy($$->type, $3->type);
                    strcpy($$->name, create_temp_var());
                    emit("-", $1->name, $3->name, $$->name);
                    } 
        | T { $$ = malloc(sizeof(symbol)); 
                    strcpy($$->type, $1->type);
                    $$ = $1;
                     }
    T: T MULTIPLY f { $$ = malloc(sizeof(symbol)); 
                        if(strcmp($1->type,"REAL")==0) strcpy($$->type, "REAL");
                        else if(strcmp($3->type,"REAL")==0) strcpy($$->type, "REAL");
                        else
                    strcpy($$->type, $3->type); 
                    
                    strcpy($$->name, create_temp_var());
                   // printf("ooooo%s\n",$1->name);
                    emit("*", $1->name, $3->name, $$->name);


                    }
        | T DIVIDE f { $$ = malloc(sizeof(symbol)); strcpy($$->type, "REAL");
                           
                    
                    strcpy($$->name, create_temp_var());
                   // printf("%d\n",temp_var_counter);
                    emit("/", $1->name, $3->name, $$->name);
                   
        }
        | T MOD f { $$ = malloc(sizeof(symbol)); strcpy($$->type, "INT");}  
        | f { $$ = malloc(sizeof(symbol)); 
                    strcpy($$->type, $1->type);
                    $$ = $1; }
    f:  LP e RP { $$ = malloc(sizeof(symbol)); 
                    strcpy($$->type, $2->type); 
                    $$=$2;}
        |ID { check_assigned($1); $$ = malloc(sizeof(symbol)); symbol* s = lookup($1); 
                if(s->type=="INT" || s->type=="REAL")
                    strcpy($$->type, s->type);
                    strcpy($$->name, $1);
                     }
        |ID LB e RB { check_assigned($1); }
        |NUM { $$ = malloc(sizeof(symbol)); sprintf($$->name,"%d",$1); strcpy($$->type, "INT"); }
        |REALNUM { $$ = malloc(sizeof(symbol)); strcpy($$->type, "REAL"); };  
    %%
     
   int main(int argc, char *argv[]) {
    if(argc < 2){
        printf("No filename provided!\n");
        return 1;
    }
    char *filename = argv[1];
    yyin = fopen(filename, "r");
    if(yyin == NULL){
        printf("Error opening file!\n");
        return 1;
    }
    yyparse();
    if(flag==1){
        //printf("valid input\n");
    }
        printf("symbol table\n");
        printf("%-25s %-25s %-25s %-25s\n", "Name", "Type", "Assigned", "isArray");
        for(int i=0;i<symtab_len;i++){
            if(symtab[i].name[0]!='t')
            printf("%-25s %-25s %-25d %-25d\n", symtab[i].name, symtab[i].type, symtab[i].assigned, symtab[i].isArray);
        }
    // printf("quadruple table\n");
    //     for(int i=0;i<quad_len;i++  ){
    //         printf("%-25s %-25s %-25s %-25s\n", quad[i].op, quad[i].arg1, quad[i].arg2, quad[i].result);
    //     }
    fclose(yyin);
    return 0;
}
     
    int yyerror(const char *msg) {
        printf("Syntax error: %s\n", msg);
        return 0;
    }

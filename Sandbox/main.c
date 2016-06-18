//
//  main.c
//  CDev
//
//  Created by Corry Chapman on 1/15/16.
//  Copyright © 2016 CDev. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <ctype.h>
#include "getop.h"
#include <malloc/malloc.h>
#include <setjmp.h>

#define HEXSIZE 20
#define ALLOCSIZE 100000
#define MAXLINES 5000
#define MAXLEN 1000
#define HASHSIZE 101

#define NALLOC 1024

#define MAXTOKENS 100
#define MAXTOKENLEN 64

#define MAXTOKEN 100

#define MAX_BUFFER   1024
#define SPACE        ' '
#define TAB			 8

enum type_tag {IDENTIFIER, QUALIFIER, TYPE};

struct token {
    char type;
    char string[MAXTOKENS];
};

int top = -1;
struct token stack[MAXTOKENS];
struct token this;

#define pop stack[top--]
#define push(s) stack[++top] = s

enum type_tag classify_string();
void gettoken();
void read_to_first_identifier();
void deal_with_arrays();
void deal_with_function_args();
void deal_with_pointers();
void deal_with_declarator();
void parseSyntax();

enum { NAME, PARENS, BRACKETS };

void parseSyntaxKR(void);
void dcl(void);
void dirdcl(void);

int tokentype;
char token[MAXTOKEN];
char name[MAXTOKEN];
char datatype[MAXTOKEN];
char out[1000];
void undcl(void);
void dcl(void);
void dirdcl(void);
int getToken(void);


struct nlist {
    
    struct nlist * next;
    char * name;
    char * defn;
    
};

static struct nlist *hashtab[HASHSIZE];

char hex[HEXSIZE];

static char allocbuf[ALLOCSIZE] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', //
    'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};

static char daytab[][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

static struct tVal {
    char * name;
    char * defn;
} tValTab[] = {
    
    {"IN", "3"},
    {"out", "go away"},
    {"TODAY", "622"},
    {"define_it", "dragon"},
    {"out", "monkey"},
    {"653", "Checking account"},
    {"IN", "jungle"}

};

static char *allocp = allocbuf;

char *lineptr[MAXLINES];

int readlines(char *lineptr[], int nlines);
void writelines(char *lineptr[], int nlines);

// void qSort(char *lineptr[], int left, int right);

void qSort(void *lineptr[], int left, int right,
           int (*comp) (void *, void *));

int numcmp(char *, char *);


int getLine(char *, int);

int isHex(char[]);

void htoi();

void shellSort(int[], int);

void showbits(unsigned int);

void bmTesting();

unsigned getbits(unsigned, int, int);

void printd(int);

char *alloc(int);

void afree(char *);

void seeArray(char[]);
void seePointer(char *);

void pointerTests();
void testWriteLines();

int day_of_year(int, int, int);
void month_day(int, int, int *, int *);

int testPointerToFunction();

int numeric = 0;

struct nlist *lookup(char *);
struct nlist *install(char *, char *);

char *strDup(char *);

void testHash();

void printnList();

void printHash(struct nlist *h);

typedef long Align;

union header{
    
    struct{
        union header *ptr;
        unsigned size;
    } s;
    Align x;
};

typedef union header Header;

static Header base;
static Header *freep = NULL;

void *mallocTest(unsigned);
static Header *morecore(unsigned);

void add_one_v1(int*);
void add_one_v2(int*);

void printTypeLengths();
void morePointerTests();
void createMultiArray();

// void freeMem(void);

// void banana();

// K&R exercises

void printByte();
void KRSandbox();
void enTab1();
void enTab2();
void foldLines();
void removeComments();


int main(int argc, char *argv[]) {
    
    /* htoi();*/
    
    /*int intArray[7] = {6,1,1,3,2,9,1};
    
    shellSort(intArray, 7);*/
    
    /* bmTesting(); */
    
    /* printf("\n Bits for 5775 are:");
    showbits(5775);
    printf("\n Bits are %d\n", getbits(5775, 12, 2)); */
    
    /*  Recursive testing.
        Transformation of chars and ints. */
    
    /*  printd(123);
        printf("\n\n"); */
    
    /*  Getop testing
     char s[10];
     getop(s); */
    
    /* Pointer tests
     char a[] = {'a', 'b', 'c'};
     
     seeArray(a);
     seePointer(a);
     printArray(a);
     
    */
    
    /* pointerTests(); */
    
    /* More pointer tests */
    
    // testWriteLines();
    
    /*  Sort various text lines.  From K&R */
    
   /* int nlines;
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        qSort(lineptr, 0, nlines - 1);
        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Error:  Input too big to sort.\n");
        return 1;
    }
    */
    
    /*  Pointers and multi-dimensional array testing
    
    int year = 1988;
    int month = 1;
    int day = 1;
    int j, k;
    
    int dofyear = day_of_year(year, month, day);
    
    printf("\nDay is %d\n", dofyear);
    
    month_day(year, dofyear, &j, &k);
    
    printf("\nMonth is %d and day is %d\n\n", j, k);
    
    */
    
    // Command-line testing
    
    // args:  echo -wvx
    
 /*   printf("\n %s \n", *argv);          // prints /Users/corrychapman/Library/Developer/Xcode/DerivedData/CDev-extnkxbevppajpfbqwmxthyovifg/Build/Products/Debug/CDev
    printf("\n %s \n", *++argv);        // prints echo
    printf("\n %c \n", (*argv)[0]);     // prints e
    printf("\n %c \n", **argv);         // prints e
    printf("\n %c \n", *++argv[0]);     // prints c
    --argv;
    printf("\n %c \n", (*++argv)[0]);   // prints c; pointer still at second char
    --argv[0];
    printf("\n %c \n", (*argv)[0]);     // prints e;
    printf("\n %c \n", *argv[0]);       // prints e;
    printf("\n %s \n", *++argv);        // prints -wvx
    printf("\n %c \n", *++argv[0]);     // prints w
    printf("\n %c \n", (*argv)[0]);     // prints w
    printf("\n %c \n", *++argv[0]);     // prtins v
 //   printf("\n %c \n", (*++argv)[0]);   // seg fault - no additional argument
 */
    
    // Test pointers to functions.

 /*   if (argc > 1 && strcmp(argv[1], "-n") == 0)
        numeric = 1;
    
    testPointerToFunction();
*/
    
    // Test hash function with linked list.
    
    //  testHash();
    
    // Test memory allocator
    
   /* for (long i = 1; i < 9; i++){
        char !*s = (char *) mallocTest(i * 1000);
        printf("Pointer address is: %p\n", s);
	}
   */
    
    // Prints lengths of types

    // printTypeLengths();
    
    
    // Nuances of pointers.
    // Can add other testing to procedure.
    
    //morePointerTests();
    
    // Parse C syntax
    
   // parseSyntax();
	
    // K&R Parser
    
    // parseSyntaxKR();

	// printByte();  // prints unused bytes within a datatype (int)

	KRSandbox();  // K&R exercises


}

void KRSandbox(){

/*
		  unsigned long tab=8, pos=1;
		  int c;

		  while ((c=getchar()) != EOF) {

			  switch (c) {
		      	  case '\t':
		      		  c=' ';
		      		  while (pos++ < tab) putchar(' ');
		      	  case '\n': pos=0;
		    }

		    putchar(c);
		    if (pos==tab) pos=1;
		    else pos++;

		  }
*/

	// enTab1();
	// enTab2();
	// foldLines();
    removeComments();

}

void removeComments(){
    
    
    char p[] =
    "0/!1 0\"04 0\'05 0.00 1/01 1*!2 1\"/4 1\'/5 1./0 2*!3 2.!2 3/ "
    "03 *!33 .!24 \"004 \\064 .045 \'005 \\075 .056 .047 .05";
    
    int c,i,d;
    char s,n;
    s = '0';
    
    while((c=getchar()) != EOF){
        d=0;
        for(i = 0; p[i] != '\0' && d == 0; i = i+4){
            if(p[i] == s && (p[i+1] == c || p[i+1]=='.')){
                if(p[i+2]=='0')
                    putchar(c);
                else
                    if(p[i+2] == '/'){
                        putchar('/');
                        putchar(c);
                    } else if(p[i+2] ==' ')
                        putchar(' ');
                n = p[i+3];
                d=1;
            }
        }
     
        s = n;
    }
}

void foldLines(){

	int counter = 0, length = 50, lastSpace = 0, c;
    char buf[100], t;

		while ((c = getchar()) != EOF){

			if (c == '\n'){
				buf[counter++] = c;
				buf[counter] = '\0';
				printf("%s", buf);
                counter = 0;
                c = getchar();
			}

			buf[counter++] = c;

            if (c == ' ') lastSpace = counter-1;

			if (counter > 0 && counter%length == 0){
                
                if (lastSpace >= (counter - 7))  // Go back at least 6 chars to split
                    buf[lastSpace] = '\n';
                
                else {
                    // Long word or nonsense.  Just break the text
                    t = buf[counter-1];
                    buf[counter-1] = '\n';
                    buf[counter++] = t;
                }
            }

		}
}


void enTab1(){

		int c, pos = 1, tab = 8, blanks = 0;

		while ((c = getchar()) != EOF){

				  while (c == ' '){

					  if (pos == tab){
						  putchar('\t');
						  pos = 1;
						  blanks = 0;
					  } else {
						  blanks++;
					  	  pos++;
					  }

					  c = getchar();

				  }

				  if (blanks){
					  while (blanks-- > 0) putchar(' ');
					  blanks = 0;
				  }

				  if (c == '\n') pos = 0;

				  putchar(c);

				  if (pos == tab) pos = 1;
				  else pos++;

			  }
}

void enTab2(){

	/*


    		 int p = 0;
		     int blanks = 0;
		     char chunk[TAB+2];
		     int c;

		     while((c=getchar()) != EOF) {
		         chunk[p++] = c;
		         if(c == ' ')
		             ++blanks;
		         else
		             blanks = 0;
		         if(p == TAB || c == '\n') {
		             chunk[p] = '\0';
		             if(blanks > 1) {
		                 p -= blanks;
		                 chunk[p] = '\t';
		                 chunk[p+1] = '\0';
		             }
		             printf("%s", chunk);
		             p = blanks = 0;
		         }
		     }
		     if(p > 0) {
		         chunk[p] = '\0';
		         printf("%s", chunk);
		     }

		     */


}

void printByte(){

	// Prints memory addresses not in use by 4 byte integer
	// type when integer is less than 1 byte.
	// Written to try and understand how memory addresses in C
	// are mapped sequentially based on byte-size of
	// data type (byte=addressable memory).
	// This routine is able to access the "empty" bytes
	// of a small integer by casting first integer to void
	// and incrementing.  Since void type is 1 byte (on my machine),
	// can look at how integer is stored in byte cells.
	// Actually, this doesn't work.  Pointer arithmetic on a void
	// is undefined behavior.  Won't work if integer is > 1 byte.


	int ia[] = {2147483647, 3, 4, 7};

	printf("Address of Int Array 0 is: %p\n", &ia[0]);
	printf("Address of Int Array 1 is: %p\n", &ia[1]);
	printf("Address of Int Array 2 is: %p\n", &ia[2]);
	printf("Address of Int Array 3 is: %p\n", &ia[3]);

	void *addr = (void *) &ia[0];

	for (int i = 0; i < sizeof(ia); i++){

		printf("\nAddress:  %p\n", addr);
		printf("Data: 0x%08x == %u\n", *((unsigned int*) addr), *((unsigned int*) addr));
		addr = addr+1;
	}

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));

	addr = addr+1;

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));

	addr = addr+1;

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));

	addr = addr+1;

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));

	addr = addr+1;

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));

	addr = addr+4;

	printf("\nAddress: %p\n", addr);
	printf("Data:  %d\n", *((int*) addr));


}

void parseSyntax(){
    
    read_to_first_identifier();
    deal_with_declarator();
    printf("\n");
    
}

void parseSyntaxKR(){
    
    while (getToken() != EOF){
        
        strcpy(datatype, token);
        out[0] = '\0';
        dcl();
        if (tokentype != '\n')
            printf("Syntax Error.\n");
        printf("%s:  %s %s\n", name, out, datatype);
    }
    
}

int getToken(void){
    
    int c;
    char *p = token;
    
    while ((c = getchar()) == ' ' || c == '\t')
        ;
    
    if (c == '('){
        
        if ((c = getchar()) == ')') {
            strcpy(token, "()");
            return tokentype = PARENS;
        } else {
            ungetc(c, stdin);
            return tokentype = '(';
        }
    
    } else if (c == '['){
       
        for (*p++ = c; (*p++ = getchar()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
        
    } else if (isalpha(c)) {
        
        for (*p++ = c; isalnum(c = getchar()); )
            *p++ = c;
        *p = '\0';
        ungetc(c, stdin);
        return tokentype = NAME;
        
    } else
        
        return tokentype = c;
    
}

void dcl(void){
    
    int ns;
    
    for (ns = 0; getToken() == '*';)
        ns++;
    
    dirdcl();
    while (ns-- > 0)
        strcat(out, " pointer to");
    
}

void dirdcl(void){
    
    int type;
    
    if (tokentype == '('){
        dcl();
        if (tokentype != ')')
            printf("Error:  Missing )\n");
    } else if (tokentype == NAME)
        strcpy(name, token);
    else
        printf("Error: Expected name or (dcl)\n");
    
    while ((type = getToken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    
}

void undcl(void){
    
    int type;
    char temp[MAXTOKEN];
    
    while (getToken() != EOF){
        
        strcpy(out, token);
        
        while ((type = getToken()) != '\n')
            
            if (type == PARENS || type == BRACKETS){
                
                strcat(out, token);
            
            }   else if (type == '*') {
                
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
                
            } else if (type == NAME){
                
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
                
            } else
                
                printf("Invalid input at %s\n", token);
        
        printf("%s\n", out);
    }
    
}

enum type_tag classify_string(){
    
    char *s = this.string;
    
    if (!strcmp(s, "const")){
        strcpy(s, "read-only");
        return QUALIFIER;
    }
    
    if (!strcmp(s, "volatile")) return  QUALIFIER;
    if (!strcmp(s, "void")) return TYPE;
    if (!strcmp(s, "char")) return TYPE;
    if (!strcmp(s, "signed")) return TYPE;
    if (!strcmp(s, "unsigned")) return TYPE;
    if (!strcmp(s, "short")) return TYPE;
    if (!strcmp(s, "int")) return TYPE;
    if (!strcmp(s, "long")) return TYPE;
    if (!strcmp(s, "float")) return TYPE;
    if (!strcmp(s, "double")) return TYPE;
    if (!strcmp(s, "struct")) return TYPE;
    if (!strcmp(s, "union")) return TYPE;
    if (!strcmp(s, "enum")) return TYPE;
    
    return IDENTIFIER;
    
}

void gettoken(){
    
    char *p = this.string;
    
    while ((*p = getchar()) == ' ');
    
    if (isalnum(*p)){
  
        while ( isalnum(*++p = getchar()));

        ungetc(*p, stdin);
        *p = '\0';

        this.type = classify_string();
        return;
    
    }
    
    if (*p == '*'){
        
        strcpy(this.string, "pointer to");
        this.type = '*';
        return;
        
    }
    
    this.string[1] = '\0';
    this.type = *p;
    return;
    
}

void read_to_first_identifier(){
    
    gettoken();
    
    while (this.type != IDENTIFIER){
        push(this);
        gettoken();
    }
    
    printf("%s is ", this.string);

    gettoken();
    
  //  printf("\nItems on stack:\n");
  // for (int i = 0; i < 20; i++){
  //  	struct token t = stack[i];
  //  	printf("token string is: %s\n", t.string);
  //  	printf("token type is: %c\n", t.type);
  //  }


}

void deal_with_arrays(){
    
    while (this.type == '['){
        printf("array ");
        
        gettoken();
        
        if (isdigit(this.string[0])){
            printf("0..%d ", atoi(this.string)-1);
            gettoken();
        }
        
        gettoken();
        printf("of ");
    }
}

void deal_with_function_args(){
    
    while (this.type != ')'){
        gettoken();
    }
    
    gettoken();
    printf("function returning ");
    
}

void deal_with_pointers(){
    
    while (stack[top].type == '*'){
        printf("%s ", pop.string );
    }
}

void deal_with_declarator(){
    
    switch (this.type){
        case '[' : deal_with_arrays(); break;
        case '(' : deal_with_function_args();
    }
    
    deal_with_pointers();
    
    while (top >= 0){
        
        if (stack[top].type == '('){
            pop;
            gettoken();
            deal_with_declarator();
            
        } else {
            printf("%s ", pop.string);
        }
    }
}

void morePointerTests(){
    
    createMultiArray();
    
   
    /*
    int ary[2] = {63, -63};
    int *ptr = ary;
    
    // Can change dereferenced value of pointer
    // but can't change address pointer points to
    // inside this routine.
    
    add_one_v1(ptr);
    
    printf("@ %p\n", ptr);
    printf("%d\n", *(ptr));
    printf("%d\n\n", *(ptr+1));
    */
    /* 
     v1: pre:   p = 0x7fff5fbff7d0
     v1: pre:  *p = 63
     v1: post:  p = 0x7fff5fbff7d0
     v1: post: *p = 64
     @ 0x7fff5fbff7d0
     64
     -63
     */
    
   /* add_one_v2(ptr);
    
    printf("@ %p\n", ptr);
    printf("%d\n", *ptr);
    printf("%d\n", *(ptr+1));
    */
    /*
     v2: pre:   p = 0x7fff5fbff7d0
     v2: pre:  *p = 64
     v2: post:   p = 0x7fff5fbff7d4
     v2: post:  *p = -63
     v2: post:   q = 64
     @ 0x7fff5fbff7d0
     64
     -63
     */

}

void add_one_v1(int *p){
    
    printf("v1: pre:   p = %p\n",p);
    printf("v1: pre:  *p = %d\n",*p);
    
    // changes value that pointer points to;
    // persists in calling routine.
    *p = *p + 1;
    // same as *p = ++(*p);
    
    printf("v1: post:  p = %p\n",p);
    printf("v1: post: *p = %d\n",*p);

}

void add_one_v2(int *p){
    
    printf("v2: pre:   p = %p\n",p);
    printf("v2: pre:  *p = %d\n",*p);
    
    // dereferences p into q, then advances pointer
    // advancement does not persist into calling routine.
    int q = *p++;
    
    printf("v2: post:   p = %p\n",p);
    printf("v2: post:  *p = %d\n",*p);
    printf("v2: post:   q = %d\n",q);
    
}

void createMultiArray(){
    
    // Creating a multi-dimensional array.
    // This creates a series of rows with increasing columns.
    // Pointers to pointers are sequential in memory, 8 bytes each.
    
    int rows = 3;
    
    printf("Size of int* is %lu\n", sizeof(int*));  // Int is 4 bytes.  Int* is 8 bytes
    
    int ** ptrtab = (int**) malloc(rows * sizeof(int*));
    
    size_t memSize = malloc_size(ptrtab);  // Returns 32?  Pointer to pointer?
    
    printf("Bytes allocated by malloc for ptrtab is: %lu\n", memSize);
    printf("Size of ptrtab is: %lu\n\n", sizeof(ptrtab));  // 8 bytes
    
    size_t sum = 0;
    
    for (int r = 0; r < rows; r++){
        
        ptrtab[r] = (int*) malloc(sizeof(int) * (r+1));
        
        // malloc returns memory blocks that are multiples of 16, depending on # of rows.
        // Each block will hold 4 ints, or columns.
        
        printf("For row %d, allocating %lu bytes\n", r, (sizeof(int) * (r+1)));
        
        printf("Size of row %d allocated by malloc is: %lu\n", r,  malloc_size(ptrtab[r]));
        
        sum += malloc_size(ptrtab[r]);
    }
    
    printf("Sum of rows is %lu\n\n", sum);
    
    // Add elements to array.
    // Pointers to pointers are sequential, but the memory they point to may not be.
    // Thus, for row 0, may add 4 intengers that are accessible via indexes, since
    // the row has 16 bytes.
    // In fact, may add as many extra elements as desired.  Rather than a segfault,
    // subsequent row elements may overwrite index slots beyond that allocated
    // when initializing columns.
    // Thus this is not a true array but rather a series of pointer to pointers that
    // point to memory where you are guaranteed to find the values assigned if you use
    // the appropriate index value.
    // Extra memory slots may exist for a particular row, depending on the row allocation,
    // which depends on the row being created, the size of int, and whether the final number
    // is less than or greater than a multiple of 16.
    
    ptrtab[0][0] = 22;
    ptrtab[1][0] = 99;
    ptrtab[1][1] = 109;
    ptrtab[2][0] = 7;
    ptrtab[2][1] = 65;
    ptrtab[2][2] = 808;
    
    
    printf("\nRow pointer points to: %p\n", ptrtab);
    printf("Column poiner points to: %p\n\n", *ptrtab);
    printf("Here: %p, %d\n", *ptrtab, **ptrtab);
    
    ptrtab++;
    
    printf("\nRow pointer points to: %p\n", ptrtab);
    printf("Column poiner points to: %p\n\n", *ptrtab);
    printf("Here: %p, %d\n", *ptrtab, *(*ptrtab)++);
    printf("Here: %p, %d\n\n", *ptrtab, **ptrtab);
    
    ptrtab++;
    
    printf("\nRow pointer points to: %p\n", ptrtab);
    printf("Column poiner points to: %p\n\n", *ptrtab);
    printf("Here: %p, %d\n", *ptrtab, *(*ptrtab)++);
    printf("Here: %p, %d\n", *ptrtab, *(*ptrtab)++);
    printf("Here: %p, %d\n\n", *ptrtab, **ptrtab);
    
}

void printTypeLengths(){

     printf("%d byte for chars\n", sizeof(char));
     printf("%d byte for shorts\n", sizeof(short int));
     printf("%d byte for ints\n", sizeof(int));
     printf("%d byte for longs\n", sizeof(long int));
     printf("%d byte for long longs\n", sizeof(long long int));
     printf("%d byte for floats\n", sizeof(float));
     printf("%d byte for doubles\n", sizeof(double));
     printf("%d byte for pointers\n", sizeof(int*));
     printf("%d byte for void\n", sizeof(void));

    
    /*
     
     1 byte for chars
     2 byte for shorts
     4 byte for ints
     8 byte for longs
     8 byte for long longs
     4 byte for floats
     8 byte for doubles
     8 byte for pointers
     
     */
     
     
     
}

void *mallocTest(unsigned nbytes){
    
    Header *p, *prevp;
    unsigned nunits;
    
    printf("\nSize of Header is %d\n", sizeof(Header));
    printf("\nBytes requested is %d\n", nbytes);

    nunits = (nbytes + sizeof(Header)-1)/sizeof(Header) + 1;
    
    if ((prevp = freep) == NULL){
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    
    for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr){
        
        if (p->s.size >= nunits) {
            if (p->s.size == nunits)
                prevp->s.ptr = p->s.ptr;
            else {
            	printf("Pointer size is %d\n", p->s.size);
            	printf("nunits is %d\n", nunits);
                p->s.size -= nunits;
                // changes size of prevp
                p += p->s.size;
                p->s.size = nunits;
                printf("Original pointer size is %d\n", prevp->s.ptr->s.size);
                // does not change size of prevp
            }
            freep = prevp;
            printf("\nReturning pointer to %p\n",p);
            return (void *)p+1;
        }
        if (p == freep)
            if ((p = morecore(nunits)) == NULL)
                return NULL;
    }

    return NULL;
}

static Header *morecore(unsigned nu){
    
    char *cp;
    Header *up;
    
    if (nu < NALLOC)
        nu = NALLOC;
    
    cp = sbrk(nu * sizeof(Header));
    
    if (cp == (char *) - 1)
        return NULL;
    
    printf("\nmorecore called.\n");
    printf("\nNumber of units requested is %d\n", nu);
    printf("\nSize of Header is: %lu\n", sizeof(Header));
    printf("\nSize of block is %lu\n", (nu * sizeof(Header)));

    up = (Header *) cp;
    up->s.size = nu;

    free((void *)(up + 1));

    // Adds 16 to *up address, which is size of Header

    return freep;
    
    
}

void free(void *ap){

	printf("\nFree called.\n");
    
    Header *bp, *p;
    
    bp = (Header *)ap - 1;
    
    for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
      
        if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
            break;
            
    if (bp + bp-> s.size == p->s.ptr){
        bp->s.size += p->s.ptr->s.size;
        bp->s.ptr = p->s.ptr->s.ptr;
        
    } else
        bp->s.ptr = p->s.ptr;
    
    if (p + p->s.size == bp){
        p->s.size += bp->s.size;
        p->s.ptr = bp->s.ptr;
    } else
        p->s.ptr = bp;
            
    freep = p;
    
}

void testHash(){
    
    struct tVal v;
    
    for (int i = 0; i < 7; i++){
        
        v = tValTab[i];
        install(v.name, v.defn);
    }
    
    printnList();
    
}

void printnList(){
    
    struct nlist *np;
    
    for (int i = 0; i < HASHSIZE; i++){
        
        if ((np = hashtab[i]) !=  NULL){
            printf("\nFound key: %d", i);
            printHash(np);
        }
 
    }
}

void printHash(struct nlist *np){
    
    printf("\nName is: %s", np->name);
    printf("\nDefn is: %s\n", np->defn);
    
    if (np->next){
        printf("Going to linked node.\n");
        printHash(np->next);
    }
}

char *strDup(char *s){
    
    char *p;
    
    p = (char *) malloc(strlen(s)+1);
    
    if (p != NULL)
        strcpy(p, s);
    
    return p;
}

unsigned hash(char *s){
    
    unsigned hashval;
    
    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;

   // return hashval % HASHSIZE;
    return 18;
}

struct nlist *lookup(char *s){
    
    struct nlist *np;
    
    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;
    
    return NULL;
    
}

struct nlist *install(char *name, char *defn){
    
    struct nlist *np;
    unsigned hashval;
    
    if ((np = lookup(name)) == NULL){
    
        np = (struct nlist *) malloc(sizeof(*np));
        
        if (np == NULL || (np->name = strDup(name)) == NULL)
            return NULL;
        
        hashval = hash(name);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    
    } else
        
        free((void *) np->defn);
        
    if ((np->defn = strDup(defn)) == NULL)
        return NULL;
    
    return np;
    
}



int testPointerToFunction(){
    
    int nlines;
    
    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        
        qSort((void **)lineptr, 0, nlines - 1,                          // will also run as qSort((void *)
              (int (*)(void *, void *))(numeric ? numcmp : strcmp));    // as void * can be any type.
        writelines(lineptr, nlines);
        return 0;
        
        /*    qSort((void **)lineptr, 0, nlines - 1,
         (int (*) (void *, void *)) numcmp);
         writelines(lineptr, nlines);
         return 0;
         */
        
    } else {
        
        printf("Input too big to sort.\n");
        return 1;
        
    }
    
}
void qSort(void *v[], int left, int right,
           int (*comp) (void *, void *)){
    
    int i, last;
    
    void swap(void *v[], int, int);
    
    if (left >= right)
        return;
    
    swap(v, left, (left + right)/2);
    last = left;
    for (i = left+1; i <= right; i ++)
        if ((*comp)(v[i], v[left]) < 0)
            swap(v, ++last, i);
    swap(v, left, last);
    qSort(v, left, last-1, comp);
    qSort(v, last+1, right, comp);


}

int numcmp(char *s1, char *s2){
    
    double v1, v2;
    
    v1 = atof(s1);
    v2 = atof(s2);
    
    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
    
}

void swap(void *v[], int i, int j){
    
    void *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

int day_of_year(int year, int month, int day){
    
    
    int i, leap;
    
    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    
    // Implementation with pointers.

    char (*ptodaytab)[13] = daytab;
    
    if (leap) ++ptodaytab;
    
    for (i = 1; i < month; i++){
        
        ptodaytab = *ptodaytab+1;
        day += **ptodaytab;
    
    }
   
    //  Implementation with arrays.
    //
    //  for (i = 1; i < month; i++)
    //    day += daytab[leap][i];
    
    return day;
}

void month_day(int year, int yearday, int *pmonth, int *pda){
    
    int i, leap;
    
    leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
    
    // Implementation with pointers.
    
    char (*ptodaytab)[13] = daytab;
    
    if (leap) ++ptodaytab;
    
    for (i = 0; yearday > **ptodaytab; i++){
        yearday -= **ptodaytab;
        ptodaytab = *ptodaytab+1;
    }

  
    // Implementation with arrays.
    
    // for (i = 1; yearday > daytab[leap][i]; i++)
    //   yearday -= daytab[leap][i];
    
    *pmonth = i;
    *pda = yearday;
    
}


void testWriteLines(){
    
    // Tests to understand pointers and arrays of pointers.
    
    char *s = "hey buddy";
    char *p;
    p = alloc(30);
    strcpy(p,s);
    lineptr[0] = p;
    char *d = "i love you";
    char *r = alloc(30);
    strcpy(r,d);
    lineptr[1] = r;
    writelines(lineptr, 2);
    
}

int readlines(char *lineptr[], int maxlines){
    
    int len, nlines;
    char *p, line[MAXLEN];
    
    nlines = 0;
    
    while ((len = getLine(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = alloc(len)) == NULL)
            return -1;
        else {
            line[len - 1] = '\0';
            strcpy(p, line);
            lineptr[nlines++] = p;
            
        }

    return nlines;
}

void writelines(char *lineptr[], int nlines){
    
    /* printf("\n%s\n", lineptr);          // prints \200
    printf("\n%s\n", *lineptr);         // prints hey buddy
    printf("\n%s\n", lineptr[0]);       // prints hey buddy
    //  printf("\n%s\n", *lineptr[0]);   // seg fault -- can't pass single char to %s
    printf("\n%c\n", *lineptr[0]);      // prints h
    printf("\n%c\n", *++lineptr[0]);    // prints e
    printf("\n%c\n", *lineptr[0]);      // prints e
    printf("\n%c\n", (*lineptr)[0]);    // prints e
    
    printf("\n%c\n", **++lineptr);      // prints i. Advances pointer to second string, prints pointer to first char. (**)
    printf("\n%c\n", *++*lineptr);      // prints blank space
    printf("\n%c\n", *++*lineptr);      // prints l
                                        // *lineptr deref to pointer to array of char (string) -->
                                        // ++*lineptr increments position pointed to in array (string) -->
                                        // *++*lineptr deref character!
                                        // More complex:  *++*++lineptr:  iterates pointer to next string, 
                                        // iterates char in string, prints char!
    
    --lineptr;                          // go back to 1st string.
    printf("\n%s\n", *lineptr);         // prints ey buddy; pointer still on 2nd character of 1st string.
    --lineptr[1];                       // move pointer to char on lineptr[1] back to beginning.
    --lineptr[1];
    printf("\n%c\n", *lineptr[1]);      // prints i
    printf("\n%c\n", (*++lineptr)[0]);  // prints i.  Advances pointer to [1] and prints first char. [] binds first, if no parentheses.
                                        // "i love you" is now in position [0];  position [1] is null.  If no parentheses, would print "y"
    printf("\n%s\n", lineptr[1]);       // prints null
    --lineptr;
    printf("\n%s\n", lineptr[1]);       // prints i love you
    printf("\n%s\n", *++lineptr);       // prints i love you; dereferenced name always points to first variable;
                                        // in this case, lineptr has been advanced one.
*/

    // new pointer points to same address as lineptr.
    // iterations of lineptr DO NOT iterate copyLP.
    // changing data lineptr points to changes copyLP.
    
    int x = nlines;
    char **copyLP = lineptr;
    
    
    //  uses lineptr as POINTER to print strings.
    //  *lineptr returns char *
    //  %s argument of printf takes char *
    //  and prints chars until \0
    
    while (nlines-- > 0)
        printf("%s\n", *lineptr++);

    
    // uses lineptr as ARRAY to print strings.
    // moves pointer along indexed string.
    // have to use copy of lineptr because previous
    // loop moved to end of pointer.
    
    for (int i = 0; i < x; i++){
        
        while (*copyLP[i] != '\0')
            printf("%c", *copyLP[i]++);
        
        printf("\n");
        
    }
    
    
}

int getLine(char *s, int lim){
    
    int c, i;
    
    i = 0;
    
    while (--lim > 0 && (c = getchar()) != EOF && c != '\n')
           s[i++] = c;
    
    if (c == '\n')
           s[i++] = c;
    
    s[i] = '\0';
    
    return i;
    
}

/*
void qSort(char *v[], int left, int right){
    
    printf("\nqSort called\n");
    printf("left is %d and right is %d\n", left, right);
    
    int i, last;
    void swap(char *v[], int i, int j);
    
    if (left >= right){
        printf("\nLeft >= to right.  Exit qSort\n");
        return;
    }
    
    printf("Calling swap with left: %d and (left+right)/2: %d\n", left, (left+right)/2);
    swap(v, left, (left + right)/2);
    last = left;
    printf("\nlast set to %d\n", last);
    for (i = left+1; i <= right; i++){
        printf("\nOrder of strings is:\n");
        printf("%s\n", v[0]);
        printf("%s\n", v[1]);
        printf("%s\n", v[2]);
        printf("%s\n", v[3]);
        printf("%s\n", v[4]);
        printf("%s\n", v[5]);
        printf("%s\n", v[6]);
        printf("%s\n", v[7]);
        printf("%s\n", v[8]);
        
        
        printf("\nqSort loop.  Comparing elements %d and %d\n", i, left);
        if (strcmp(v[i], v[left]) < 0){
            printf("Called strcmp.  i is %d and left is %d\n", i, left);
            printf("Called strcmp:  Is %s < %s?\n", v[i], v[left]);
            printf("Calling swap with last incremented by one: %d and iterator i: %d:\n", last+1, i);
            swap(v, ++last, i);
        }
    }
    
    

    printf("\nExiting inner qSort loop.  Last set to %d\n", last);
    printf("Calling swap with left: %d and last: %d\n", left, last);
    swap(v, left, last);
    
    printf("\nCalling recursive sSort with left: %d and last-1:%d\n", left, last-1);
    qSort(v, left, last-1);
    printf("\nCalling second recursive qSort with last+1: %d and right: %d\n", last+1, right);
    qSort(v, last+1, right);
    printf("\nExiting qSort\n");
    
}

void swap(char *v[], int i, int j){
    
    printf("Swap called.  Swapping elements %d and %d\n", i, j);
    
    char *temp;
    
    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

*/

void pointerTests(){
    
    /*  allocbuf is the char array with which the pointers used
     in alloc() and afree() and in calls below will work.
     They must use the same array to do comparisons.
     */
    
    /*  First use alloc. Move the pointer ahead 3 chars to letter 'd'.
     alloc RETURNS a different pointer that is at the beginning of the range
     checked, in this case, 'a'.  Slots at this point could be filled.
     */
    
    /*  afree takes a pointer set at a different slot in the array
     and substitutes it for the current pointer.
     */
    
    char *aChar = alloc(2);
    
    printf("\nalloc called for 2 spaces.\n");
    printf("\nallocp has been set to:  %c\n", *allocp);
    printf("\nalloc returned pointer set to:  %c\n", *aChar);
    printf("\n\nCreate new pointer to allocbuf.  Advance 5 spaces.\n");
    
    char *newChar = allocbuf;
    
    for (int i = 0; i < 5; i++)
        newChar++;
    
    printf("\nNew pointer set to:  %c\n", *newChar);
    
    afree(newChar);
    
    printf("\n\nafree called.\n");
    printf("\nallocp now set to: %c\n", *allocp);
    printf("\nPointer from initial alloc set to:  %c\n", *aChar);
    printf("\n\nCall alloc again, for 5 spaces.\n");
    
    aChar = alloc(5);
    
    printf("\nallocp has been set to: %c\n", *allocp);
    printf("\nallocp returned pointer set to:  %c\n", *aChar);

}

char *alloc(int n){
    
    if (allocbuf + ALLOCSIZE - allocp >= n){
        allocp += n;
        
        /*  'allocp += n' is an _assignment_.
            Moves the pointer 4 places along the array it points to.  
            'allocp - n' is not an asssignment unless returned.
            If not returned, creates an unused pointer set 'n' spaces back.
            allocp is unaffected and remains set += n spaces ahead.
         */
         
        return allocp - n;
        
    } else {
        return 0;
    }
    
}

void afree(char *p){
    
    if (p >= allocbuf && p < allocbuf + ALLOCSIZE)
        allocp = p;
    
}

/*  The following two functions return same results
    as array A is equivalent to pointer to A[0]
*/

void seeArray(char a[]){
    
    char *pa = a;
    
    printf("\n Value of a[0] is %c\n", *pa);
    
    char *ap = &a[0];
    
    printf("\n Value of a[0] is %c\n", *(ap++));
    
    printf("\n Now at value of: %c\n", *ap);
    
    printf("\n Now at value of: %c\n", *(ap + 1));
    
}

void seePointer(char *a){
    
    char *pa = a;
    
    printf("\n Value of a[0] is %c\n", *pa);
    
    char *ap = &a[0];
    
    printf("\n Value of a[0] is %c\n", *(ap++));
    
    printf("\n Now at value of: %c\n", *ap);
    
    printf("\n Now at value of: %c\n", *(ap + 1));
    
    *(++ap) = 'x';
    --ap;
    --ap;
    

    //printArray(ap, 30);

}



void printd(int n){
    
    if (n < 0) {
        putchar('-');
        n = -n;
    }
    
    
    if (n/10)
        printd(n/10);
    
    printf("\nPrintd called.  Variable n is:  %d\n", n); 
    
    putchar(n % 10 + '0');
    
    /*
     
     The reason to use modulus in this recursive function is that for a
     number such as '12', we only want to work with one digit (the 2, for example)
     at a time, and we want it as an int.
     
     Modulus returns an actual int, not the ASCII value for an integer char.
     We ADD char '0' to the int to give us the char [int] spaces beyond '0'.
     
     When we are working with chars of ints (ex., atoi functions turning text
     numbers into integers), we SUBTRACT '0' from the char int to give the ASCII
     value for the char, to return as an int.
     
     Thus:
     
     1.  Convert int into char, ADD '0' (48) to int value.
     
     2.  Convert char into int, SUBTRACT '0' from char value.
     
     */
    
    
    /* Create array of chars using int n and sprintf */
    
    /* char buffer[25] = {};
     sprintf(buffer, "%d",n); */
    
    /* Convert char '1' to true int 1.
       SUBTRACT 48 ('0') from '1' (49) to give int of 1. */
    
    /* int j = buffer[0] - '0'; */
    
    /* Check results */
    
    /* printf("\nConvert char to int using SUBTRACTION:\n");
    printf("\nBuffer[0] holds char:  %c\n", buffer[0]);
    printf("\nBuffer[0] holds int:  %d\n", buffer[0]);
    printf("\nBuffer[0] - '0' (48) is int:  %d\n", j); */
    
    /*  Convert true int 1 to char '1'.
        ADD 48 ('0') to int 1 to give int 49, which is char '1'. */
    
    /*  char k = j + '0'; */
    
    /*  Check results */
    
    /* printf("\nConvert int to char using ADDITION:\n");
    printf("\nInt j is:  %d\n", j);
    printf("\nInt j + '0' value is: %d\n", j + '0');
    printf("\nInt j + char '0' is:  %c\n", k); */

}

void bmTesting(){
    
    int j = 5225, m, n;
    
    printf("The decimal %d is equal to binary = ", j);
    
    showbits(j);
    
    for (m = 0; m <=5; m++){
        n = j >> m;
        printf("%d right shift %d gives \n", j, m);
        showbits(n);
    }
}

unsigned getbits(unsigned x, int p, int n){
    
    /* get bits n from position p */
    
    unsigned t = (x >> (p + 1 - n));
    unsigned w = ~(~0 << n);
    
    showbits(t);
    showbits(w);
    showbits(t & w);
    return t & w;
    
    
    /*return (x >> (p + 1 - n)) & ~(~0 << n);*/
    
}

void showbits(unsigned int x){
    
    int i;
    
    /* Binary 5225 = 0001 0100 0110 1001 */

    /*  (x & (1 << i)) ? putchar('1') : putchar('0');*/

    for (i = (sizeof(int)*8-1); i >= 0; i--)
    {
        long y = (x&(1<<i));
        
        if (y > 0){
            putchar('1');
        } else {
            putchar('0');
        }
/*        putchar('1');
        
        if (y > 0) putchar('1');
            else putchar('0');
  */
    }
    
    printf("\n");
}


void htoi(){
    
    do {
        
        printf("Enter a number: ");
        
        fgets(hex, HEXSIZE, stdin);
        
        if (strcmp(hex, "Quit\n") == 0) break;
        
        if (isHex(hex))
            printf("Hex is %lu \n", strtol(hex, NULL, 16));
        else
            printf("Not a hex.  Try again.\n");
        
    } while (1);
}

int isHex(char hex[]){
    
    for (int i = 0; i < HEXSIZE; i++){
        
        if (hex[i] >= '0' && hex[i] <= '9')
            continue;
        else if ((hex[i] >= 'A' && hex[i] <= 'F') || (hex[i] >= 'a' && hex[i] <= 'f'))
            continue;
        else if ((i == 1) && ((hex[i] == 'X' || hex[i] == 'x')))
            continue;
        else if (hex[i] == '\n') return 1;
        else return 0;
    }
            
    return 1;
}


void shellSort(int v[], int n){
    
    int gap, i, j, temp = 0;

    for (gap = n/2; gap > 0; gap /=2){
      /*  printf("\nFirst loop:  gap is %d, i is %d\n", gap, i);*/
        for (i = gap; i < n; i++){
            printf("\nSecond loop:  gap is equal to n/2, decrements by division by 2:  %d; i starts as gap and increments by one:  %d\n", gap, i);
            for (j=i-gap; j>=0 && v[j] > v[j+gap]; j -= gap){
                printf("\nThird loop:  gap is %d, i is %d, j is i-gap, decrements by subtraction of gap: %d", gap,i,j);
                printf("\n*** If j (%d) is >= 0 and item[j] (%d) in array is greater than item v[j+gap] (%d+%d), then do the following:***\n", j,j,j,gap);
                printf("\n Right now, array is:\n");
               // printArray(v, 30);
                temp = v[j];
                printf("\n Temp variable is v[j] or: %d\n", v[j]);
                printf("\n Set v[j] to v[j+gap] or v[%d]\n", j+gap);
                v[j] = v[j+gap];
                printf("\n Set v[j+gap] to temp\n");
                v[j+gap] = temp;
                printf("\nArray is now:\n");
               // printArray(v, 30);
            }
        }
    }
}



                
                


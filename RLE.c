#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>
/*Shuhao Zhang
  Using std=c99 decode
*/

int main(int argc, char **argv){
    char str1[40];
    if (argc < 3){
        printf("Error: No input file specified!");
	exit(1);
    }
    if (argc >= 1){
	if (strcmp(argv[2],"e") != 0 && strcmp(argv[2],"d") != 0){
	    printf("invald Usage, expected: RLE {%s} [e | d] to the console", argv[1]);
            exit(4);
	}
    }
    FILE *filePointer;
    filePointer = fopen(argv[1], "r");
    if (access(argv[1], R_OK) == -1){
        printf("Read error: file not found or cannot be read");
        exit(2);
    }
    fgets(str1, sizeof(char) * 40 , filePointer);
    for (int i = 0; i < strlen(str1); i++){
        if ((str1[i] == ' ' && str1[i+1] != ' ') || (str1[i] != 'A' && str1[i] != 'C' && str1[i] != 'T'  && str1[i] != 'G' && str1[i] > '9')){
            printf("Error: Invalid format");
            exit(3);
        }
    }
    
    if (strcmp(argv[2], "e") == 0){
        encode(str1);
    }

    if (strcmp(argv[2], "d") == 0){
        decode(str1);
    }

}
void encode(char c[]){
   
    int count = 1;

    for (int i = 0; i < 40; i = i + 2){
        if (c[i] != 'A' && c[i] != 'C' && c[i] != 'T' && c[i] != 'G' ){
            printf("Error: String could not be encoded");
            exit(5);
        }
    }

    for (int i = 0; i < strlen(c);i++){
	if (c[i] == c[i+1] || c[i+1] == '\0'){
            count++;
        }
        if (c[i] != c[i+1] || c[i+1] == '\0'){
            printf("%c%d", c[i], count);
            count = 1;
        }
    }
    exit(0);
}
void decode(char c[]){

    for (int i = 0; i < strlen(c); i = i + 2){
        if ((c[i] != 'A' && c[i] != 'C' && c[i] != 'T' && c[i] != 'G' ) && ((int)(c[i+1])< 0 || (int)(c[i+1])> 9 )){
            printf("Error: String could not be decoded");
            exit(5);
        }
    }

    for (int i = 0; i < strlen(c);i = i + 2){
        int times = (int)(c[i+1]) - 48;
	for (int j = 0; j < times;j++){
	    printf("%c", c[i]);
	}
    }
    exit(0);
}

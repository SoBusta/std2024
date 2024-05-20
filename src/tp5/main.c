#include <stdio.h>

unsigned long int hashFunction(void *key){
    const char* string = (const char *) key;
    unsigned long int hash;

    printf("%s\n", string);

    return hash;
}

int main()
{
    hashFunction("chat");
    
    return 0;
}

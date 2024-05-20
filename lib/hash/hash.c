#include <stdlib.h>
#include <math.h>
#include <string.h>

#include "./../list/list.h"
#include "hash.h"

#define ALPHABET_SIZE 26

unsigned long int hashFunction(void* key){
    const char* string = (const char* ) key;
    unsigned long int hash = 0;

    for(int i = 0; i < strlen(string); i++){
        char letter = string[i];

        /*
        Cette hashFunction additionne les indices des lettres composant le mot,
        chacune sont multipliée par des puissances croissantes de 26
        */

       // On utilise le codage ASCII pour déterminer la position de la lettre dans l'alphabet
       int alphabetPos = letter - 'a' + 1;

       hash += alphabetPos*  pow(ALPHABET_SIZE, i);
    }

    return hash;
}
#pragma region("Hash")

HashTable* hashCreate(int size, unsigned long int (*hashFunction)(void* )){

    HashTable* table = malloc(sizeof(HashTable));
    if(table == NULL){
        return NULL;
    }

    void** buckets = calloc(size, sizeof(void* ));
    if(buckets == NULL){
        free(table);

        return NULL;
    }

    table->buckets = buckets;
    table->hashFunction = hashFunction;
    table->size = size;

    return table;
}
void hash_destroy(HashTable* table){

    if(table == NULL){
        return;
    }

    free(table->buckets);
    free(table);
}
void hash_insert(HashTable* table, void* key, void* data){
    if(table == NULL){
        return;
    }

    unsigned long int hash = table->hashFunction(key);

    // pour s’assurer que l’index soit valide, nous utilisons le module 
    // en base de la taille de votre table de hachage. 
    int index = hash % table->size;

    table->buckets[index] = data;
}
void hash_delete(HashTable* table, void* key){
    if(table == NULL){
        return;
    }

    unsigned long int hash = table->hashFunction(key);
    int index = hash % table->size;

    table->buckets[index] = NULL;

}
void* hash_get(HashTable* table, void* key){

    if(table == NULL){
        return NULL;
    }

    unsigned long int hash = table->hashFunction(key);
    int index = hash % table->size;

    return table->buckets[index];
}
int hash_size(HashTable* table){
    if(table == NULL){
        return 0;
    }

    int size = 0;

    for(int i = 0; i < table->size; i++){
        if(table->buckets[i] != NULL){
            size++;
        }
    }

    return size;
}

#pragma endregion("Hash")

#pragma region("Hash With External Chaining")

HashTableChain* hashChainCreate(int size, unsigned long int (*hashFunction)(void* )){

    HashTableChain* table = malloc(sizeof(HashTableChain));
    if(table == NULL){
        return NULL;
    }

    void* *buckets = calloc(size, sizeof(List* ));
    if(buckets == NULL){
        free(table);

        return NULL;
    }

    table->buckets = buckets;
    table->hashFunction = hashFunction;
    table->size = size;

    return table;
    
}
void hash_chain_destroy(HashTableChain* table){
    if(table == NULL){
        return;
    }

    for(int i = 0; i <table->size; i++){
        List* ToDelete = table->buckets[i];
        if(ToDelete == NULL){
            continue;
        }

        list_destroy(ToDelete);
    }

    free(table->buckets);
    free(table);
}
void hash_chain_insert(HashTableChain* table, void* key, void* data){
    if(table == NULL){
        return;
    }

    unsigned long int hash = table->hashFunction(key);
    int index = hash % table->size;

    // Points to the list at the index position
    List* bucketChain = table->buckets[index];
    if(bucketChain == NULL){
        bucketChain = list_create();
        if(bucketChain == NULL){
            return;
        }
        table->buckets[index] = bucketChain;
    }

    HashTableBucketNode* bucketNode = malloc(sizeof(HashTableBucketNode));
    if(bucketNode == NULL){
        return;
    }

    bucketNode->key = key;
    bucketNode->data = data;

    list_append(bucketChain, bucketNode);
    
}
void hash_chain_delete(HashTableChain* table, void* key){
    if(table == NULL){
        return;
    }

    unsigned long int hash = table->hashFunction(key);
    int index = hash % table->size;

    List* bucketChain = table->buckets[index];

    // Searches the list for the node to delete
    for(int i = 0; i < list_size(bucketChain); i++){
        HashTableBucketNode* BucketNode = (HashTableBucketNode* ) list_get(bucketChain, i);
        if(BucketNode == NULL){
            continue;
        }

        if(strcmp(BucketNode->key, key) == 0){ // strcmp returns 0 if the two strings match
            list_delete(bucketChain, i);
        }
    }
}
void* hash_chain_get(HashTableChain* table, void* key){
   
    if(table == NULL){
        return NULL;
    }

    unsigned long int hash = table->hashFunction(key);
    int index = hash % table->size;

    List* bucketChain = table->buckets[index];
    if(bucketChain == NULL){
        return NULL;
    }

    // Searches the list for the node to delete
    for(int i = 0; i < list_size(bucketChain); i++){
        HashTableBucketNode* BucketNode = (HashTableBucketNode* ) list_get(bucketChain, i);
        if(BucketNode == NULL){
            continue;
        }

        if(strcmp(BucketNode->key, key) == 0){ // strcmp returns 0 if the two strings match
           return BucketNode->data;
        }
    }

    return NULL;

}
int hash_chain_size(HashTableChain* table){
    if(table == NULL){
        return 0;
    }

    int size = 0;

    for(int i = 0; i < table->size; i++){
        List* BucketChain = table->buckets[i];
        if(BucketChain == NULL){
            continue;
        }
        size += list_size(BucketChain);
    }

    return size;
}

#pragma endregion("Hash With External Chaining")
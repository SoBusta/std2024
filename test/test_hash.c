#include "acutest.h"
#include "./../lib/hash/hash.h"

void hash_function(){
    char* a = "ba";
    TEST_CHECK_(hashFunction(a) == 28, "Error: hashFunction");
}

void regular_hash_insert_and_get()
{
    HashTable *table = hashCreate(10, (unsigned long int (*)(void *)) & hashFunction);
    hash_insert(table, (void *)"chat", (void *)43);
    TEST_ASSERT_(hash_get(table, (void *)"chat") == (void *)43, "Error: insert");
    hash_insert(table, (void *)"chat", (void *)44);
    TEST_ASSERT_(hash_get(table, (void *)"chat") == (void *)44, "Error: insert");
}

void regular_hash_delete()
{
    HashTable *table = hashCreate(10, (unsigned long int (*)(void *)) & hashFunction);
    hash_insert(table, (void *)"chat", (void *)43);
    hash_insert(table, (void *)"chat", (void *)44);
    hash_delete(table, (void *)"chat");
    TEST_ASSERT_(hash_get(table, (void *)"chat") == NULL, "Error: remove");
}

void chain_hash_insert_and_get()
{
    HashTableChain *table = hashChainCreate(10, (unsigned long int (*)(void *)) & hashFunction);
    hash_chain_insert(table, (void *)"chat", (void *)44);
    TEST_ASSERT_(hash_chain_get(table, (void *)"chat") == (void *)44, "Error: insert");
    hash_chain_insert(table, (void *)"g", (void *)45);
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == (void *)45, "Error: insert");
}

void chain_hash_delete()
{
    HashTableChain *table = hashChainCreate(10, (unsigned long int (*)(void *)) & hashFunction);
    hash_chain_insert(table, (void *)"chat", (void *)44);
    hash_chain_insert(table, (void *)"g", (void *)45);
    hash_chain_delete(table, (void *)"chat");
    TEST_ASSERT_(hash_chain_get(table, (void *)"chat") == NULL, "Error: remove");
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == (void *)45, "Error: remove");
    hash_chain_delete(table, (void *)"g");
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == NULL, "Error: remove");
}

void extra_regular_hash_insert_and_get(){
    HashTable *table = hashCreate(5, (unsigned long int (*)(void *)) & hashFunction);
    hash_insert(table, (void *)"chat", (void *)1);
    TEST_ASSERT_(hash_get(table, (void *)"chat") == (void *)1, "Error: insert");
    hash_insert(table, (void *)"chat", (void *)2);
    TEST_ASSERT_(hash_get(table, (void *)"chat") == (void *)2, "Error: insert");
}

void extra_regular_hash_delete(){
    HashTable *table = hashCreate(5, (unsigned long int (*)(void *)) & hashFunction);
    hash_insert(table, (void *)"chat", (void *)1);
    hash_insert(table, (void *)"chat", (void *)2);
    hash_delete(table, (void *)"chat");
    TEST_ASSERT_(hash_get(table, (void *)"chat") == NULL, "Error: remove");
}

void extra_chain_hash_insert_and_get(){
    HashTableChain *table = hashChainCreate(5, (unsigned long int (*)(void *)) & hashFunction);
    hash_chain_insert(table, (void *)"chat", (void *)1);
    TEST_ASSERT_(hash_chain_get(table, (void *)"chat") == (void *)1, "Error: insert");
    hash_chain_insert(table, (void *)"g", (void *)2);
    TEST_ASSERT_(hash_chain_get(table, (void *)"chat") == (void *)1, "Error: insert");
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == (void *)2, "Error: insert");
}

void extra_chain_hash_delete(){
    HashTableChain *table = hashChainCreate(5, (unsigned long int (*)(void *)) & hashFunction);
    hash_chain_insert(table, (void *)"chat", (void *)1);
    hash_chain_insert(table, (void *)"g", (void *)2);
    hash_chain_delete(table, (void *)"chat");
    TEST_ASSERT_(hash_chain_get(table, (void *)"chat") == NULL, "Error: remove");
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == (void *)2, "Error: remove");
    hash_chain_delete(table, (void *)"g");
    TEST_ASSERT_(hash_chain_get(table, (void *)"g") == NULL, "Error: remove");
}

TEST_LIST = {
    { "hash_function", hash_function },
    {"regular_hash_insert_and_get", regular_hash_insert_and_get},
    {"regular_hash_delete", regular_hash_delete},
    {"chain_hash_insert_and_get", chain_hash_insert_and_get},
    {"chain_hash_delete", chain_hash_delete},
    { "extra_regular_hash_insert_and_get", extra_regular_hash_insert_and_get },
    { "extra_regular_hash_delete", extra_regular_hash_delete },
    { "extra_chain_hash_insert_and_get", extra_chain_hash_insert_and_get },
    { "extra_chain_hash_delete", extra_chain_hash_delete },
    { NULL, NULL }
};

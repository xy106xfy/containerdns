#ifndef _DNSHASHMAP_H_
#define _DNSHASHMAP_H_


#define HASH_NODE_FIND   1

typedef struct hashNode_ {
	char *key;
	void * data;
    int  fingerprint; // 
    struct hashNode_ *next;
} hashNode;

typedef struct hashMap_
{
	hashNode** hashBuckets;
	rte_rwlock_t * locks;
    unsigned int bucketsSize; // 2^x -1
    unsigned int lockSize;    // 2^x -1
    unsigned int (*hashFun)(char *key);  
    int (*equalFun)(char *key,void *data, hashNode *node);  // check the k-v
    int (*queryFun)(hashNode *node, void* arg);          // check the node
    int (*checkExpiredFun)(hashNode *node,void* arg);                 // 
    int (*getAllNodeFun)(hashNode *node, void* arg); 
}hashMap;

hashMap * hashMap_create(int bucketsSize, int lockSize, unsigned int (*hashFun)(char *key),
    int(*equalFun)(char *key,void *data, hashNode *node),int (*queryFun)(hashNode *node,void* arg),
    int (*checkExpiredFun)(hashNode *node,void* arg),int (*getAllNodeFun)(hashNode *node, void* arg));
int hmap_lookup(hashMap *map, 	char *key, void * data, void* output);
void hmap_del(hashMap *map, char *key, void * data);
void hmap_update(hashMap *map, char *key, void * data);
int hmap_check_expired(hashMap *map, void* arg);
int hmap_get_all(hashMap *map, void* arg);




unsigned int elfHashDomain(char* str) ;



#endif  /*_DNSHASHMAP_H_*/


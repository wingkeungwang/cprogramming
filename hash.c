#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TABLE_SIZE	 20
//hash element
typedef struct kv {

	struct kv *next;
	char *key;
	void *value;
	void (*free_value)(void *);
} kv_t;


//hash table
//
typedef struct HashTable {

	kv_t **table;

} HashTable_t;


void HashTableDelete(HashTable_t *ht);

int hash_table_put(HashTable_t *ht, char *key, void *value, void (*free_value)(void *));

void *hash_table_get(HashTable_t *ht, char *key);


void *hash_table_get(HashTable_t *ht, char *key);

void init_kv(kv_t *kv)
{
	kv->next = NULL;
	kv->key = NULL;
	kv->value = NULL;
	kv->free_value = NULL;
}

void free_kv(kv_t *kv)
{
	if (kv) {
		if (kv->free_value)
			kv->free_value(kv->value);
		free(kv->key);
		kv->key = NULL;
		free(kv);
	}
}

unsigned int hash_33(char *key)
{
	unsigned int hash = 0;
	while (*key) {

		hash = (hash<<5) + hash + *key++;
	}

	return hash;
}

//new hash table instance

HashTable_t *hash_table_new()
{

	HashTable_t *ht = malloc(sizeof(HashTable_t));
	if (NULL == ht) {
		HashTableDelete(ht);
		return NULL;
	}


	ht->table = malloc(sizeof(kv_t)* TABLE_SIZE);
	if (ht->table == NULL) {
		HashTableDelete(ht);
		return NULL;
	}
	
	memset(ht->table, 0, sizeof(kv_t *)*TABLE_SIZE);

	return ht;
}

void HashTableDelete(HashTable_t *ht)
{
	int i = 0;
	kv_t *p = ht->table[i];
	kv_t *q = NULL;
	if (ht) {
		if (ht->table) {
			for (i = 0; i < TABLE_SIZE; i++) {
				while(p) {
					q = p->next;
					free_kv(p);
					p = q;
				}

			}
			free(ht->table);
			ht->table = NULL;
		}

		free(ht);
	}

}


//insert or update indexed by indexed key 
int hash_table_put(HashTable_t *ht, char *key, void *value, void (*free_value)(void *))
{
	
	int i = hash_33(key)%TABLE_SIZE;
	kv_t *p = ht->table[i];
	kv_t *prev = p;

	//if key is already stored, update its value
	while(p) {
		if (strcmp(p->key, key) == 0) {
			if (p->free_value) {
				p->free_value(p->value);
			}

			p->value = value;
			p->free_value = free_value;
			break;
		}
		prev = p;
		p = p->next;
	}

	if (p == NULL) {//if the key has not stored, then add it
		char *kstr = malloc(strlen(key) + 1);
		if (kstr == NULL) {
			return -1;
		}

		struct kv *kv = malloc(sizeof(kv_t));
		if (NULL == kv) {
			free(kstr);
			kstr = NULL;
			return -1;
		}

		init_kv(kv);
		kv->next = NULL;
		strcpy(kstr, key);
		kv->key = kstr;
		kv->value = value;
		kv->free_value = free_value;


		if (prev == NULL) {

			ht->table[i] = kv;
		} else {

			prev->next = kv;
		}

	}
	return 0;
}

//get a value indexed by key

void *hash_table_get(HashTable_t *ht, char *key)
{
	int i = hash_33(key) % TABLE_SIZE;
	kv_t *p = ht->table[i];
	while (p) {
		if (strcmp(key, p->key) == 0) {
			return p->value;
		}

		p = p->next;

	}

	return NULL;
}

//remove a value indexed by key

void hash_table_rm(HashTable_t *ht, char *key)
{

	int i = hash_33(key) % TABLE_SIZE;
	kv_t *p  = ht->table[i];
	kv_t *prep = p;
	while(p) {
		if (strcmp(key, p->key) == 0) {
			free_kv(p);
		}

		if (p == prep) {
			ht->table[i] = NULL;
		} else {
			prep->next = p->next;
		}
	}

	prep = p;
	p = p->next;

}

typedef struct Student {
	int age;
	float score;
	char name[32];
	char data[1024*1024*10];

} Student_t;

void free_student(void *stu)
{
	free(stu);
}

void show_student(Student_t *p)
{
	printf("name:%s, age:%d, score:%.2f    \n", p->name, p->age, p->score);

}

int main(int argc, char *argv[])
{
	int i = 0;
	HashTable_t *ht = hash_table_new();
	if (NULL == ht) {
		return -1;
	}

	for (i = 0; i < 100; i++) {
		Student_t * stu = (Student_t *)malloc(sizeof(Student_t));
		stu->age = 18 + rand()%100;
		sprintf(stu->name, "classmate%d", i);
		hash_table_put(ht, stu->name, stu, free_student);

	}

	for (i = 0; i < 100; i++) {
		char name[32];
		sprintf(name, "classmate%d", i);
		Student_t *stu = (Student_t *)hash_table_get(ht, name);
		show_student(stu);
	}

	HashTableDelete(ht);

	return 0;
}

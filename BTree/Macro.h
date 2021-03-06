#ifndef __MACRO_H__
#define __MACRO_H__

typedef char DataType;

#define deBug() printf("File = %s\nLine = %d\n", __FILE__, __LINE__)

#include <stdio.h>
#include <stdlib.h>

#ifndef __cplusplus
	typedef int Bool;
	#define true 1
	#define false 0
#else
	typedef bool Bool;
#endif 

#define MALLOC(type, size) 	(type*)malloc(sizeof(type) * size)
#define FREE(p)				(free(p), p = NULL)

#define STRUCT(type)	typedef struct __struct##type type;\
						struct __struct##type

typedef enum
{
    PreOrder,
    InOrder,
    PostOrder,
    LevelOrder
} BTTraversal;

STRUCT(BTreeNode)					
{
	DataType data;
	BTreeNode *parent;
	BTreeNode *m_left;
	BTreeNode *m_right;
};

STRUCT(BTree)
{
	BTreeNode* root;
};
						
#endif
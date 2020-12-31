#ifndef __LINKLISTVERTEX_H__
#define __LINKLISTVERTEX_H__

#include "Macro.h"
#include "LinkListEdge.h"

STRUCT(VertexNode)
{
	Vertex vertex;
	LinkListEdge *list;
};

STRUCT(LLNodeVertex)
{
	VertexNode *data;
	LLNodeVertex *next;
};

STRUCT(LinkListVertex)
{
	int len;
	LLNodeVertex *next;
	LLNodeVertex *m_current;
};

VertexNode* VertexNodeCreate(void);
VertexNode* VertexNodeDestroy(VertexNode *node);
LinkListVertex* LinkListVertexCreate(void);
LinkListVertex* LinkListVertexDestroy(LinkListVertex *list);
int LinkListVertexLength(LinkListVertex *list);
Bool LinkListVertexInsert(LinkListVertex *list, int i, VertexNode *data);
Bool LinkListVertexDelete(LinkListVertex *list, int i, VertexNode **data);
int LinkListVertexFind(LinkListVertex *list, VertexNode *data); 
Bool LinkListVertexSet(LinkListVertex *list, int i, VertexNode *data);
Bool LinkListVertexGet(LinkListVertex *list, int i, VertexNode **data);
LLNodeVertex* LinkListVertexMove(LinkListVertex *list, int i);
Bool LinkListVertexEnd(LinkListVertex *list);
void LinkListVertexNext(LinkListVertex *list);
VertexNode *LinkListVertexCurrent(LinkListVertex *list);

#endif

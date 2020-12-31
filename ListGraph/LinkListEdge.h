#ifndef __LinkListEdge_H__
#define __LinkListEdge_H__

#include "Macro.h"

STRUCT(EdgeNode)
{
	int end;
	Edge edge;
};

STRUCT(LLNodeEdge)
{
	EdgeNode data;
	LLNodeEdge *next;
};

STRUCT(LinkListEdge)
{
	int len;
	LLNodeEdge *next;
	LLNodeEdge *m_current;
};

LinkListEdge* LinkListEdgeCreate(void);
LinkListEdge* LinkListEdgeDestroy(LinkListEdge *list);
int LinkListEdgeLength(LinkListEdge *list);
Bool LinkListEdgeInsert(LinkListEdge *list, int i, EdgeNode data);
Bool LinkListEdgeDelete(LinkListEdge *list, int i, EdgeNode *data);
int LinkListEdgeFind(LinkListEdge *list, int end); 
Bool LinkListEdgeSet(LinkListEdge *list, int i, EdgeNode data);
Bool LinkListEdgeGet(LinkListEdge *list, int i, EdgeNode *data);
LLNodeEdge* LinkListEdgeMove(LinkListEdge *list, int i);
Bool LinkListEdgeEnd(LinkListEdge *list);
void LinkListEdgeNext(LinkListEdge *list);
EdgeNode LinkListEdgeCurrent(LinkListEdge *list);
EdgeNode* LinkListEdgeCurrentPtr(LinkListEdge *list);

#endif

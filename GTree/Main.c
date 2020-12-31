#include <stdio.h>
#include "GTree.h"

int main()
{
	GTree *tree = GTreeCreate();
	
	if(tree != NULL)
	{
		LinkList* list = NULL;
		GTreeNode *node = NULL;
		GTreeInsertValue(tree, 1, node);
		
		node = GTreeFindValue(tree, 1);
		GTreeInsertValue(tree, 2, node);
		GTreeInsertValue(tree, 3, node);
		
		node = GTreeFindValue(tree, 2);
		GTreeInsertValue(tree, 4, node);
		GTreeInsertValue(tree, 5, node);
		GTreeInsertValue(tree, 6, node);
		
		node = GTreeFindValue(tree, 3);
		GTreeInsertValue(tree, 7, node);
		
		node = GTreeFindValue(tree, 5);
		GTreeInsertValue(tree, 8, node);
		GTreeInsertValue(tree, 9, node);
		
		node = GTreeFindValue(tree, 7);
		GTreeInsertValue(tree, 10, node);
		
		node = GTreeFindValue(tree, 11);
		printf("node = %p\n", node);
		printf("flag = %d\n", GTreeInsertValue(tree, 12, node));
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree One: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		node = GTreeRemoveValue(tree, 5);
		node->parent = NULL;
		
		list = LinkListDestroy(list);
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree Two: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = GTreeDestroy(tree);
		
		tree = GTreeCreate();
		GTreeInsertNode(tree, node);
		
		list = GTreeTraversal(tree);
		
		if(list != NULL)
		{
			printf("Tree Three: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = GTreeDestroy(tree);
	}
	
	return 0;
}
#include <stdio.h>
#include "BTree.h"
#include "Macro.h"

int main()
{
	BTree *tree = BTreeCreate();
	
	if(tree != NULL)
	{
		LinkList *list = NULL;
		BTreeNode *node = NULL;
		BTreeInsertValue(tree, 1, node);
		
		node = BTreeFindValue(tree, 1);
		BTreeInsertValue(tree, 2, node);
		BTreeInsertValue(tree, 3, node);
		
		node = BTreeFindValue(tree, 2);
		BTreeInsertValue(tree, 4, node);
		BTreeInsertValue(tree, 5, node);
		printf("flag = %d\n", BTreeInsertValue(tree, 6, node));
		
		node = BTreeFindValue(tree, 3);
		BTreeInsertValue(tree, 7, node);
		
		node = BTreeFindValue(tree, 5);
		BTreeInsertValue(tree, 8, node);
		BTreeInsertValue(tree, 9, node);
		
		node = BTreeFindValue(tree, 7);
		BTreeInsertValue(tree, 10, node);
		
		node = BTreeFindValue(tree, 11);
		printf("node = %p\n", node);
		printf("flag = %d\n", BTreeInsertValue(tree, 12, node));
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree One: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		node = BTreeRemoveValue(tree, 5);
		node->parent = NULL;
		
		list = LinkListDestroy(list);
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree Two: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = BTreeDestroy(tree);
		
		tree = BTreeCreate();
		BTreeInsertNode(tree, node);
		
		list = BTreeTraversal(tree, LevelOrder);
		
		if(list != NULL)
		{
			printf("Tree Three: \n");
			for(LinkListMove(list, 0); !LinkListEnd(list); LinkListNext(list))
			{
				printf("data = %d\n", LinkListCurrent(list)->data);
			}
		}
		
		list = LinkListDestroy(list);
		tree = BTreeDestroy(tree);
	}
	
	return 0;
}
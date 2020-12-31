#include "LinkList.h"
#include <iostream>

using namespace std;

int main()
{
    LinkList *list = LinkListCreate();

    if (list != NULL)
    {
        for (int i = 0; i < 10; i++)
        {
            int *data = MALLOC(int, 1);

            if (data == NULL)
            {
                cout << "no momery to create int data: i = " << i << endl;
            }
            else
            {
                *data = i;
                bool ok = LinkListInsertBack(list, data);
                cout << "result of inserting data: " << ((ok == true) ? "true." : "false.") <<
                     endl;
            }
        }

        LinkListForEach(list)
        {
            int *data = LinkListEntry(list, int);
            if (data != NULL)
            {
                cout << "get data successful: data = " << *data << endl;
            }
            else
            {
                cout << "get data failed." << endl;
            }
        }

        int len = LinkListLength(list);

        for (int i = 0; i < len; i++)
        {
            int *data = reinterpret_cast<int *>(LinkListDelete(list, 0));

            if (data != NULL)
            {
                cout << "get data successful: data = " << *data << endl;
                FREE(data);
            }
            else
            {
                cout << "get data failed." << endl;
            }
        }

        list = LinkListDestroy(list);
    }

    return 0;
}
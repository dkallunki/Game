struct ITEM_T {
	Box    *boxPtr;  // ptr to a Box (the data)
	ITEM_T *nextPtr; // ptr to next ITEM_T in the linked list
;

ITEM_T *headPtr = nullPtr;      // Linked list head
ITEM_T *tailPtr = nullPtr;      // Linked list tail


void addItem(ITEM_T **headPtrPtr, ITEM_T **tailPtrPtr, Box *box )
{
	ITEM_T *newItemPtr = new ITEM_T();
	newItemPtr->boxPtr = box;
	newItemPtr->nextPtr = nullPtr;
	if( *headPtr == nullPtr ){	// Add first item to the list	        
		*headPtr = newItemPtr;
		*tailPtr = newItemPtr;
	}
	else 
	{
		*tailPtr->nextPtr = newItemPtr;
		*tailPtr = newItemPtr;
	}
}

Box* getItemN(ITEM_T *headPtr, int N)
{
	Box *b = nullPtr;
	ITEM_T *i = headPtr;
	while (N-- && i != nullPtr) 
	{
		b = i->boxPtr;
		i = i->nextPtr;
	}
	return b;
}

		
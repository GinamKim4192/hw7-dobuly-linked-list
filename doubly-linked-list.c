/*
 *  doubly-linked-list.c
 *
 *  Doubly Linked List
 *
 *  Data Structures
 *  Department of Computer Science 
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 if necessary */


typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;



typedef struct Head {
	struct Node* first;
}headNode;

/* 함수 리스트 */

/* note: initialize는 이중포인터를 매개변수로 받음
         lab3의 initialize와 차이점을 이해 할것 */
int initialize(headNode** h);

/* note: freeList는 싱글포인터를 매개변수로 받음
        - initialize와 왜 다른지 이해 할것
         - 이중포인터를 매개변수로 받아도 해제할 수 있을 것 */
int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
	printf("[----- [김기남]  [2022299002] -----]\n");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {
		case 'z': case 'Z':
			initialize(&headnode);
			break;
		case 'p': case 'P':
			printList(headnode);
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);
			break;
		case 'e': case 'E':
			deleteLast(headnode);
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);
			break;
		case 't': case 'T':
			deleteFirst(headnode);
			break;
		case 'r': case 'R':
			invertList(headnode);
			break;
		case 'q': case 'Q':
			freeList(headnode);
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {

	/* headNode가 NULL일 경우, 할당된 linked List가 없음.
	   따라서, 할당을 해제할 메모리가 없는 것임. */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 할당 초기화 */
	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;
	return 1;
}

int freeList(headNode* h){
	/* h와 연결된 listNode 메모리 해제
	 * headNode도 해제되어야 함.
	 */
	listNode* p = h->first;

	listNode* prev = NULL;
	/*headNode의 first로부터
	  NULL값이 될때까지 반복문을 돌며
	  할당 해제*/
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	// 마지막으로 head노드 할당 해제
	free(h);
	return 0;
}


void printList(headNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}




/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(headNode* h, int key) {
	// 추가할 Node 동적메모리 할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	//추가할 노드 초기화
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	/*headNode가 NULL일 경우,
	  아직 linkedList가 만들어 지지 않은 것이므로
	  headNode로부터 새로운 Node 연결*/
	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	/*LinkedList의 마지막까지 반복문을 돌며
	  NULL이 나온 위치 다음에 노드 추가*/
	listNode* n = h->first;
	while(n->rlink != NULL) {
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



/**
 * list의 마지막 노드 삭제
 */
int deleteLast(headNode* h) {
	/*headNode에 연결된 것이 없다면
	  linkedList가 만들어지지 않은 것이므로
	  삭제할 수 없음*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	/* 노드가 하나만 있는 경우, 즉 first node == last node인  경우 처리 */
	if(n->rlink == NULL) {
		h->first = NULL;
		free(n);
		return 0;
	}

	/* 반복문을 돌며 다음 링크가 NULL까지 반복
	   trail에 해당 링크 할당 */
	while(n->rlink != NULL) {
		trail = n;
		n = n->rlink;
	}

	/* 할당된 trail(마지막 링크) 연결 해제 */
	trail->rlink = NULL;
	free(n);

	return 0;
}



/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(headNode* h, int key) {
	// 추가할 노드 동적할당
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;
	/*headNode가 NULL일 경우
	  headNode로 다음 링크에 새로운 노드 할당*/
	if(h->first == NULL)
	{
		h->first = node;
		return 1;
	}
	/*headNode다음에 새로운 Node를 연결하고
	  새로운 Node를 원래 첫번째 있던 Node와 연결*/
	node->rlink = h->first;
	node->llink = NULL;
	
	/*원래 첫번쨰 Node는 새로운 Node와 연결*/
	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(headNode* h) {
	/*headNode에 연결된 값이 없다면
	  아직 linkedList가 만들어지지 않은 것이므로
	  삭제 불가*/
	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}
	/*headNode는 두번째 Node와 연결하고
	  첫번째 node할당 해제*/
	listNode* n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}



/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(headNode* h) {

	/*headNode의 연결된 값이 없으면
	  아직 linkedList가 만들어지지 않은 것이므로
	  역순으로 재배치 불가*/
	if(h->first == NULL) {
		printf("nothing to invert...\n");
		return 0;
	}
	/*역순으로 재배치를 할 temp노드에
	  headNode를 할당함*/
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	/*trail Node, middle Node를 이용하여
	   반복문을 돌며, 위치 변경*/
	while(n != NULL){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(headNode* h, int key) {

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;

	/* linkedList의 마지막까지 반복문 */
	while(n != NULL) {
		/*특정 위치에서 추가하는 key값이 더 작을 경우*/
		if(n->key >= key) {
			/* headNode다음인지 확인 */
			if(n == h->first) {
				insertFirst(h, key);
				/*head노드가 아니면
				  새로운 Node를 좌우로 link 연결 */
			} else {
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	/* 위에서 return되지 못했을 경우 마지막에 삽입 */
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(headNode* h, int key) {

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;
	/* linkedList의 마지막까지 반복문 */
	while(n != NULL) {
		/*특정 위치에서 추가하는 key값이 나올 경우*/
		if(n->key == key) {
			/* headNode다음인지 확인 */
			if(n == h->first) {
				deleteFirst(h);
			/*마지막 노드까지 반복문을 실행했을 경우,
			  해당 위치의 Node 삭제*/
			} else if (n->rlink == NULL){
				deleteLast(h);
			/*그 이외에 중간 노드인경우
			새로운 Node를 좌우로 link 연결 */
			} else {
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	/* 찾지 못 한경우 */
	printf("cannot find the node for key = %d\n", key);
	return 1;
}



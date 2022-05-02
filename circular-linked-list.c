/*
 *  doubly circular linked list
 *
 *  Data Structures
 *
 *  Department of Computer Science
 *  at Chungbuk National University
 *
 */



#include<stdio.h>
#include<stdlib.h>
/* 필요한 헤더파일 추가 */

typedef struct Node {
	int key;
	struct Node* llink;
	struct Node* rlink;
} listNode;

/* 함수 리스트 */
int initialize(listNode** h);
int freeList(listNode* h);
int insertLast(listNode* h, int key);
int deleteLast(listNode* h);
int insertFirst(listNode* h, int key);
int deleteFirst(listNode* h);
int invertList(listNode* h);

int insertNode(listNode* h, int key);
int deleteNode(listNode* h, int key);

void printList(listNode* h);



int main()
{
	printf("----- 허정윤 2021041047-----\n");
	char command;
	int key;
	listNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                  Doubly Circular Linked List                   \n");
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


int initialize(listNode** h) {

	/* headNode가 NULL이 아니면, freeNode를 호출하여 할당된 메모리 모두 해제 */
	if(*h != NULL)
		freeList(*h);

	/* headNode에 대한 메모리를 할당하여 리턴 */
	*h = (listNode*)malloc(sizeof(listNode));
	(*h)->rlink = *h;
	(*h)->llink = *h;
	(*h)->key = -9999;
	return 1;
}

/* 메모리 해제 */
int freeList(listNode* h){
	//비어있어서 rlink가 h가 되어있는 경우
	if(h->rlink == h){
		free(h);
		return 1;
	}

	//h의 rlink를 계속 받아서 prev로 넘기고 해제시킨다.
	listNode* p = h->rlink;
	listNode* prev = NULL;
	while(p != NULL && p!=h){
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}



void printList(listNode* h) {
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {
		printf("Nothing to print....\n");
		return;
	}

	p = h->rlink;

	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}
	printf("  items = %d\n", i);


	/* print addresses */
	printf("\n---checking addresses of links\n");
	printf("-------------------------------\n");
	printf("head node: [llink]=%p, [head]=%p, [rlink]=%p\n", h->llink, h, h->rlink);

	i = 0;
	p = h->rlink;
	while(p != NULL && p != h) {
		printf("[ [%d]=%d ] [llink]=%p, [node]=%p, [rlink]=%p\n", i, p->key, p->llink, p, p->rlink);
		p = p->rlink;
		i++;
	}

}



/**
 * list에 key에 대한 노드하나를 추가
 */
int insertLast(listNode* h, int key) {
	//h가 initialize되지 않았으면 return -1
	if(h==NULL) return -1;

	//node를 만들어준다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	//h가 비어있는 경우.(첫 노드 삽입)
	if(h->rlink == h){
		h->rlink = node;
		h->llink = node;
		node->rlink = h;
		node->llink = h;
	}
	//node를 중간에 삽입(뒤의 오른쪽, 앞의 왼쪽, 노드의 2개 총 4개 변경)
	else {
		h->llink->rlink = node;
		node->llink = h->llink;
		h->llink = node;
		node->rlink = h;
	}
	return 1;
}


/**
 * list의 마지막 노드 삭제
 */
int deleteLast(listNode* h) {
	//h에 노드가 없거나, 비어있거나(initialize되지 않음)하는 경우 에러
	if(h->llink == h || h == NULL){
		printf("Error : Nothing to delete\n");
		return 1;
	}

	//h의 llink와 연결된 link들을 h에 대한 link들로 바꾸고, 해제
	listNode* nodetoremove = h->llink;

	nodetoremove->llink->rlink = h;
	h->llink = nodetoremove->llink;
	free(nodetoremove);

	return 1;
}


/**
 * list 처음에 key에 대한 노드하나를 추가
 */
int insertFirst(listNode* h, int key) {
	//비어있으면 오류메시지.
	if(h==NULL){
		printf("Error : h is NULL\n");
		return 1;
	}
	//node를 만들어준다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink =node->llink = NULL;

	//연결
	node->rlink = h->rlink;
	h->rlink->llink = node;
	node->llink = h;
	h->rlink = node;

	return 1;
}

/**
 * list의 첫번째 노드 삭제
 */
int deleteFirst(listNode* h) {
	//h가 없거나(initialize 안됨), 비어있거나.
	if(h==NULL||h->rlink == h){
		printf("Error : Nothing to delete.\n");
		return 1;
	}

	//삭제용 nodetoremove를 만들어서 좌우 link를 바꾸어주고 해제.
	listNode* nodetoremove = h->rlink;
	nodetoremove->rlink->llink =h;
	h->rlink = nodetoremove->rlink;

	free(nodetoremove);

	return 1;

}


/**
 * 리스트의 링크를 역순으로 재 배치
 */
int invertList(listNode* h) {
	//비어있거나, 만들어지지 않았으면 에러메시지
	if(h->rlink ==h || h == NULL){
		printf("Error : Nothing to inver\n");
		return 0;
	}
	listNode* n = h->rlink;
	listNode* trail = h;
	listNode *middle = h;

	h->llink = h->rlink;

	//trail, middle, n은 h->rlink부터 rlink를 따라 옮겨짐
	//middle을 중심으로 좌우 링크가 바뀌게 됨.
	while(n!=NULL && n !=h){
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}
	//h에 middle 연결.
	h->rlink = middle;

	return 0;
}



/* 리스트를 검색하여, 입력받은 key보다 큰값이 나오는 노드 바로 앞에 삽입 */
int insertNode(listNode* h, int key) {
	//비어있으면 오류메시지.
	if(h==NULL){
		printf("Error : h is NULL\n");
		return 1;
	}

	//노드를 만들어준다.
	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	//h에 노드가 없으면 만들어둔 함수를 이용하여 삽입.
	if(h->rlink ==h){
		insertFirst(h, key);
		return 1;
	}
	
	//삽입을 위해 비교할 노드가 되어줄 n
	listNode* n = h->rlink;
	while(n!=NULL && n!=h){
		if(n->key >=key){
			//처음에 그러면 함수로 넣고, 아닌 경우는 따로 해준다.
			if(n==h->rlink) insertFirst(h, key);
			else{
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
				n->llink = node;
			}
			return 0;
		}
		//다음 노드로 넘어간다.
		n = n->rlink;
	}
	//삽입되지 않은 경우, 마지막에 삽입.
	insertLast(h, key);
	return 0;
}


/**
 * list에서 key에 대한 노드 삭제
 */
int deleteNode(listNode* h, int key) {
	//h가 없거나(initialize 안됨), 비어있거나.
	if(h==NULL||h->rlink == h){
		printf("Error : Nothing to delete.\n");
		return 1;
	}

	listNode* n = h->rlink;
	
	while( n != NULL && n!=h){//비어있지 않고, h가 아닐 때.
		if(n->key == key){
			//처음이나 끝인 경우는 미리 만든 함수를 이용
			//중간인 경우는 좌우의 link를 끊고 해제.
			if(n==h->rlink) deleteFirst(h);
			else if(n->rlink == h) deleteLast(h);
			else{
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 0;
		}
		//다음 노드로 넘긴다.
		n=n->rlink;
	}
	//찾지 못한 경우.
	printf("Error : Can't find the node for key %d\n", key);
	return 0;
}



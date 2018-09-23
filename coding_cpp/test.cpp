#include<stdio.h>
#include<iostream>
#include<vector>
#include<map>
using namespace std;


struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

void push(struct ListNode** head_ref, int new_data){/*
    Function to insert node at head.
*/
	struct ListNode* temp = (struct ListNode*) malloc(sizeof(struct ListNode));//new ListNode;
	temp->val = new_data;
	temp->next = *head_ref;
	*head_ref = temp;
	}

ListNode *mergeKLists(vector<ListNode *> &lists) {/*
    Function to merge sorted linked lists.
    parameters: vector of sorted LLs.
    return: merged LL
*/
        multimap<int, ListNode*> mp;  //a new multimap<val, head> to store data
        for (auto p : lists) {
            if (p != NULL) { //every List , <val, ListHead>, if ListHead != NULL
                mp.insert(make_pair(p->val, p)); 
            }
        }
        ListNode *ret = NULL;
        ListNode *p = NULL;
        while (!mp.empty()) {
            multimap<int, ListNode*>::iterator it = mp.begin();
            if (ret == NULL) {
                ret = it->second;
                p = ret;
            } else {
                p->next = it->second;
                p = p->next;
            }
            if (it->second->next != NULL) {
                mp.insert(make_pair(it->second->next->val, it->second->next));
            }
            mp.erase(it);
        }
        return ret;
    }
void printList(struct ListNode *node){/*
    Function to print content of a linked list.
*/
	while(node !=NULL){
		//cout>>node.val>>"->";
		printf("%d --> ",node->val);
		node = node->next;
	}
	// printf("NULL");
	cout<<"NULL\n"<<endl;
}
ListNode* reverseList(ListNode* head) {/*
    Function to reverse a linkedlist in place.
*/
        if(head == NULL||head->next == NULL) return head;
        ListNode* pre = NULL;
        ListNode* cur = head;
        while(cur!=NULL){
            ListNode* temp = cur->next;
            cur->next = pre;
            pre = cur;
            cur = temp;
        }
        return pre;
    }    
/* Given a node prev_node, insert a new node after the given
   prev_node */
void insertAfter(struct ListNode* prev_node, int new_data){
	if(prev_node == NULL){
		printf("not \n");
    return;
	}
	struct ListNode* new_node = (struct ListNode*) malloc(sizeof(struct ListNode));
	new_node->val = new_data;
	new_node->next = prev_node->next;
	prev_node->next = new_node;
}

/* Given a reference (pointer to pointer) to the head
   of a list and an int, appends a new node at the end  */
void append(struct ListNode** head_ref, int new_data){
    /* 1. allocate node */
    struct ListNode* new_node = (struct ListNode*) malloc(sizeof(struct ListNode));
 
    struct ListNode *dummy = *head_ref;  /* used in step 5*/
 
    /* 2. put in the data  */

    new_node->val  = new_data;
    //printf("\ncreated new node with %d value and the new_node->data shows : %d",new_data,new_node->data);
    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->next = NULL;
 
    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
       return;
    }
 
    /* 5. Else traverse till the last node */
    while (dummy->next != NULL)
        dummy = dummy->next;
 
    /* 6. Change the next of last node */
    dummy->next = new_node;
    return;

}
void deleteNode(struct ListNode** head_ref, int todelete){
    
    struct ListNode* dummy = *head_ref;
    struct ListNode* temp = dummy;
    if(dummy!=NULL && dummy->val == todelete){
      *head_ref = dummy->next;
      free(dummy);
      return;
    }
    while(dummy->val!=todelete){
      temp = dummy;
      dummy = dummy->next;
    }

    if(dummy->next == NULL){
      return;
    }
    temp->next = dummy->next;
    free(dummy);
    
}

/* Function to remove duplicates from a
unsorted linked list */
void removeDuplicates(struct ListNode *start)
{
	struct ListNode *ptr1, *ptr2, *dup;
	ptr1 = start;

	/* Pick elements one by one */
	while (ptr1 != NULL && ptr1->next != NULL)
	{
		ptr2 = ptr1;

		/* Compare the picked element with rest
		of the elements */
		while (ptr2->next != NULL)
		{
			/* If duplicate then delete it */
			if (ptr1->val == ptr2->next->val)
			{
				/* sequence of steps is important here */
				dup = ptr2->next;
				ptr2->next = ptr2->next->next;
				free(dup);
			}
			else /* This is tricky */
				ptr2 = ptr2->next;
		}
		ptr1 = ptr1->next;
	}
}
int main(){
    // pair<int,int>p;
    // p = make_pair(20,3);
    // cout << "p: "<<p.first<<","<<p.second;
    struct ListNode* head = NULL;    
    for(int i = 1; i<11; ++i){
	push(&head, i);
    }
    head = reverseList(head);
    // cout<<"\ncreated first";
    struct ListNode* second = NULL;
    for(int i = 2; i<25; i*=2){
    	//cout<<"\n"<<i;
        push(&second,i);	
    }
    second = reverseList(second);
    // cout<<"\ncreated second";
    struct ListNode* third = NULL;
    for(int i = 128; i>1; i>>=1){
    	// cout<<"\n"<<i;
        push(&third,i);
    }
    printList(head);
    // cout<<"\n";
    printList(second);
    // cout<<"\n";
    printList(third);
    // cout<<"\n";
    vector<ListNode*> arr;
    arr.push_back(head);
    arr.push_back(second);
    arr.push_back(third);
    struct ListNode* res = mergeKLists(arr);
    cout << "merged linked list:"<<endl;
    printList(res);
    cout << "after removing duplicates:" << endl;
    removeDuplicates(res);
    printList(res);
    cout << "reversed linked list:"<<endl;
    printList(reverseList(res));
    return 0;
}

#include <stdio.h>
#include <stdlib.h>

#define LIST_OBJS 3

// This is for the folowing problem - https://leetcode.com/problems/add-two-numbers/

typedef struct ListNode {
  int val;
  struct ListNode *next;
} ln;

// Funtion prototypes
void printList(ln* list);
void unloadList(ln* list);
ln* buildList(int* nums, int size);
struct ListNode* addTwoNumbers(struct ListNode** l1, struct ListNode** l2);
struct ListNode* reverse(struct ListNode** l1);


int main(void) {
  int nums1[] = {2, 4, 3};
  int nums2[] = {5, 6, 4};
  ln* lists[LIST_OBJS];
  
  lists[0] = buildList(nums1, sizeof(nums1) / sizeof(nums1[0]));
  lists[1] = buildList(nums2, sizeof(nums2) / sizeof(nums2[0]));
  lists[2] = addTwoNumbers(&lists[0], &lists[1]);

  printf("Main: print lists and free their memory\n");
  for (int i=0; i<LIST_OBJS; i++) {
    printList(lists[i]);
    unloadList(lists[i]);

  }
} // End main


struct ListNode* addTwoNumbers(struct ListNode** l1, struct ListNode** l2) {
  // Reverse the lists
  *l1 = reverse(l1);
  *l2 = reverse(l2);

  struct ListNode* p1 = *l1;
  struct ListNode* p2 = *l2;

  ln* head = (ln*) malloc(sizeof(ln));
  ln* cur = head;
  int carry = 0;
  int insert;

  while (p1 != NULL || p2 != NULL) {
    insert = p1->val + p2->val;
    insert += carry;
    carry = insert >= 10 ? 1 : 0;
    insert = insert % 10;

    cur->val = insert;
    if (p1->next == NULL) {
      cur->next = NULL;
    } else {
      cur->next = (struct ListNode*) malloc(sizeof(struct ListNode));
      cur = cur->next;
    }
    p1 = p1->next;
    p2 = p2->next;
  }

  printf("Exiting addTwoNumbers\n\n");
  return head;
} // End addTwoNumbers


struct ListNode* reverse(struct ListNode** l1) {
  struct ListNode *prev = NULL;
  struct ListNode *current = *l1;
  struct ListNode *next = NULL;

  while (current != NULL) {
    next = current->next;   // Save the next node
    current->next = prev;   // Reverse the current node's pointer
    prev = current;         // Move prev to current node
    current = next;         // Move to the next node
  }
  
  return prev;  // The new head of the reversed list
}


void printList(ln* list) {
  printf("Val: %d\t\tHas: %p\t\tNext: %p\n", list->val, list, list->next);
  while (list->next != NULL) {
    // printf("%d\n", list->next->val);
    printf("Val: %d\t\tHas: %p\t\tNext: %p\n", list->next->val, list->next, list->next->next);
    list = list->next; 
  }
}


void unloadList(ln* list) {
  ln* del = list;
  while (list->next != NULL) {
    list = list->next;
    free(del);
    del = list;
  }
  free(del);
}


ln* buildList(int* nums, int size) {
  ln* head = (ln*) malloc(sizeof(ln));
  ln* cur = head;
  // ln* tail = cur;

  for (int i=0; i < size; i++) {
    // tail = cur;
    printf("Inserting %d\n", nums[i]);
    cur->val = nums[i];
    if (i == size - 1) {
      cur->next = NULL;
    } else {
      cur->next = (ln*) malloc(sizeof(ln));
      cur = cur->next;
    }
  }
  return head;
} // End buildList

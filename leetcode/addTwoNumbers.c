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
  int nums1[] = {9,9,9,9,9,9,9};  //{2, 4, 3};
  int nums2[] = {9,9,9,9};  //{5, 6, 4};
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
  // Allocate the initial memory 
  struct ListNode *result = malloc(sizeof(struct ListNode));
  struct ListNode *cur = result;

  struct ListNode *p1 = *l1;
  struct ListNode *p2 = *l2;

  int carry = 0;

  while (p1 || p2 || carry) {
    if (p1) {
      printf("p1->val is %d\t", p1->val);
      carry += p1->val;
      p1 = p1->next;
    }
    if (p2) {
      printf("p2->val is %d\t", p2->val);
      carry += p2->val;
      p2 = p2->next;
    }
    printf("carry is %d\n", carry);
    cur->val = carry % 10;
    carry /= 10;
    if (p1 || p2 || carry) {
      cur->next = malloc(sizeof(struct ListNode));
      cur = cur->next;
    } else {
      cur->next = NULL;
    }
  } 
  return result;
} // End addTwoNumbers


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


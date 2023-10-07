/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() { 
  // @TODO: graded in mp_lists part 1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;            //create empty list, which means length is 0
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in mp_lists part 1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy() {
  /// @todo Graded in mp_lists part 1
  ListNode *temporary;
  if(head_ == NULL){
    return;
  }
  while(head_ != NULL){
    temporary = head_->next;
    delete head_;
    head_ = temporary;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;
  
  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }
  
  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata) {
  /// @todo Graded in mp_lists part 1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = NULL;
  newNode -> prev = tail_;          //same as insertFront except swapped bc now at back
  
  if (tail_ != NULL) {
    tail_ -> next = newNode;
  }
  if (head_ == NULL) {
    head_ = newNode;
  }
  
  tail_ = newNode;
  length_++;

}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint) {
  /// @todo Graded in mp_lists part 1
  ListNode * curr = start;
  if(curr == NULL || splitPoint > length_){
    return NULL;
  }
  if(splitPoint < 1){
    return start;
  }
  for (int i = 1; i < splitPoint && curr != NULL; i++) {
    curr = curr->next;
  }
  if (curr != NULL) {
      curr = curr->next;
      curr->prev->next = NULL;
      tail_ = curr->prev;
      curr->prev = NULL;
      return curr;
  }
  return NULL;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall() {
  /// @todo Graded in part 1
  if(head_->next == tail_ || head_->next == NULL){                  //return list if next thing to remove is either tail or null
    return;
  }
  ListNode *curr = head_;
  ListNode *temp;
  while(curr->next != NULL && curr->next->next != NULL){
    curr = curr->next;
    curr->next->prev = curr->prev;
    curr->prev->next = curr->next;
    temp = curr->next;
    tail_->next = curr;
    curr->prev = tail_;
    curr->next = NULL;
    tail_ = curr;
    curr = temp;
    }
  }



/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse() {
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint) {
  /// @todo Graded in mp_lists part 2
  ListNode *start = startPoint;
  ListNode *end = endPoint->next;
  ListNode *prev = startPoint->prev;
  ListNode *temp;
  if(startPoint == endPoint){
    return;
  }
  while(startPoint != endPoint){
    temp = startPoint->prev;
    startPoint->prev = startPoint->next;
    startPoint->next = temp;
    startPoint = startPoint->prev;
  }
  temp = startPoint->prev;
  startPoint->prev = prev;
  startPoint->next = temp;
  endPoint = start;
  endPoint->next = end;
  if(prev == NULL){
    head_ = startPoint;
  }
  else{
    prev->next = startPoint;
  }
  if(end == NULL){
    tail_ = endPoint;
  }
  else{
    end->prev = endPoint;
  }
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n) {
  /// @todo Graded in mp_lists part 2
  ListNode *uno = head_;
  ListNode *dos = uno;
  ListNode *tres;
  int elements = n;
  if(n >= length_){                       //if n is larger than the length of the list, this will do the same as reverse()
    reverse();
  }
  if(length_ < 2 || n < 2){
    return;
  }
  while(uno != NULL){
      if(elements == 0){
          if(dos == head_){
            head_ = tres;
          }
          reverse(dos, tres);
          elements = n;
          dos = uno;
          tres = uno;
       }
       if (uno->next == NULL){
            reverse(dos, uno);
       }
       elements = elements-1;
       tres = uno;
       uno  = uno->next;
  }
}

/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */
template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}

/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */
template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second) {
  /// @todo Graded in mp_lists part 2
  ListNode *list;
  ListNode *temp;
  if(first == NULL){
    return second;
  }
  if(second == NULL){ 
    return first;
  }
  if(first->data < second->data){              //operator<
  list = first;
  first = first->next;
  }
  else{
  list = second;
  second = second->next;
  }
  temp = list;
  while(first != NULL && second != NULL){
    if(first->data < second->data){
      first->prev = temp;
      temp->next = first;
      first = first->next;
    }
    else{
      second->prev = temp;
      temp->next = second;
      second = second->next;
    }
    temp = temp->next;
  }
  if(second == NULL){
    first->prev = temp;
    temp->next = first;
  }
  if(first == NULL){
    second->prev = temp;
    temp->next = second;
  }
  return list;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength) {
  /// @todo Graded in mp_lists part 2
  if(chainLength == 1){
    return start;
  }
  else{
  ListNode* splitlist = split(start, chainLength/2);
  ListNode* poke = mergesort(start, chainLength/2);
  ListNode* mon = mergesort(splitlist, chainLength - chainLength/2);
  return merge(poke, mon);
  }
}


class ListIterator : public std::iterator<std::bidirectional_iterator_tag, T> {
  private:
    // @TODO: graded in mp_lists part 1
    ListNode* position_;

  public:
    ListIterator() : position_(NULL) { }
    ListIterator(ListNode* x) : position_(x) { }


    // Pre-Increment, ++iter
    ListIterator& operator++() {
        // @TODO: graded in mp_lists part 1
        position_ = position_->next;
        return *this;
    }
    
    // Post-Increment, iter++
    ListIterator operator++(int) {
        // @TODO: graded in mp_lists part 1
        ListNode *yugioh = position_;
        position_ = position_->next;
        return ListIterator(yugioh);
    }

    // Pre-Decrement, --iter
    ListIterator& operator--() {
        // @TODO: graded in mp_lists part 1
        position_ = position_->prev;
        return *this;
    }

    // Post-Decrement, iter--
    ListIterator operator--(int) {
        // @TODO: graded in mp_lists part 1
        ListNode *yugioh = position_;
        position_ = position_->prev;            //same as operator++(int) but position is now ->prev instead of ->next
        return ListIterator(yugioh);
    }

    bool operator!=(const ListIterator& rhs) {
        // @TODO: graded in mp_lists part 1
        if(this->position_ != rhs.position_){
        return true;
        }
        else{
        return false;
        }
    }
    

    bool operator==(const ListIterator& rhs) {
        return !(*this != rhs);
    }

    const T& operator*() {
        return position_->data;
    }

    const T* operator->() {
        return &(position_->data);
    }
};

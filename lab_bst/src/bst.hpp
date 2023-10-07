/**
 * @file bst.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V BST<K, V>::find(const K& key)
{
    // your code here
    Node *&temp = find(root,key);
    return temp->value;
}

template <class K, class V>
struct BST<K, V>::Node* & BST<K, V>::find(Node* & subtree, const K& key)
{
    // Your code here
    if(subtree == nullptr || subtree->key == key){
        return subtree;
    }
    
    if(subtree->key < key){
        return find(subtree->right,key);
    }
    else{
        return find(subtree->left,key);
    }
}

template <class K, class V>
void BST<K, V>::insert(const K & key, const V & value)
{
    // your code here
    insert(root, key, value);
}

template <class K, class V>
void BST<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    BST<K,V>::Node *&temp = find(subtree,key);
    if(!temp){
        temp = new Node(key,value);
    }
    }

template <class K, class V>
void BST<K, V>::swap(Node*& first, Node*& second)
{
    // your code here
    K key1 = first->key;
    V value1 = first->value;
    first->key = second->key;
    first->value = second->value;
    second->key = key1;
    second->value = value1;

}

template <class K, class V>
void BST<K, V>::remove(const K& key)
{
    // your code here
    remove(root, key);
}

template <class K, class V>
void BST<K, V>::remove(Node*& subtree, const K& key)
{
    // your code here
    BST<K, V>::Node*& temp1 = find(subtree, key);
    if(temp1->left != nullptr && temp1->right == nullptr){
        Node* temp2 = temp1 -> left;
        temp1 = temp2;
        return; 
    } 
    if(temp1->right != nullptr && temp1->left == nullptr){ 
        Node* temp2 = temp1 -> right;
        temp1 = temp2;
        return;
    } 
    if(temp1->right == nullptr && temp1->left == nullptr){
        temp1 = nullptr;
        return; 
    } 
    else{ 
        Node* temp2 = temp1->left;
        while(temp2->right){
            temp2 = temp2->right;
        }
        swap(temp1,temp2);
        remove(temp1->left,temp2->key);
        return;
    }
}

template <class K, class V>
BST<K, V> listBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    BST<K,V> temp;
    for (auto const &nodes : inList){
        temp.insert(nodes.first, nodes.second);
    }
    return temp;

}

template <class K, class V>
std::vector<int> allBuild(std::vector<std::pair<K, V>> inList){
    // your code here
    std::sort(inList.begin(),inList.end());
    std::vector<int>temp(inList.size());
    do{
    BST<K,V> temp2;
    for (auto const &pair:inList) {
        temp2.insert(pair.first,pair.second);
    }
    ++temp[temp2.height()];
    }while(std::next_permutation(inList.begin(),inList.end()));
    return temp;
}
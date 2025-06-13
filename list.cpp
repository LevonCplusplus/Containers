#include <iostream>
template <class T>
class list {

    struct node{
        mutable node* next;
        mutable node* prev;
        T val;
        // template <typename... Args> 
        // node(Args&& ... args):val(std::forward<Args>(args)...){};
        template <typename...Args>
        node(node* prev1,node* next1,Args&&... args):prev(prev1),next(next1),val(std::forward<Args>(args)...){};
        
    };
    node* head;
    node* tail;
    public:
    class const_iterator{
    protected:  
        const node* ptr;
    public:
        explicit const_iterator(node* p):ptr(p){};
        const T& operator*()const{
            return  ptr->val;
        }
        const_iterator& operator++(){
            ptr = ptr -> next; 
            return *this; 
        }  
        const_iterator operator++(int){
            node* ptr1 = ptr;
            ptr = ptr -> next; 
            return const_iterator(ptr1);  
        }
        bool operator==(const_iterator pos){
            return pos.ptr == ptr;
        }
        bool operator!=(const_iterator pos){
            return pos.ptr != ptr;
        }
        
        friend class list<T>; 
    };
    class iterator:const_iterator{
    public:
        explicit iterator(node* p):const_iterator(p){};
        T& operator*(){
            return  const_cast<T&>(const_iterator::operator*());
        }
        const T& operator*()const {
            return  const_iterator::operator*();
        }
        iterator& operator++(){
            const_iterator::operator++(); 
            return *this; 
        }  
        iterator operator++(int){
            iterator tmp = (*this); 
            tmp;
            ++(*this);
            return iterator(tmp);  
        }
        bool operator==(iterator pos){
            return pos.ptr == this->ptr;
        }
        bool operator!=(iterator pos){
            return pos.ptr != this->ptr;
        }
        
        friend class list<T>;
    };

    
    list():head(nullptr),tail(nullptr){};
    
    const T& front()const{
        return head -> val;
    }
    
    T& front(){
        return head -> val;
    }
    
    const T& back()const{
        return tail -> val;
    }
    
    T& back(){
        return tail -> val;
    }
    
    template <typename U>
    iterator insert (const_iterator pos,U&& arg)
    {
        if(pos == cbegin){
            
            return emplace_front(arg);
        }
        else if(pos == cend()){
            
            return emplace_back(arg); 
        }
        node* first = pos.ptr;
        node* node1 = new node(first -> prev, first, arg);
        first ->prev -> next = node1;
        first -> prev = node1;

        return iterator(node1);
    }
    
    template <typename U>
    void push_back(U&& val1){
        node* newnode = new node(tail, nullptr, std::forward<U>(val1));
        if(!head){
            head = tail = newnode;
            return;
        }
        tail -> next =  newnode;
        tail = newnode;
    }
    
    template <typename... Args>
    T& emplace_back(Args&& ... args){
        node* newnode = new node(tail ,nullptr, std::forward<Args>(args)...);
        if(!head){
            head = tail = newnode;
            return newnode->val;
        }
        tail->next = newnode;
        tail = newnode;
        return newnode -> val;
    }
    
    template <typename U> 
    void push_front(U&& val1){
        node* newnode = new node(nullptr, head, std::forward<U>(val1));
        if(!head){
            head = tail = newnode;
            return;
        }
        head -> prev = newnode;
        head = newnode; 
    }
    
    template <typename... Args>
    T&  emplace_front(Args&&...args){
        node* newnode = new node (nullptr, head, std::forward<Args>(args)...);
        
        if(!head){
            head = tail = newnode;
            return newnode -> val;
        }
        head ->prev = newnode;
        head = newnode;
        return newnode -> val;
    }
    
    void pop_front(){

        head = head -> next;
        delete head -> prev;

    }
    
    void pop_back(){
        
        tail = tail -> prev;
        delete tail -> next;
    
    }
    
    template <typename... Args>
    iterator emplace(const_iterator pos,Args&&... args){
        if(pos == cbegin())
        {
            emplace_front(std::forward<Args>(args)...);
            return begin();
        }
        if(pos == cend())
        {
            emplace_back(std::forward<Args>(args)...);
            auto it = end();
            --it;
            return it;
        }
        node* first = pos.ptr; 
        node* newnode = new node(first -> prev, first, std::forward<Args>(args)...);
        first -> prev -> next = newnode;
        first -> prev = newnode;

        return iterator(newnode);
        
    }
    
    void erase(iterator first,iterator last){

        node* fir = first -> ptr;
        node* las = last -> ptr;
        if(!first){
            return;
        }
        if(first -> prev){
            fir -> prev -> next = las -> next;
        }
        else{
            head = las; 
        }

        if(las){
           las -> prev = fir -> prev;
        }
        else{
            tail = first -> prev;
        }

        while(fir != las){
            fir = fir -> next;
            delete fir -> prev;
        }
      
    }
    
    void erase(const_iterator pos){
        node* first = pos.ptr;
        if(first == nullptr)
        {
           exit(-1);
        }
        if(pos == cbegin()){
            pop_front();
            return;
        }
        first -> prev -> next = first -> next;
        first -> next -> prev = first -> prev;
        delete first;
    }
    
    iterator begin(){
        return iterator(head); 
    }
    
    iterator end(){
        return iterator(nullptr);
    }
    
    const_iterator cbegin(){
        return const_iterator(head);
    }
    
    const_iterator cend(){
        return const_iterator(nullptr);
    }
    
};
int main()
{
    list<int> list1; 
    list1.push_back(5);
    list1.push_back(6);
    list1.push_back(7);
    list<int>::iterator it = list1.begin();
   for(auto it1:list1){
    std::cout<< it1;
   }
    return 0; 
}
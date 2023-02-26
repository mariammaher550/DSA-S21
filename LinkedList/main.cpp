/**
 * @author Mariam Abuelfotouh
 * @date 20/2/2021
 */


#include <iostream>
#include <vector>
#include <string>
#include <iomanip>

using namespace std;
template <typename T>
class List {
public:
    virtual void add(T item) = 0;
    virtual void remove(int i) = 0;
    virtual  T least() = 0;
    virtual T greatest() = 0;
    virtual T get(int i) = 0;
    virtual int indexOf(T item) = 0;
    virtual  vector<T> searchRange(T from , T before) = 0;
    virtual int size() = 0;
    virtual bool isEmpty() = 0;

};

template <typename T>
struct node {
    node<T>* next;
    T value;
};

//node head, tail;
template <typename T>
class SortedLinkedList : public List<T> {
public:
    struct node<T> *head;
    struct node<T> *tail;
    int nodesNum = 0;
    SortedLinkedList<T>(){
        head = NULL;
        tail = NULL;
    }
    /**
     * function that adds a node with item value in the linked list
     * @param item
     */
    void add(T item) {
     nodesNum++;
        //no element
        if(head == NULL){
            head = new node<T>;
            head->value = item;
            head->next = NULL;
            tail = new node<T>;
            tail = head;
            return;
        }
        else{
            if(head == tail){
                struct node<T> *newN = new node<T>;
                newN->value = item;
              item < head->value ? head = newN : tail = newN;
              head->next = tail;
              tail->next = NULL;
              return;
            }
            else {

                struct node<T> *prev = new node<T>;
                prev = head;
                struct node<T> *nxt = new node<T>;
                nxt = head->next;
                if(item < head->value){
                    struct node<T> *newN = new node<T>;
                    struct node<T> *temp = head;
                    newN->value = item;
                    newN->next = temp;
                    head = newN;
                    return;
                }
                while (nxt) {
                    if (item <= nxt->value && item >= prev->value) {
                        struct node<T> *newNode = new node<T>;
                        newNode->value = item;
                        newNode->next = nxt;
                        prev->next = newNode;
                        return;
                    }
                    prev = nxt;
                    nxt = nxt->next;
                }
                struct node<T> *newNode = new node<T>;
                newNode->value = item;
                newNode->next = NULL;
                struct node<T> *temp = new node<T>;
                temp = tail;
                temp->next = newNode;
                tail = newNode;
            }

        }
    }
    /**
     * function that remove a node form linkedlist
     * @param i
     */
    void remove(int i){
        nodesNum--;
        if(i == 1){
            head = head->next;
            return;
        }
        struct node<T> *prev = new node<T>;
        prev = head;
        struct node<T> *toR = new node<T>;
         toR= head->next;
        for(int a = 1; a < i - 1; a++){
            prev = toR;
            toR = toR->next;
        }
        //cout <<"ITEM TO BE REMOVED IS "<< toR->value << endl;
        prev->next = toR->next;
        if(toR == tail)
        {
            tail = prev;
        }

    } /// handle out of index + numNodes
    /**
     *
     * @return least element
     */
    T least(){
        return head->value;
    }
    /**
     *
     * @return greatest element
     */
    T greatest(){
        return tail->value;
    }
    /**
     * fucntion that returnt the ith least item
     * @param i
     * @return ith item
     */
    T get(int i){
        struct node<T> *curr = new node<T>;
        curr = head;
        for(int a = 1; a < i; a++)
            curr = curr->next;
        return curr->value;
    } ///handle out of index
    /**
     *
     * @param item
     * @return the index of node that has item
     */
    int indexOf(T item){
        int idx = 0;
        struct node<T> *curr = new node<T>;
        curr = head;
        while(curr){
            if(curr->value == item)
            break;
            curr = curr->next;
            idx++;
        }
        return idx + 1;
    }
    /**
     * function that search within a specific range
     * @param from
     * @param to
     * @return vector of the range
     */
    vector <T> searchRange(T from, T to){
        vector<T> items;
        struct node<T> *curr = new node<T>;
        curr = head;
        while(curr)
        {
            if(curr->value >= from && curr->value <= to)
            {
                items.push_back(curr->value);
            }
            curr = curr->next;
        }
        return items;
    } /// handle when boundaries are out of range
    int size(){
        return nodesNum;
    }
    bool isEmpty(){
        return (head == NULL);
    }
    void print(){
        struct node<T> *nxt = head;
        while(nxt != NULL){
            cout<< nxt->value << endl;
            nxt = nxt->next;
        }
    }

};
int main() {

 SortedLinkedList<pair<double,string>> list;
 pair<double, string> p ;
 int n;
 string cmd,price, name;
 cin >> n;
 while(n--){
     cin>> cmd;
     if(cmd == "ADD") {
         cin >> price;
         getline(cin, name);

         p.first = stod(price.substr(1,price.size()-1));
         p.second = name;
         list.add(p);
     }
     else if(cmd == "REMOVE"){
         cin >> price;
         getline(cin, name);
         p.first = stod(price.substr(1,price.size()-1));;
         p.second = name;
         list.remove(list.indexOf(p));
     }

     else{
         string r1,r2;
         cin >> r1 >> r2;
         vector<pair<double,string>> range;
         pair<double, string> p;

        struct node<pair<double, string> > *curr = new node<pair<double, string> >;
        curr = list.head;
        while(curr){
            if(curr->value.first >= stod(r1.substr(1, r1.size() - 1)) && curr->value.first <= stod(r2.substr(1, r2.size() - 1)))
                range.push_back(curr->value);
            curr = curr->next;
        }

         for(int a = 0; a < range.size(); a++)
         {
             cout << "$" << fixed <<  setprecision(2) << range[a].first << range[a].second;
             if(a < range.size() - 1) cout << ", ";
         }
         cout << endl;

     }

     }


 }




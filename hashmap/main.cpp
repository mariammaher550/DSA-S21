/**
 * @author Mariam Abuelfotouh
 * @date 20/2/2021
 */

#include <iostream>
#include<vector>
#include <string>
#include <utility>
#include <iomanip>
using namespace std;

//base class
template <typename T> class Map {
public:
   virtual void insert(long long key, T item) = 0;
     virtual bool isEmpty() = 0;
     virtual int size() = 0;
    virtual int hashFun(long long key) = 0;
    virtual T get(long long key) = 0;
};
template <typename T> class HashMap : public Map<T>{
public:
    static const int capacity = 50021;
    long long uniqKeys[capacity] = {};
    bool existance [capacity] = {};
    int numOfEntery = 0;
    pair<long long,T> hashtable[capacity] ;
/**
 * a hash function
 * @param key
 * @return hash value
 */
    int hashFun(long long key) override {
        return key % capacity;
    };
    /**
     * function that inserts items in hashtable
     * @param key
     * @param item
     */
    void insert(long long key, T item) override{
        uniqKeys[numOfEntery] = key;
        numOfEntery++;
        int idx = hashFun(key);
        //cout << "The hash is "<<  idx <<endl;
        pair<long long , T> p;
        p.second = item;

        //linear prop
        while(idx < capacity)
        {
            if(!hashtable[idx].first)
            {
                p.first = key;
                hashtable[idx] = p;
                existance[idx] = 1;
                //cout << "The final idx is " << idx << endl;
                return;
            }
            idx++;
        }
    }
    /**
     * function that returns an item from hashtable
     * @param key
     * @return item
     */
    T get (long long key) override {

        int idx = hashFun(key);

        while(idx < capacity){
            if(key == hashtable[idx].first)
            {
                return hashtable[idx].second;
            }
            idx++;
        }
        cerr<< "ITEM NOT FOUND" << endl; //if an item not found
    }
    /**
     *
     * @return size
     */
    int size() override{
        return numOfEntery;
    }
    /**
     *
     * @return true if hashtable is empty
     */
    bool isEmpty() override{
        return (!numOfEntery);
    }
    /**
     *
     * @param key
     * @return if a key already exists in hashtable or not
     */
    bool exist(long long key){
        int idx = hashFun(key);
        if(!existance[idx]) return false;
        while(idx < capacity){
            if(key == hashtable[idx].first)
            {
                return true;
            }
            idx++;
        }
        return false;
    }
    /**
     * function that modify value of a key in hashtable
     * @param key
     * @param item
     */
    void modify(long long key, T item){
        int idx = hashFun(key);

        while(idx < capacity){
            if(key == hashtable[idx].first)
            {
                hashtable[idx].second = item;
                return;
            }
            idx++;
        }
        cerr << "ITEM NOT FOUND" << endl; // if item is not found
    }
    /**
     *
     * @return number of unique keys in the hashtable
     */
    long long *uniqueKeys(){
        return uniqKeys;
    }
};

int main() {

    HashMap<double> *days = new HashMap< double>;// a hashmap of a hashmap , each day has a hashmap of its recipts,where receipts are identified with hours;
    int uniqRec[50021] = {};
    pair<long long , string> reciepts[50021];
    int recCount = 0;
    int n ;
    string day, hour, reciept, price, item;
    string rec = "";
    long long dayV,recV;
    int digit;
    double priceV;
    pair<long long , string> inp;
    cin >> n;
    for(int idx = 0; idx < n; idx++)
    {
        cin >> day >> hour >> reciept >> price;
        getline(cin , item);

        dayV = stol(day.substr(0, 4) + day.substr(5, 2) + day.substr(8, 2));
        priceV = stod(price.substr(1, price.size() - 1));
        if(days->exist(dayV)){
            bool flag = true;
            priceV += days->get(dayV);
            days->modify(dayV, priceV);
            for(int a = 0; a < recCount; a++)
            {
                if(dayV == reciepts[a].first && reciepts[a].second == reciept)
                {
                    flag = false;
                }
            }
            if(flag){
                inp.first = dayV;
                inp.second = reciept;
                reciepts[recCount] = inp;
                recCount++;
                uniqRec[days->hashFun(dayV)]++;
            }
        }
     else{
         inp.first = dayV;
         inp.second = reciept;
         uniqRec[days->hashFun(dayV)]++;
         days->insert(dayV, priceV);
            reciepts[recCount] = inp;
            recCount++;

     }

    }

    long long *arr = days->uniqueKeys();
    double total;
    string date = "";
    string temp;
    int uniq ;
    for(int i = 0; i < days->size(); i++){

        temp = to_string(*(arr + i));
        total = days->get(*(arr+i));
        uniq = uniqRec[days->hashFun(*(arr + i))];
        cout <<  temp.substr(0, 4) <<"-"<< temp.substr(4, 2) << "-" << temp.substr(6, 2) << " $" << fixed << setprecision(2) << total << " " <<  uniq << endl;


    }
    return 0;
}

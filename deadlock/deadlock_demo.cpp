/*
    philosophers dining and eating..
*/
#include<iostream>
#include<mutex>
#include<thread>
#include<vector>
using namespace std;
#define THREAD_CNT  5

// shared resource..
int soup_count = 15000;

void runFunction(const int id, vector<mutex>& spoon)
{
    int loc_count = 0;
    while(soup_count > 0) {

        scoped_lock lock(spoon[0], spoon[1], spoon[2], spoon[3], spoon[4]);
        // for(int i = id; i < (THREAD_CNT+id); i++) {
        //     //unique_lock<mutex> spoon_lock(spoon[i]);
        //     spoon[i % THREAD_CNT].lock();
        // }
        
        //spoon.lock();
        soup_count--;
        loc_count++;
        //spoon.unlock();

        // for(int i = 0; i < THREAD_CNT; i++) {
        //     spoon[i % THREAD_CNT].unlock();
        // }
            
    }

    spoon[0].lock();
    cout << "Thread id: " << id << " took soup " << loc_count << " times.." << endl;  
    spoon[0].unlock();
}



int main()
{   
    vector<mutex> spoon(THREAD_CNT);
    //mutex spoon[THREAD_CNT];
    thread person[THREAD_CNT];

    for(int i = 0; i < THREAD_CNT; i++)
    {
        person[i] = thread(runFunction, i, ref(spoon));
    }
    
    for(int i = 0; i < THREAD_CNT; i++)
    {
        person[i].join();
    }   
}
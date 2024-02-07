#include "request_queue.h"
using namespace std;
    RequestQueue::RequestQueue(const SearchServer& search_server) 
    : search_server_(search_server)
    {
        
    }   
    
    vector<Document> RequestQueue::AddFindRequest(const string& raw_query, DocumentStatus status) {
        vector<Document> r = search_server_.FindTopDocuments(raw_query, status);
        if(!r.empty())
        {
            if(requests_.size() == min_in_day_)
            {
                requests_.pop_front();
            }
            requests_.push_back({true,r});
        }
        else
        {
            if(requests_.size() == min_in_day_)
            {
                requests_.pop_front();
            }
            requests_.push_back({false,r});
        }       
        return r;        
    }
    
    vector<Document> RequestQueue::AddFindRequest(const string& raw_query) {
        vector<Document> r = search_server_.FindTopDocuments(raw_query);       
        if(!r.empty())
        {
            if(requests_.size() == min_in_day_)
            {
                requests_.pop_front();
            }
            requests_.push_back({true,r});
        }
        else
        {
            if(requests_.size() == min_in_day_)
            {
                requests_.pop_front();
            }
            requests_.push_back({false,r});
        }       
        return r;        
    }
    
    int RequestQueue::GetNoResultRequests() const {
    int result = 0;
    for(auto x: requests_)
    {
        if (x.empty == false)
        {        
            result++;           
        }     
        
    }
        return result;
    }

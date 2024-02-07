#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <utility>

template <typename Iterator>
class Paginator {    
public:
explicit Paginator(Iterator it_begin,Iterator it_end, size_t page_size)        
{       
    int full_pages = distance(it_begin,it_end)/page_size;
    int num_doc_last_pages = distance(it_begin,it_end)%page_size;
    for(int x = 0;x<full_pages;x++)
    {           
        pages_.push_back({it_begin,it_begin + page_size});
        it_begin = it_begin+page_size;
    }        
    if(num_doc_last_pages > 0)
    {
        pages_.push_back({it_begin,it_begin + num_doc_last_pages});
    }
}
    
auto ReturnPages() {    
    return pages_;
}
    
Iterator begin() const {
    return pages_.first;
}
 
Iterator end() const {
    return pages_.second;
}
    
private:
std::vector<std::pair<Iterator,Iterator>> pages_;    
};

template <typename Iterator>
std::ostream& operator<<(std::ostream& output, std::pair<Iterator,Iterator> page) 
{
    while (page.first != page.second)
    {
        output <<"{ document_id = " << page.first->id << ", relevance = " << page.first->relevance 
        << ", rating = " << page.first->rating << " }";
        page.first= next(page.first, 1);
    } 
    return output;
}

template <typename Container>
auto Paginate(const Container& c, size_t page_size) 
{
    Paginator r = Paginator(begin(c), end(c), page_size);
    return r.ReturnPages();
}

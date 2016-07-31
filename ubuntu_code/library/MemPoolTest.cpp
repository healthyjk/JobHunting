#include "MemPool.h"  
  
#define DATA_BLOCK_LEN 1500  

using std::cout;
  
int main()  
{  
    CMemPool myPool1(DATA_BLOCK_LEN, 0, 10);  
  
    std::cout <<"myPool1 block size = "<<myPool1.BlockSize()<< std::endl;  
    std::cout <<"myPool1 allocated block num = "<<myPool1.Allocated()<< std::endl;  
    std::cout <<"myPool1 available block num = "<<myPool1.Available()<< std::endl<< std::endl;  
  
    std::vector<void*> ptrs;  
    for (int i = 0; i < 10; ++i)  
    {  
        ptrs.push_back(myPool1.Get());  
    }  
  
    myPool1.Get();  
  
    int iavilable = 0;  
    for (std::vector<void*>::iterator it = ptrs.begin(); it != ptrs.end(); ++it)  
    {  
        myPool1.Release(*it);  
        ++iavilable;  
        std::cout <<"myPool1 available block num = "<<myPool1.Available()<< std::endl;  
    }  
  
    CMemPool myPool2(DATA_BLOCK_LEN, 5, 10);  
    std::cout << std::endl<<"myPool2 block size = "<<myPool2.BlockSize()<< std::endl;  
    std::cout <<"myPool2 allocated block num = "<<myPool2.Allocated()<< std::endl;  
    std::cout <<"myPool2 available block num = "<<myPool2.Available()<< std::endl;  
  
    return 0;  
}  

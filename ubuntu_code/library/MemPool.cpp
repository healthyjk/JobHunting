/*======================================================
#
# Filename: MemPool.cpp
#
# Version: 
#
# Last modified: 2016-02-26 14:11
#
# Description: 
#
# Author: jkyan - jkyan@fudan.edu.cn
#
# Copyright (c) 2014, All Right Reserved, MicroSystems, Fudan University
#
# Mode: C++; tab-width: 2;
# vim: set tabstop=2 softtabstop=2 shiftwidth=2 expandtab: 
#
=====================================================*/

#include "MemPool.h"  

CMemPool::CMemPool(std::size_t blockSize, int preAlloc, int maxAlloc):  
	m_blockSize(blockSize),  
	m_maxAlloc(maxAlloc),  
	m_allocated(preAlloc) {  
	if ( preAlloc < 0 || maxAlloc == 0 || maxAlloc < preAlloc ) {  
		std::cout <<"CMemPool::CMemPool parameter error."<< std::endl;  
	}  

	int r = BLOCK_RESERVE;  
	if (preAlloc > r)  
		r = preAlloc;  
	if (maxAlloc > 0 && maxAlloc < r)  
		r = maxAlloc;  
	m_blocks.reserve(r);  
	for (int i = 0; i < preAlloc; ++i) {  
		m_blocks.push_back(new char[m_blockSize]);  
	}  
}  


CMemPool::~CMemPool() {  
	for (BlockVec::iterator it = m_blocks.begin(); it != m_blocks.end(); ++it) {  
		std::cout << "delete it..." << std::endl;
		delete [] *it;  
	}  
}  


void* CMemPool::Get() {  
	pthread_mutex_lock(&m_mutex);

	if (m_blocks.empty()) {  
		if (m_maxAlloc == 0 || m_allocated < m_maxAlloc) {  
			++m_allocated;  
			pthread_mutex_unlock(&m_mutex);
			return new char[m_blockSize];  
		}  
		else {  
			std::cout <<"CMemPool::get CMemPool exhausted."<< std::endl;  
			pthread_mutex_unlock(&m_mutex);
			return (void *)NULL;  
		}  
	} else {  
		char* ptr = m_blocks.back();  
		m_blocks.pop_back();  
		pthread_mutex_unlock(&m_mutex);
		return ptr;  
	}  
}  

void CMemPool::Release(void* ptr) {  
	pthread_mutex_lock(&m_mutex);
	m_blocks.push_back(reinterpret_cast<char*>(ptr));  
	pthread_mutex_unlock(&m_mutex);
} 

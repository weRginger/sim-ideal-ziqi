#include "owbp.h"

uint32_t OwbpCache::blkHitAccess(const uint64_t& PageNo  , cacheAtom& value, uint32_t status){
	
}

void OwbpCache::insertNewBlk(cacheAtom& value){
	uint64_t currSsdBlkNo = value.getSsdblkno();
	uint32_t currLine = value.getLineNo();
	deque<nextPageRef> nextPages;
	pair< map<uint64_t,OwbpCacheBlock>::iterator, bool> ret;
	nextPages = getFuturePageRef(currSsdBlkNo, currLine);
	
	OwbpCacheBlock tempBlock(nextPages,value);
	
	ret = blkID_2_DS.insert(pair<uint64_t,OwbpCacheBlock>(currSsdBlkNo,tempBlock));
	
	assert ( ret.second == true ) ; 
	
	
}

// access to a page 
uint32_t OwbpCache::access(const uint64_t& k  , cacheAtom& value, uint32_t status) {
	
	assert(_capacity != 0);
	PRINTV(logfile << "Access page number: " << k << endl;);
	uint64_t currSsdBlkNo = value.getSsdblkno();
	// Attempt to find existing block 
	map< uint64_t, OwbpCacheBlock >::iterator 	blkit;
	blkit = blkID_2_DS.find(currSsdBlkNo);
	
	if( blkit ==  blkID_2_DS.end() ) {
		status |= BLKMISS | PAGEMISS;
		if(status & WRITE){
			insertNewBlk(k, value);
		}
	}
	else{
		status |= BLKHIT;
		//PAGEMISS or hit to status is return value of this function
		status |= blkHitAccess(k, value, status);
	}
	
	return status;
// 	BiMapType::left_const_iterator left_it;
// 	left_it = BiMap.left.find( value.getSsdblkno() ); 
	
	
// 	if(left_it == BiMap.left.end()) {
// 		// We don’t have it:
// 		PRINTV(logfile << "Miss on block: " << value.getSsdblkno() << endl;);
// 		// Evaluate function and create new record
// 		cacheAtom v = _fn(k, value);
// 		
// 		///ARH: write buffer inserts new elements only on write miss
// 		if(status & WRITE) {
// 			status |=  insert(k, v);
// 			PRINTV(logfile << "Insert block "<< v.getSsdblkno() <<" , as a result of page miss on page " << k << endl;);
// 		}
// 		
// 		return (status | BLKMISS);
// 	} else {
// 		PRINTV(logfile << "Hit on Block: " << value.getSsdblkno() << endl;);
// 		status |= BLKHIT;
// 		
// 		SsdBlock_type tempBlock;
// 		SsdBlock_type::iterator pageit;
// 		
// // 		tempBlock = it->second;
// 		pageit = tempBlock.find(k);
// 		
// 		if(pageit == tempBlock.end() ){
// 			PRINTV(logfile << "Miss on key: " << k << endl;);
// 			tempBlock.insert(k);
// 			return (status | PAGEMISS );
// 		}
// 		else{
// 			PRINTV(logfile << "Hit on key: " << k << endl;);
// 			return (status | PAGEHIT );
// 		}
// 		// We do have it. Do nothing in MIN cache
// 	}
	
} //end access

uint32_t OwbpCache::insert( uint64_t k, cacheAtom v) {
// 	PRINTV(logfile << "insert key " << k  << endl;);
// 	int status = 0;
// 	uint64_t tempBlkNo = v.getSsdblkno(); 
// 	// Method is only called on cache misses
// 	assert(  BiMap.left.find( tempBlkNo) == BiMap.left.end());
// 	
// 	// Make space if necessary
// 	if( currSize == _capacity) {
// 		PRINTV(logfile << "Cache is Full with " << BiMap.left.size() << " blocks, and "<< currSize <<" pages" << endl;);
// 		evict();
// 		status = EVICT;
// 	}
// 	
// 	uint32_t futureDist = getFutureBlkDist(tempBlkNo, v.getLineNo());
// 	
// 	BmAtom bmAtom(tempBlkNo, futureDist, v );
// 	BiMap.insert( bmAtom ); 
// 	// Record ssdblkno and lineNo in the maxHeap
// 	uint32_t tempLineNo = v.getLineNo();
// 	uint64_t tempSsdblkno = v.getSsdblkno();
// 	PRINTV(logfile<<"key "<<k<<" is in ssdblock "<< tempSsdblkno<<endl;);
// 	uint32_t nextAccessLineNo = accessOrdering.nextAccess(tempSsdblkno,tempLineNo);
// 	PRINTV(logfile<<"next access to block "<<tempSsdblkno<<" is in lineNo "<<nextAccessLineNo<<endl;);
// 	assert( tempLineNo <= _gConfiguration.maxLineNo|| nextAccessLineNo <= _gConfiguration.maxLineNo || nextAccessLineNo == INF );
// 	HeapAtom tempHeapAtom(nextAccessLineNo, tempSsdblkno);
// 	maxHeap.push(tempHeapAtom);
// 	
// 	// Create the key-value entry,
// 	SsdBlock_type tempBlock;
// 	tempBlock.clear();
// 	tempBlock.insert(k);
// 	// linked to the usage record.
// 	_key_to_block.insert(make_pair(v.getSsdblkno(),tempBlock));
	// No need to check return,
	// given previous assert.
// 	return status;
}

void OwbpCache::evict(){
// 	PRINTV(logfile<<" evicting victim block "<< maxHeapAtom.key <<" with next lineNo "<< maxHeapAtom.lineNo << endl;);
}
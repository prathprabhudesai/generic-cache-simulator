typedef unsigned long ulong;
using namespace std;

string  REPLACEMENT_POLICY;
string  INCLUSION_TYPE;
bool ISL2;

class Cache {
 private:
  ulong size, assoc, blockSize, numberOfSets, blockOffset, reads, writes, readMisses, writeMisses, writeBacks,  evictedAddress;
  string missType;
  bool writeBack, evicted;
  class CacheBlock*** CacheBlock;
  Cache* lowerCache;

 public: 
  ulong RPSeqNo; //Replacement Policy
  ulong* Set;

  Cache(ulong size, ulong assoc, ulong blockSize) {
    if(assoc < 1) {
      cout << "Associativity is wrong. Please check the configuration again!!" << endl;
      exit(1); 
    }
    this->RPSeqNo = 0;
    this->size = size;
    this->assoc = assoc;
    this->blockSize = blockSize;
    this->numberOfSets = size/(blockSize * assoc); 
    this->blockOffset = (ulong) log2(blockSize);
    reads = writes = readMisses = writeMisses = writeBacks = 0; 
 
    Set = new ulong[numberOfSets];
    this->CacheBlock = new class CacheBlock**[numberOfSets];
    for (int i=0; i < (int) numberOfSets; ++i){
      Set[i] = 0;
      CacheBlock[i] = new class CacheBlock*[assoc];
      for (int j=0; j < (int) assoc; ++j) {
	CacheBlock[i][j] = new class CacheBlock(assoc);
      } 
    } 
    this->lowerCache = NULL;
  }

  void initL2(Cache* cache) {
    this->lowerCache = cache;
  }

  // Getters and setters for Private variables

  ulong getEvictedAddress() { return evictedAddress; }

  void setEvictedAddress(ulong tag) { if(evicted) evictedAddress = getAddress(tag); }

  void setWriteBack() { writeBack = true; }

  void incWriteBacks(){ writeBacks++; }

  void incReads() { reads++; }

  void incWrites() { writes++; }
  
  void addReadMiss() { readMisses++;  missType = "READMISS"; }

  void addWriteMiss() { writeMisses++;  missType = "WRITEMISS"; }

  ulong getMemoryTraffic() { return(readMisses + writeMisses + writeBacks); }

  float getMissRate() { return(((float)(readMisses + writeMisses))/((float)(reads + writes))); } 

  ulong getReads() { return reads; }

  ulong getWrites() { return writes; }

  ulong getReadMisses() { return readMisses; }

  ulong getWriteMisses() { return writeMisses; }

  ulong getWriteBacks() { return writeBacks; } 

  Cache * getLowerCache() { return lowerCache; }

  
  // checking bool conditions
  
  bool isWriteBack() { return writeBack; }

  bool isEvicted() { return evicted; }

  bool isMiss() { return (missType == "READMISS" || missType == "WRITEMISS"); }

  bool isHit() { return (missType == "HIT"); }

  // Bit manipulations and calculations

  ulong getAddress(ulong tag) { return (tag << blockOffset); }

  ulong getIndex(ulong address) { return (getTag(address) & (ulong)(numberOfSets - 1)); }

  ulong getTag(ulong address) { return (address >> (blockOffset)); }
  
  // Try to access the block
  
  void getBlockAccess(ulong address, char method, bool isL2Exclusive ){
    missType = "UNKNOWN";
    evicted = writeBack = false;
    class CacheBlock* CacheBlock = findCacheBlock(address);
    if(method == 'r') incReads();  else incWrites(); 
      
    if(CacheBlock == NULL) {
      if (method == 'r') addReadMiss();  else addWriteMiss();
      if(isL2Exclusive)  CacheBlock = fillCacheBlock(address);
    }
    else {
      missType = "HIT";
      if (REPLACEMENT_POLICY != "FIFO")  processLRU(CacheBlock);
    } 
    if (method == 'w')
      CacheBlock->setState("DIRTY"); 
  }

  // Find the block

  class CacheBlock* findCacheBlock(ulong address){
    ulong tag = getTag(address);
    class CacheBlock** CacheBlock = this->CacheBlock[getIndex(address)];
    for(int i=0; i < (int) assoc; ++i) {
      if((tag == CacheBlock[i]->getTag()) && CacheBlock[i]->isValid())
	return CacheBlock[i]; 
    }
    return NULL;
  }

  // Get The Block
  class CacheBlock* getBlockToBeFilled(ulong address) {
    class CacheBlock* blockToBeFilled = NULL;
    ulong index = getIndex(address);

    for (int i=0; i < (int) assoc; ++i) {
      if(!CacheBlock[index][i]->isValid())
	return CacheBlock[index][i];
    }

    if (blockToBeFilled == NULL) {
      evicted = true;
      blockToBeFilled = CacheBlock[index][0];
      for (int i=1; i < (int) assoc; ++i){
	if(CacheBlock[index][i]->getSeq() < blockToBeFilled->getSeq()){
	  blockToBeFilled = CacheBlock[index][i];
	}
      }
    } 
    return blockToBeFilled;
  }

  // Fill The Block
  
  class CacheBlock* fillCacheBlock(ulong address){
    int index = getIndex(address);
    class CacheBlock* blockToBeFilled = getBlockToBeFilled(address);
    setEvictedAddress(blockToBeFilled->getTag());

    if (blockToBeFilled != NULL && blockToBeFilled->isDirty()) {
      setWriteBack();
      incWriteBacks();
    }
    if (blockToBeFilled->isValid()){ Set[index] = blockToBeFilled->getSeq(); }

    blockToBeFilled->setTag(getTag(address));
    blockToBeFilled->setState("VALID");
    processLRU(blockToBeFilled);
    return blockToBeFilled; 
  }

  // LRU Replacement Policy
  void processLRU(class CacheBlock* cacheBlock) {
    cacheBlock->setSeq(++RPSeqNo);
  }
  
  // Invalidate the block
  
  void invalidateBlock(ulong address){
    class CacheBlock* cacheBlock = findCacheBlock(address);
    if(cacheBlock) {
      if(INCLUSION_TYPE == "INCLUSION" && lowerCache){
	if (cacheBlock->isDirty()){
	  setWriteBack();
	  incWriteBacks();
	  lowerCache->setWriteBack();
	  lowerCache->incWriteBacks();
	}
      }
      cacheBlock->setState("INVALID");
    } 
  }
};

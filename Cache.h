typedef unsigned long ulong;
using namespace std;

string  REPLACEMENT_POLICY;
string  INCLUSION_TYPE;
bool ISL2;
bool EXCLUSIVITY;

class Cache {
 private:
  ulong size, assoc, blockSize, numberOfSets, blockOffset, reads, writes, readMisses, writeMisses, writeBacks,  evictedAddress, loopComp;
  string missType;
  bool writeBack, evicted;
  class CacheBlock*** CacheBlock;
  Cache* lowerCache;

 public: 
  ulong RPSeqNo; //Replacement Policy
  ulong* Set;

  Cache(ulong blockSize, ulong assoc, ulong size) {
    reads = writes = readMisses = writeMisses = writeBacks = loopComp = 0;
    this->RPSeqNo = 0;
    this->size = size;
    this->assoc = assoc;
    this->blockSize = blockSize;
    this->numberOfSets = size/(blockSize * assoc); 
    this->blockOffset = (ulong) log2(blockSize);
    Set = new ulong[numberOfSets];
    this->CacheBlock = new class CacheBlock**[numberOfSets];
    for (int i=0; i < (int) numberOfSets; ++i){
      CacheBlock[i] = new class CacheBlock*[assoc];
      for (int j=0; j < (int) assoc; ++j) {
	loopComp++;
	CacheBlock[i][j] = new class CacheBlock(assoc);
      }
      Set[i] = 0;
    } 
    this->lowerCache = NULL;
  }

  void initL2(Cache* cache) {
    this->lowerCache = cache;
  }

  // Getters and setters for Private variables

  ulong getEvictedAddress() { return this->evictedAddress; }

  void setEvictedAddress(ulong tag) { if(this->evicted) this->evictedAddress = getAddress(tag); }

  void setWriteBack(bool cond) { this->writeBack = cond; }

  void setEvicted(bool cond) { this->evicted = cond; }

  void incWriteBacks(){ this->writeBacks++; }

  void incReads() { this->reads++; }

  void incWrites() { this->writes++; }
  
  void addReadMiss() { this->readMisses++;  this->missType = "READMISS"; }

  void addWriteMiss() { this->writeMisses++;  this->missType = "WRITEMISS"; }

  ulong getMemoryTraffic() { return(this->readMisses + this->writeMisses + this->writeBacks); }

  float getMissRate() { return(((float)(this->readMisses + this->writeMisses))/((float)(this->reads + this->writes))); } 

  ulong getReads() { return this->reads; }

  ulong getWrites() { return this->writes; }

  ulong getReadMisses() { return this->readMisses; }

  ulong getWriteMisses() { return this->writeMisses; }

  ulong getWriteBacks() { return this->writeBacks; } 

  Cache * getLowerCache() { return this->lowerCache; }

  // checking bool conditions
  
  bool isWriteBack() { return this->writeBack; }

  bool isEvicted() { return this->evicted; }

  bool isMiss() { return (this->missType == "READMISS" || this->missType == "WRITEMISS"); }

  bool isHit() { return (this->missType == "HIT"); }

  // Bit manipulations and calculations

  ulong getAddress(ulong tag) { return (tag << blockOffset); }

  ulong getIndex(ulong address) { return (getTag(address) & (ulong)(numberOfSets - 1)); }

  ulong getTag(ulong address) { return (address >> (blockOffset)); }
  
  // Try to access the block
  
  void getBlockAccess(ulong address, char method){
    missType = "UNKNOWN";
    setWriteBack(false);
    setEvicted(false);
    
    class CacheBlock* CacheBlock = findCacheBlock(address);
    if(method == 'r') incReads();  else incWrites(); 
      
    if(CacheBlock == NULL) {
      if (method == 'r') addReadMiss();  else addWriteMiss();
      if(EXCLUSIVITY)  CacheBlock = fillCacheBlock(address);
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
      loopComp++;
      if((tag == CacheBlock[i]->getTag()) && CacheBlock[i]->isValid())
	return CacheBlock[i]; 
    }
    return NULL;
  }

  // Get The Block
  class CacheBlock* getBlockToBeFilled(ulong address) {
    class CacheBlock* blockToBeFilled = getInvalidBlock(getIndex(address));
    if (!blockToBeFilled) {
      setEvicted(true);
      blockToBeFilled = getRepPolBlock(getIndex(address)); 
    } 
    return blockToBeFilled;
  }


  // Check the invalid/empty block
  class CacheBlock* getInvalidBlock(ulong index){
    for (int i=0; i < (int) assoc; ++i) {
      loopComp++;
      if(!CacheBlock[index][i]->isValid())
	return CacheBlock[index][i]; 
    }
    return NULL;
  }


  class CacheBlock* getRepPolBlock(ulong index){
    class CacheBlock* block = CacheBlock[index][0];
    for (int i=1; i < (int) assoc; ++i){
      loopComp++;
      if(CacheBlock[index][i]->getSeq() < block->getSeq()){
	block = CacheBlock[index][i];
      }
    }
    return block;
  }

  // Fill The Block
  
  class CacheBlock* fillCacheBlock(ulong address){
    int index = getIndex(address);
    class CacheBlock* blockToBeFilled = getBlockToBeFilled(address);
    setEvictedAddress(blockToBeFilled->getTag());

    if (blockToBeFilled != NULL && blockToBeFilled->isDirty()) {
      setWriteBack(true);
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
	  setWriteBack(true);
	  incWriteBacks();
	  lowerCache->setWriteBack(true);
	  lowerCache->incWriteBacks();
	}
      }
      cacheBlock->setState("INVALID");
    } 
  }
};

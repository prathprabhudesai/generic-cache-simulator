#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<math.h>
#include<bitset>
#include<iostream>
#include<string.h>
#include "CacheBlock.h"
#include "Cache.h"
using namespace std;

typedef unsigned long ulong;


// Basic Functions assisting Main 

bool readCmdInput(char *argv[],ulong *blockSize,ulong *l1Size,ulong *l1Assoc, ulong *l2Size, ulong *l2Assoc){

  if(argv[1] == NULL) {
    cout << "No input parameters are provided" << endl;
    cout << "Valid Input: .\\sim_cache <BLOCKSIZE> <L1_SIZE> <L1_ASSOC> <L2_SIZE> <L2_ASSOC> <REPL_POLICY> <INCLUSION> <TRACE_FILE> " << endl;
    return false;
  }

  *blockSize = atoi(argv[1]);
  *l1Size = atoi(argv[2]);
  *l1Assoc = atoi(argv[3]);
  *l2Size = atoi(argv[4]);
  *l2Assoc = atoi(argv[5]);

  switch(atoi(argv[6])) {
  case 0: REPLACEMENT_POLICY = "LRU";  break;
  case 1: REPLACEMENT_POLICY = "FIFO";  break;
  default: cout << "Wrong Replacement Policy: Valid Options: 0: LRU, 1: FIFO" << endl;  return false; 
  }
  
  switch(atoi(argv[7])){
  case 0: INCLUSION_TYPE = "NON-INCLUSIVE";  break;
  case 1: INCLUSION_TYPE = "INCLUSIVE";  break;
  case 2: INCLUSION_TYPE = "EXCLUSIVE";  break;
  default: cout << "Wrong Inclusion Type: Valid Options 0: NON-INCLUSIVE, 1: INCLUSIVE, 2: EXCLUSIVE" << endl;  return false;
  }
  
  ISL2 = (*l2Size == 0) ? false : true;
  return true;
}


void printCacheConfig(ulong *blockSize, ulong *l1Size, ulong *l1Assoc, ulong *l2Size, ulong * l2Assoc,char fname[] ){
  cout << "==== Simulator Configuration ====" << endl;
  cout << "BLOCKSIZE: \t\t" << *blockSize << endl;
  cout << "L1_SIZE: \t\t" << *l1Size << endl;
  cout << "L1_ASSOC: \t\t" << *l1Assoc << endl;
  cout << "L2_SIZE: \t\t" << *l2Size << endl;
  cout << "L1_ASSOC: \t\t" << *l2Assoc << endl;
  cout << "REPLACEMENT POLICY: \t" << REPLACEMENT_POLICY << endl;
  cout << "INCLUSION PROPERTY: \t" << INCLUSION_TYPE << endl;
  printf("trace_file: \t\t%s\n",fname);
}

/*
  class CacheBlock{
  private:
  ulong assoc, seq, index, tag;
  string state;

  public:
  // Constructor
  CacheBlock(ulong assoc) {
  this->assoc = assoc;
  this->seq = 0;
  this->index = 0;
  this->state = "INVALID";
  }

  //Destructor
  ~CacheBlock(){ }

  //Valid
  bool isValid() const {
  return (state != "INVALID");
  }

  bool isDirty() const {
  return (state == "DIRTY");
  }

  void incSeq(){
  ++seq;
  }

  //getters and setters for the cache private params
  ulong getIndex() const {
  return index;
  }

  void setIndex(ulong index) {
  this->index = index;
  }

  ulong getSeq() const {
  return seq;
  }

  void setSeq(ulong seq) {
  this->seq = seq;
  }

  string getState() const {
  return state;
  }

  void setState(string state) {
  this->state = state;
  }

  ulong getTag() const {
  return tag;
  }

  void setTag(ulong tag) {
  this->tag = tag;
  }
  
  };

*/
/*
  class Cache {
  private:
  ulong size, assoc, blockSize, numberOfSets, blockOffset;
  ulong reads, writes, readMisses, writeMisses, writeBacks;
  ulong evictedAddress;
  string missType;
  bool writeBack, evicted;
  class CacheBlock*** CacheBlock;
  Cache* lowerCache;

  public:
  // Constructor
  ulong RPSeqNo;
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

  // L2 cache initialization

  void initL2(Cache* cache) {
  this->lowerCache = cache;
  }

  // Fill Blocks

  class CacheBlock* fillCacheBlock(ulong address){
  int index = getIndex(address);
  class CacheBlock* blockToBeFilled = getBlockToBeFilled(address);
  setEvictedAddress(blockToBeFilled->getTag());
  if (blockToBeFilled != NULL && blockToBeFilled->isDirty()) {
  setWriteBack();
  incWriteBacks();
  }
  if (blockToBeFilled->isValid()){
  Set[index] = blockToBeFilled->getSeq();
  }

  blockToBeFilled->setTag(getTag(address));
  blockToBeFilled->setState("VALID");
  processLRU(blockToBeFilled);
  return blockToBeFilled; 
  }

  void processLRU(class CacheBlock* cacheBlock){
  cacheBlock->setSeq(++RPSeqNo);
  }
  
  ulong getEvictedAddress() const{
  return evictedAddress;
  }

  void setEvictedAddress(ulong tag) {
  if (!evicted) return;
  evictedAddress = getAddress(tag);
  }

  ulong getAddress(ulong tag) const{
  return (tag << blockOffset);
  }

  class CacheBlock* getBlockToBeFilled(ulong address){
  class CacheBlock* blockToBeFilled = NULL;
  ulong index = getIndex(address);

  //check if there are invalid blocks in the set
  for (int i=0; i < (int) assoc; ++i){
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

  ulong getIndex(ulong address) const {
  ulong index, tagslack;
  tagslack = (ulong) (numberOfSets - 1);
  index = getTag(address) & tagslack;
  assert(index < numberOfSets);
  return index;
  }

  ulong getTag(ulong address) const{
  return (address >> (blockOffset));
  }


  class CacheBlock* findCacheBlock(ulong address){
  ulong tag = getTag(address);
  class CacheBlock** CacheBlock = this->CacheBlock[getIndex(address)];
  for(int i=0; i < (int) assoc; ++i) {
  if((tag == CacheBlock[i]->getTag()) && CacheBlock[i]->isValid())
  return CacheBlock[i]; 
  }
  return NULL;
  }


  bool isWriteBack() {
  return writeBack;
  }

  bool isEvicted() {
  return evicted;
  }

  void setWriteBack() {
  writeBack = true; 
  }

  void incWriteBacks(){
  writeBacks++;
  }
  
  void addReadMiss(){
  readMisses++;
  missType = "READMISS";
  }

  void addWriteMiss(){
  writeMisses++;
  missType = "WRITEMISS";
  }

  bool isMiss(){
  if(missType == "READMISS" || missType == "WRITEMISS")
  return true;
  else
  return false;
  }

  bool isHit(){
  if(missType == "HIT")
  return true;
  else
  return false;
  }

  
  void getBlockAccess(ulong address, char method, bool isL2Exclusive ){
  missType = "UNKNOWN";
  evicted = writeBack = false;
  class CacheBlock* CacheBlock = findCacheBlock(address);
  if(method == 'r') reads++;
  else writes++; 
      
  if(CacheBlock == NULL) {
  if (method == 'r') addReadMiss();
  else addWriteMiss();
  if(isL2Exclusive)
  CacheBlock = fillCacheBlock(address);
  }
  else{
  missType = "HIT";
  if (REPLACEMENT_POLICY != "FIFO"){
  processLRU(CacheBlock);
  }
  }
  if (method == 'w')
  CacheBlock->setState("DIRTY");
    
  }

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

  void displayOutput(){
  cout << "\n===== Simulation Results =====" << endl;
  cout << "a. Number of L1 reads: \t\t\t" << reads << endl;
  cout << "b. Number of L1 read misses: \t\t" << readMisses << endl;
  cout << "c. Number of L1 writes: \t\t" << writes << endl;
  cout << "d. Number of L1 write misses: \t\t" << writeMisses << endl;
  if(ISL2){
  cout << "g. Number of L2 reads: \t\t\t" << lowerCache->reads << endl;
  cout << "h. Number of L2 read misses: \t\t" << lowerCache->readMisses << endl;
  cout << "i. Number of L2 writes: \t\t" << lowerCache->writes << endl;
  cout << "j. Number of L2 write misses: \t\t" << lowerCache->writeMisses << endl;
  }
  }
  };
  o
  */
// Main Starts Here

  int main(int argc, char *argv[]){

    bool isCmdValid, isConfigSuccessful; 
    ulong blockSize, l1Size, l1Assoc, l2Size, l2Assoc;
    char *fname;
    FILE *traceFile;
    
    isCmdValid = readCmdInput(argv,&blockSize,&l1Size,&l1Assoc,&l2Size,&l2Assoc);

    // reading the trace file

    if(isCmdValid){
      fname = argv[8];
      traceFile = fopen(fname, "r");
      if(traceFile == 0) {
	cout << "\nThere is a problem reading the trace file." <<endl;
	isConfigSuccessful = false;
      }
      else {
	isConfigSuccessful = true;
      }
    }
    
    if(isConfigSuccessful) printCacheConfig(&blockSize,&l1Size,&l1Assoc,&l2Size,&l2Assoc,fname);

    Cache* L1 = new Cache(l1Size, l1Assoc, blockSize);
    Cache* L2;
  
    if(ISL2){
      L2 = new Cache(l2Size,l2Assoc,blockSize);
      L1->initL2(L2);
    }
    char instruction[20];
    int address_accessed = 0;

    /* Read the trace file */
    while(fgets(instruction,20,traceFile) != NULL){
      int count = 1;
      char* token = strtok(instruction, " ");
      char* method;
      ulong address;
      method = token;
      token = strtok(NULL," ");
      address = strtol(token,NULL,16);

      L1->getBlockAccess(address,method[0],true);
      if(ISL2){
	// Non inclusive
	if(INCLUSION_TYPE == "NON-INCLUSIVE") {
	  if (L1->isWriteBack())  L2->getBlockAccess(L1->getEvictedAddress(), 'w', true); 
	  if(L1->isMiss())  L2->getBlockAccess(address, 'r', true);
	}
	else if(INCLUSION_TYPE == "INCLUSIVE") {
	  if (L1->isWriteBack())  L2->getBlockAccess(L1->getEvictedAddress(), 'w', true); 
	  if (L2->isEvicted())  L1->invalidateBlock(L2->getEvictedAddress()); 
	  if(L1->isMiss()) {
	    L2->getBlockAccess(address, 'r', true);
	    if (L2->isEvicted())  L1->invalidateBlock(L2->getEvictedAddress());
	  }
	}
	else if(INCLUSION_TYPE == "EXCLUSIVE") {
	  if(L1->isHit()) L2->invalidateBlock(address);
	  if(L1->isEvicted()) {
	    L2->getBlockAccess(L1->getEvictedAddress(),'w',true);
	    if(!L1->isWriteBack()) L2->findCacheBlock(L1->getEvictedAddress())->setState("VALID"); 
	  }
	  if(L1->isMiss()){
	    L2->getBlockAccess(address,'r',false);
	    if(L2->isHit()){
	      if(L2->findCacheBlock(address)->isDirty())
		L1->findCacheBlock(address)->setState("DIRTY");
	      L2->invalidateBlock(address);
	    }
	  }
	
	}
	else{
	  cout << "Associativity Mismatch!!!" << endl;
	}
      } 
    }

    L1->displayOutput();
    return 1;
  }


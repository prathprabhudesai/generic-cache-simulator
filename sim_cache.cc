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

//Functions assisting Main 

void printCacheConfig(ulong blockSize, ulong l1Size, ulong l1Assoc, ulong l2Size, ulong l2Assoc,char *fname ){
  cout << "==== Simulator Configuration ====" << endl;
  cout << "BLOCKSIZE: \t\t" << blockSize << endl;
  cout << "L1_SIZE: \t\t" << l1Size << endl;
  cout << "L1_ASSOC: \t\t" << l1Assoc << endl;
  cout << "L2_SIZE: \t\t" << l2Size << endl;
  cout << "L1_ASSOC: \t\t" << l2Assoc << endl;
  cout << "REPLACEMENT POLICY: \t" << REPLACEMENT_POLICY << endl;
  cout << "INCLUSION PROPERTY: \t" << INCLUSION_TYPE << endl;
  cout << "trace_file: \t\t" << fname;
}

// Read Command Inputs

bool readCmdInput(int argc, char *argv[],ulong *blockSize,ulong *l1Size,ulong *l1Assoc, ulong *l2Size, ulong *l2Assoc, FILE ** traceFile){
  char * fname; 
  if(argc <= 8) {
    cout << "Not enough input parameters are provided" << endl;
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

  fname = argv[8]; 
  *traceFile = fopen(fname, "r"); 
  if(*traceFile == 0) {
    cout << "\nThere is a problem reading the trace file." <<endl;
    return false;
  }

  ISL2 = (*l2Size == 0) ? false : true;
  printCacheConfig(*blockSize,*l1Size,*l1Assoc,*l2Size,*l2Assoc,fname);
  return true;
}

// Output

void displayOutput(Cache * L1){
  cout << "\n===== Simulation Results =====" << endl;
  cout << "a. number of L1 reads: \t\t" << L1->getReads() << endl;
  cout << "b. number of L1 read misses: \t" << L1->getReadMisses() << endl;
  cout << "c. number of L1 writes: \t" << L1->getWrites() << endl;
  cout << "d. number of L1 write misses: \t" << L1->getWriteMisses() << endl;
  cout << "e. L1 miss rate: \t\t" << L1->getMissRate() << endl;
  cout << "f. number of L1 writebacks: \t" << L1->getWriteBacks() << endl; 
  Cache * L2 = L1->getLowerCache();
  if(L2) {
    cout << "g. number of L2 reads: \t\t" << L2->getReads() << endl;
    cout << "h. number of L2 read misses: \t" << L2->getReadMisses() << endl;
    cout << "i. number of L2 writes: \t" << L2->getWrites() << endl;
    cout << "j. number of L2 write misses: \t" << L2->getWriteMisses() << endl;
    cout << "k. L2 miss rate: \t\t" << L2->getMissRate() << endl;
    cout << "l. number of L2 writebacks: \t" << L2->getWriteBacks() << endl;
    cout << "m. total memory traffic: \t" << L2->getMemoryTraffic() << endl;
  } else {
    cout << "g. number of L2 reads: \t\t0" << endl;
    cout << "h. number of L2 read misses: \t0" << endl;
    cout << "i. number of L2 writes: \t0"<< endl;
    cout << "j. number of L2 write misses: \t0" << endl;
    cout << "k. L2 miss rate: \t\t0" << endl;
    cout << "l. number of L2 writebacks: \t0" << endl;
    cout << "m. total memory traffic: \t" << L1->getMemoryTraffic() << endl;
  }
}

// Access L1
void accessL1(Cache * L1, char instr, ulong address) {
  EXCLUSIVITY = true;
  L1->getBlockAccess(address,instr); 
}

// Non-Inlcusive Cache
void nonInclusiveCache(Cache * L1, Cache * L2, ulong address) {
  EXCLUSIVITY = true;
  if (L1->isWriteBack())  L2->getBlockAccess(L1->getEvictedAddress(), 'w'); 
  if(L1->isMiss())  L2->getBlockAccess(address, 'r'); 
}

// Inclusive Cache
void inclusiveCache(Cache * L1, Cache * L2, ulong address) {
  EXCLUSIVITY = true;
  if (L1->isWriteBack())  L2->getBlockAccess(L1->getEvictedAddress(), 'w'); 
  if (L2->isEvicted())  L1->invalidateBlock(L2->getEvictedAddress()); 
  if(L1->isMiss()) {
    L2->getBlockAccess(address, 'r');
    if (L2->isEvicted())  L1->invalidateBlock(L2->getEvictedAddress());
  }
}

// Exclusive Cache
void exclusiveCache(Cache * L1, Cache * L2, ulong address) {
  EXCLUSIVITY = true;
  if(L1->isHit()) L2->invalidateBlock(address);
  if(L1->isEvicted()) {
    L2->getBlockAccess(L1->getEvictedAddress(),'w');
    if(!L1->isWriteBack()) L2->findCacheBlock(L1->getEvictedAddress())->setState("VALID"); 
  }
  if(L1->isMiss()) {
    EXCLUSIVITY = false;
    L2->getBlockAccess(address,'r');
    EXCLUSIVITY = true;
    if(L2->isHit()){
      if(L2->findCacheBlock(address)->isDirty())  L1->findCacheBlock(address)->setState("DIRTY");
      L2->invalidateBlock(address);
    }
  } 
}

// Main Starts Here

int main(int argc, char *argv[]){

  bool isConfigSuccessful; 
  ulong blockSize, l1Size, l1Assoc, l2Size, l2Assoc, address;
  char *token, *method;
  FILE *traceFile;
  char instruction[20];
  
  isConfigSuccessful = readCmdInput(argc,argv,&blockSize,&l1Size,&l1Assoc,&l2Size,&l2Assoc,&traceFile);

  if(!isConfigSuccessful)  return 0;
  
  // initialize caches
  
  Cache* L1 = new Cache(l1Size, l1Assoc, blockSize);
  Cache* L2;

  if(ISL2){
    L2 = new Cache(l2Size,l2Assoc,blockSize);
    L1->initL2(L2);
  }

  // Read the trace file and simulate cache config

  while(fgets(instruction,20,traceFile) != NULL) {
    token = strtok(instruction, " "); 
    method = token;
    token = strtok(NULL," ");
    address = strtol(token,NULL,16);

    accessL1(L1, method[0], address);

    if(ISL2)
      switch(atoi(argv[7])){
      case 0: nonInclusiveCache(L1, L2, address); break;
      case 1: inclusiveCache(L1, L2, address); break;
      case 2: exclusiveCache(L1, L2, address); break; 
      }
  }
  
  displayOutput(L1);
  return 1;
}

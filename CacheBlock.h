
using namespace std;
typedef unsigned long ulong;

class CacheBlock {
   
 private:
  ulong assoc, seq, index, tag;
  string state;

 public:
  
  CacheBlock(ulong assoc) {
    this->assoc = assoc;
    this->seq = 0;
    this->index = 0;
    this->state = "INVALID";
  }

  bool isValid() { return (this->state != "INVALID"); }

  bool isDirty() { return (this->state == "DIRTY"); }

  void incSeq() { ++this->seq; }

  ulong getIndex() { return this->index; }

  void setIndex(ulong index) { this->index = index; }

  ulong getSeq() { return this->seq; }

  void setSeq(ulong seq) { this->seq = seq; }

  string getState() { return this->state; }

  void setState(string state) { this->state = state; }

  ulong getTag() { return this->tag; }

  void setTag(ulong tag) { this->tag = tag; }
  
};



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

  bool isValid() { return (state != "INVALID"); }

  bool isDirty() { return (state == "DIRTY"); }

  void incSeq() { ++seq; }

  ulong getIndex() { return index; }

  void setIndex(ulong index) { this->index = index; }

  ulong getSeq() { return seq; }

  void setSeq(ulong seq) { this->seq = seq; }

  string getState() { return state; }

  void setState(string state) { this->state = state; }

  ulong getTag() { return tag; }

  void setTag(ulong tag) { this->tag = tag; }
  
};


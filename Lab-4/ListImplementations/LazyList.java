import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class LazyList{
  private Node head;
  public LazyList(){
    // Add sentinels (head and tail)
    this.head  = new Node(Integer.MIN_VALUE);
    this.head.next = new Node(Integer.MAX_VALUE);
  }
  
  /* Check that prev and curr are still in list and adjacent */
  private boolean validate(Node pred, Node curr) {
    return  !pred.marked && !curr.marked && pred.next == curr;
  }
  /* Add an element.*/
public boolean add(int key) {
    while (true) {
      Node pred = this.head;
      Node curr = head.next;
      while (curr.key < key){
        pred = curr; curr = curr.next;
      }
      pred.lock();
      try {
          if (validate(pred, curr)) {
            if (curr.key == key) { // present
              return false;
            } else {               // not present
              Node Node = new Node(key);
              Node.next = curr;
              pred.next = Node;
              return true;
            }
          }
        }finally { // always unlock
        pred.unlock();
      }
    }
}
  /* Remove an element. */
public boolean remove(int key) {
    while (true) {
      Node pred = this.head;
      Node curr = head.next;
      while (curr.key < key) {
        pred = curr; curr = curr.next;
      }
      pred.lock();
      try {
        curr.lock();
        try {
          if (validate(pred, curr)) {
            if (curr.key != key) {    // not present 
              return false;
            } else {                  // present
              curr.marked = true;     // logically remove
              pred.next = curr.next;  // physically remove
              return true;
            }
          }
        } finally {                   // always unlock curr
          curr.unlock();
        }
      } finally {                     // always unlock pred
        pred.unlock();
      }
    }
}
public boolean contains(int key) {
    Node curr = this.head;
    while (curr.key < key)
      curr = curr.next;
    return curr.key == key && !curr.marked;
}
public void display()
{
	Node temp=head;
	while(temp.next!=null)
	{
		if(temp.marked==false){
			System.out.print("\t"+temp.key);
		}	
		temp=temp.next;
	}
}
  /* List Node */
  private class Node {
    int key;
    Node next;
    boolean marked;
    Lock lock;
    /* Constructor for usual Node*/
    Node(int key) {    
      this.key = key;
      this.next = null;
      this.marked = false;
      this.lock = new ReentrantLock();
    }
    /* Lock Node */
    void lock() {lock.lock();}
    /* Unlock Node */
    void unlock() {lock.unlock();}
  }
}


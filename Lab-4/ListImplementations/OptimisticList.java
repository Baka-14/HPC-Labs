/* OptimisticList.java */
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class OptimisticList{
  private Node head;
  public OptimisticList() {
    this.head  = new Node(Integer.MIN_VALUE);
    this.head.next = new Node(Integer.MAX_VALUE);
  }
  public boolean add(int item) {
    int key = item;
    while (true) {
      Node pred = this.head;
      Node curr = pred.next;
      while (curr.key <= key) {
        pred = curr; curr = curr.next;
      }
      pred.lock(); curr.lock();
      try {
        if (validate(pred, curr)) {
          if (curr.key == key) { // present
            return false;
          } else {               // not present
            Node node = new Node(item);
            node.next = curr;
            pred.next = node;
            return true;
          }
        }
      } finally {                // always unlock
        pred.unlock(); curr.unlock();
      }
    }
  }
  /* Remove an element.*/
  public boolean remove(int item) {
    int key = item;
    while (true) {
      Node pred = this.head;
      Node curr = pred.next;
      while (curr.key < key) {
        pred = curr; curr = curr.next;
      }
      pred.lock(); curr.lock();
      try {
        if (validate(pred, curr)) {
          if (curr.key == key) { // present in list
            pred.next = curr.next;
            return true;
          } else {               // not present in list
            return false;
          }
        }
      } finally {                // always unlock
        pred.unlock(); curr.unlock();
      }
    }
  }
  /*Test whether element is present*/
  public boolean contains(int item) {
    int key = item;
    while (true) {
      Node pred = this.head; // sentinel node;
      Node curr = pred.next;
      while (curr.key < key) {
        pred = curr; curr = curr.next;
      }
      try {
        pred.lock(); curr.lock();
        if (validate(pred, curr)) {
          return (curr.key == key);
        }
      } finally {                // always unlock
        pred.unlock(); curr.unlock();
      }
    }
  }
  private boolean validate(Node pred, Node curr) {
    Node node = head;
    while (node.key <= pred.key) {
      if (node == pred)
        return pred.next == curr;
      node = node.next;
    }
    return false;
  }
public void display()
{
	Node temp=head;
	while(temp.next!=null){
		System.out.print("\t"+temp.key);
		temp=temp.next;
	}
}
/**
* list entry
*/
private class Node {
    int key;
    Node next;
    Lock lock;
    Node(int item) {
      this.key = item;
      lock = new ReentrantLock();
      this.next=null;
    }
    void lock() {lock.lock();}
    void unlock() {lock.unlock();}
  }
}

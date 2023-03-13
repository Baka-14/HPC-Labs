/* Coarse List*/
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class CoarseList{
  private Node head;
  private Node tail;
  private Lock lock = new ReentrantLock();
  public CoarseList() {
    head  = new Node(Integer.MIN_VALUE);
    tail  = new Node(Integer.MAX_VALUE);
    head.next = this.tail;
  }  
  /*  Add an element.*/
  public boolean add(int item) {
    Node pred, curr;
    int key = item;
    try{
    lock.lock();
      pred = head;
      curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      if (key == curr.key) {
        return false;
      } else {
        Node node = new Node(item);
        node.next = curr;
        pred.next = node;
        return true;
      }
    } finally {
      lock.unlock();
    }
  }
  /* Remove an element.*/
  public boolean remove(int item) {
    Node pred, curr;
    int key = item;
    lock.lock();
    try {
      pred = this.head;
      curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      if (key == curr.key) {  // present
        pred.next = curr.next;
        return true;
      } else {
        return false;         // not present
      }
    } finally {               // always unlock
      lock.unlock();
    }
  }
  /*Test whether element is present.*/
  public boolean contains(int item) {
    Node pred, curr;
    int key = item;
    lock.lock();
    try {
      pred = head;
      curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      return (key == curr.key);
    } finally {               // always unlock
      lock.unlock();
    }
  }
  public void display()
  {
	Node temp=head;
	while(temp.next!=null){
		System.out.print("\t"+temp.key);
		temp=temp.next;
	}
  }
  private class Node {
    int key;
    Node next;
    Node(int item) {
      this.key = item;
      this.next=null;
    }
  }
}

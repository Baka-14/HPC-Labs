/* OptimisticList.java */
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class OptimisticList {
  private Node head;
  
  public OptimisticList() {
    this.head = new Node(Integer.MIN_VALUE, null, new Node(Integer.MAX_VALUE, null, null));
    this.head.next.prev = this.head;
  }
  
  public boolean add(int item) {
    int key = item;
    while (true) {
      Node pred = this.head;
      Node curr = pred.next;
      while (curr.key <= key) {
        pred = curr;
        curr = curr.next;
      }
      pred.lock();
      curr.lock();
      try {
        if (validate(pred, curr)) {
          if (curr.key == key) { // present
            return false;
          } else { // not present
            Node node = new Node(item, pred, curr);
            curr.prev = node;
            pred.next = node;
            return true;
          }
        }
      } finally { // always unlock
        pred.unlock();
        curr.unlock();
      }
    }
  }
  
  /* Remove an element. */
  public boolean remove(int item) {
    int key = item;
    while (true) {
      Node pred = this.head;
      Node curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      pred.lock();
      curr.lock();
      try {
        if (validate(pred, curr)) {
          if (curr.key == key) { // present in list
            curr.prev.next = curr.next;
            curr.next.prev = curr.prev;
            return true;
          } else { // not present in list
            return false;
          }
        }
      } finally { // always unlock
        pred.unlock();
        curr.unlock();
      }
    }
  }
  
  /* Test whether element is present */
  public boolean contains(int item) {
    int key = item;
    while (true) {
      Node pred = this.head; // sentinel node;
      Node curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      try {
        pred.lock();
        curr.lock();
        if (validate(pred, curr)) {
          return (curr.key == key);
        }
      } finally { // always unlock
        pred.unlock();
        curr.unlock();
      }
    }
  }
  
  private boolean validate(Node pred, Node curr) {
    return !pred.isDeleted() && !curr.isDeleted() && pred.next == curr && curr.prev == pred;
  }

  public void display() {
    Node temp = head;
    while (temp != null) {
      System.out.print("\t" + temp.key);
      temp = temp.next;
    }
  }

  /**
   * list entry
   */
  private class Node {
    int key;
    Node next;
    Node prev;
    boolean deleted;
    Lock lock;

    Node(int item, Node prev, Node next) {
      this.key = item;
      this.prev = prev;
      this.next = next;
      this.deleted = false;
      this.lock = new ReentrantLock();
    }

    void lock() {
      lock.lock();
    }

    void unlock() {
      lock.unlock();
    }

    boolean isDeleted() {
      return deleted;
    }

    void setDeleted(boolean deleted) {
      this.deleted = deleted;
    }
  }
}

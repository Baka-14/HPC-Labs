/*
 * LockFreeList.java
 */
import java.util.concurrent.atomic.AtomicMarkableReference;

/**
 * Lock-free List based on M. Michael's algorithm.
 * @author Maurice Herlihy
 */
public class LockFreeList {
  Node head;
  public LockFreeList() {
    this.head  = new Node(Integer.MIN_VALUE);
    Node tail = new Node(Integer.MAX_VALUE);
    while (!head.next.compareAndSet(null, tail, false, false));
  }
  /**
   * Add an element.
   * @return true iff element was not there already
   */
  public boolean add(int key) {
    boolean splice;
    while (true) {
      // find predecessor and curren entries
      Window window = find(head, key);
      Node pred = window.pred, curr = window.curr;
      // is the key present?
      if (curr.key == key) {
        return false;
      } else {
        // splice in new node
        Node node = new Node(key);
        node.next = new AtomicMarkableReference(curr, false);
        if (pred.next.compareAndSet(curr, node, false, false)) {
          return true;
        }
      }
    }
  }
  /**
   * Remove an element.
   */
  public boolean remove(int key) {
    boolean snip;
    while (true) {
      // find predecessor and curren entries
      Window window = find(head, key);
      Node pred = window.pred, curr = window.curr;
      // is the key present?
      if (curr.key != key) {
        return false;
      } else {
        // snip out matching node
        Node succ = curr.next.getReference();
        snip = curr.next.attemptMark(succ, true);
        if (!snip)
          continue;
        pred.next.compareAndSet(curr, succ, false, false);
        return true;
      }
    }
  }
  /**
   * Test whether element is present
   */
  public boolean contains(int key) {
    // find predecessor and curren entries
    Window window = find(head, key);
    Node pred = window.pred, curr = window.curr;
    return (curr.key == key);
  }
  /**
   * list node
   */
  private class Node {
    int key;
    AtomicMarkableReference<Node> next;
    Node(int key) { // sentinel constructor
      this.key = key;
      this.next = new AtomicMarkableReference<Node>(null, false);
    }
  }
  
  /**
   * Pair of adjacent list entries.
   */
  class Window {
    public Node pred;
    public Node curr;
    Window(Node pred, Node curr) {
      this.pred = pred; this.curr = curr;
    }
  }
  
  /**
   * If element is present, returns node and predecessor. If absent, returns
   * node with least larger key.
   * @param head start of list
   * @param key key to search for
   * @return If element is present, returns node and predecessor. If absent, returns
   * node with least larger key.
   */
  public Window find(Node head, int key) {
    Node pred = null, curr = null, succ = null;
    boolean[] marked = {false}; // is curr marked?
    boolean snip;
    retry: while (true) {
      pred = head;
      curr = pred.next.getReference();
      while (true) {
        succ = curr.next.get(marked); 
        while (marked[0]) {           // replace curr if marked
          snip = pred.next.compareAndSet(curr, succ, false, false);
          if (!snip) continue retry;
          curr = pred.next.getReference();
          succ = curr.next.get(marked);
        }
        if (curr.key >= key)
          return new Window(pred, curr);
        pred = curr;
        curr = succ;
      }
    }
  }
}

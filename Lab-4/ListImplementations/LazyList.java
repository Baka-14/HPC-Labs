import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
public class LazyList
{
  private Node head;
  private Node tail;
  public LazyList()
  {
    // Add sentinels (head and tail)
    this.head  = new Node(Integer.MIN_VALUE);
    this.tail = new Node(Integer.MAX_VALUE);
    this.head.next = this.tail;
    this.tail.prev = this.head;
  }
  
  /* Check that prev and curr are still in list and adjacent */
  private boolean validate(Node pred, Node curr) 
  {
    return  !pred.marked && !curr.marked && pred.next == curr && curr.prev == pred;
  }
  /* Add an element.*/

  public boolean add(int key) {
    while (true) {
      Node pred = this.head;
      Node curr = head.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      pred.lock();
      try {
        curr.lock();
        try {
          if (validate(pred, curr)) {
            if (curr.key == key) { // present
              return false;
            } else { // not present
              Node node = new Node(key);
              node.prev = pred; // Set prev pointer
              node.next = curr;
              curr.prev = node; // Set prev pointer
              pred.next = node;
              return true;
            }
          }
        } finally { // always unlock curr
          curr.unlock();
        }
      } finally { // always unlock pred
        pred.unlock();
      }
    }
  }

  /* Remove an element. */
public boolean remove(int key) 
{
    while (true) 
    {
      Node pred = this.head;
      Node curr = head.next;
      while (curr.key < key) 
      {
        pred = curr; curr = curr.next;
      }
      pred.lock();
      try 
      {
        curr.lock();
        try 
        {
          if (validate(pred, curr)) 
          {
            if (curr.key != key) 
            {    // not present 
              return false;
            } else 
            {                  // present
              curr.marked = true;     // logically remove
              curr.next.prev = pred;
              pred.next = curr.next;  // physically remove
              return true;
            }
          }
        } finally 
        {                   // always unlock curr
          curr.unlock();
        }
      } finally 
      {                     // always unlock pred
        pred.unlock();
      }
    }
}
public boolean contains(int key) 
{
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
		if(temp.marked==false)
    {
			System.out.print("\t"+temp.key);
		}	
		temp=temp.next;
	}
}
  /* List Node */
  private class Node 
  {
    int key;
    Node next;
    Node prev;
    boolean marked;
    Lock lock;
    /* Constructor for usual Node*/
    Node(int key) 
    {    
      this.key = key;
      this.next = null;
      this.prev = null;
      this.marked = false;
      this.lock = new ReentrantLock();
    }
    /* Lock Node */
    void lock() {lock.lock();}
    /* Unlock Node */
    void unlock() {lock.unlock();}
  }
}


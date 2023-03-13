/* Seq. List*/
public class SeqList{
  private Node head;//First Node
  private Node tail;//Last Node
  public SeqList() {
    head  = new Node(Integer.MIN_VALUE);
    tail  = new Node(Integer.MAX_VALUE);
    head.next = this.tail;
  }  
  /*  Add an element.*/
  public boolean add(int item) {
    Node pred, curr;
    int key = item;
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
  }
  /* Remove an element.*/
  public boolean remove(int item) {
    Node pred, curr;
    int key = item;
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
  }
  /*Test whether element is present.*/
  public boolean contains(int item) {
    Node pred, curr;
    int key = item;
      pred = head;
      curr = pred.next;
      while (curr.key < key) {
        pred = curr;
        curr = curr.next;
      }
      return (key == curr.key);
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

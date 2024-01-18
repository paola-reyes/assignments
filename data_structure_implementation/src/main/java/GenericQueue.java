/*
 Paola Reyes
 CS 342 Fall'23
 10-2-23
 Prof. Hallenbeck
  
    Project 1: Generic List

    This class is a custom implemenation of a queue class.
    It takes methods from the GenericList class. It has its
    own add() and delete() that are enqueue() dequeue(). It 
    uses the GLLIterator and ReverseGLLIterator.
*/
import java.util.Iterator;

public class GenericQueue<T> extends GenericList<T> {
    private Node<T> tail;

    // Constructor
    GenericQueue(T data) {    
        setHead(data);
        tail = getHead();    // Make this node the tail also
        setLength(1);
    }

    GenericQueue(T data, int code) {
        setHead(data, code);
        tail = getHead();
        setLength(1);
    }

    // Append value to our queue
    public void add(T data) {
        // If empty list, set head with our data
        if (getLength() == 0) {
            setHead(data);
            tail = getHead();    // Tail and head are the same node
        }
        else { // Append to the end of our list
            Node<T> current = getHead();
            
            while (current.next != null) {  // Iterate to the last node
                current = current.next;
            }
            
            Node<T> newNode = new Node<T>(data);
            current.next = newNode; // Make current point to newNode
            tail = current.next;    // Make this node the tail
        }
        
        setLength(getLength() + 1); // Update list size
    }

    // Append value to our queue
    public void add(T data, int code) {
        // If empty list, set head with our data
        if (getLength() == 0) {
            setHead(data, code);
            tail = getHead();    // Tail and head are the same node
        }
        else { // Append to the end of our list
            Node<T> current = getHead();
            
            while (current.next != null) {  // Iterate to the last node
                current = current.next;
            }
            
            Node<T> newNode = new Node<T>(data, code);
            current.next = newNode; // Make current point to newNode
            tail = current.next;    // Make this node the tail
        }
        
        setLength(getLength() + 1); // Update list size
    }

    // Return the head node's value and remove it from the list
    public T delete() {
        // Return null for an empty list
        if (getLength() == 0) {
            return null;
        }
        else { // Replace head with the value it points to
            T val = getHead().data; 
            setHead(getHead().next);    // Update head
            setLength(getLength() - 1); // Update list size

            return val;
        }
    }
 
    public void enqueue(T data) {   // Add element
        add(data);
    }

    public T dequeue() {    // Remove
        return delete();
    }

    public Iterator<T> iterator() {
        return new GLLIterator<T>(this);
    }
}

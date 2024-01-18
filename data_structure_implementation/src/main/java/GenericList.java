/*
 Paola Reyes
 CS 342 Fall'23
 10-2-23
 Prof. Hallenbeck
  
    Project 1: Generic List

    This program is a custom implementation of a linked list class. 
    It uses Iterable<T> and accepts a generic <T> as a data type.
    It also includes an iterator GLLIterator/Reverse, to iterate through 
    the linked list forwards or in reverse. This class is abstract
    for use in the GenericQueue class's add() and delete() 
 */

import java.util.ArrayList;
import java.util.Iterator;

public abstract class GenericList<T> implements Iterable<T> {
    private Node<T> head;
    private int length;

    // Subclass for our Node object
    public static class Node<T> {
        public T data;
        public int code;
        Node<T> next;

        // Constructors
        Node(T d, int c) {  
            data = d;
            code = c;
            next = null;    // Points to nothing
        }

        Node(T d) {      
            data = d;
            code = -1;
            next = null;    // Points to nothing
        }

        Node() {
            data = null;
            code = -1;
            next = null;
        }
    }   
    
    public abstract void add(T data);   // Add a value to the end of the list
    public abstract T delete();         // Delete a Node from the list

    // Print the list values
    public void print() {
        Node<T> current = head;

        // Iterate until we reach the last node
        while (current != null) {
            System.out.println(current.data);
            current = current.next;
        }
    }

    // Copy the values of this list into an ArrayList 
    public ArrayList<T> dumpList() {
        if (length == 0) {  // List is empty
            return null;
        }
        else {
            ArrayList<T> result = new ArrayList<T>();

            for (int i = 0; i < length; i++) {
                result.add(get(i));    // Use get()
            }

            return result;
        }
    }

    // Get the value at the provided index
    public T get(int index) {
        if (length == 0) {  // List is empty
            return null;
        }
        else {
            int counter = 0;

            Node<T> current = head; // For iterating through list

            // Iterate through the linked list index # times
            while (counter != index) {
                current = head.next;
                counter++;
            }

            return current.data;
        }
    }

    // Returns the Node code located at the index
    public int getCode(int index) {
        if (length == 0) {  // List is empty
            return -1;
        }
        else {
            int counter = 0;
            Node<T> current = head; // For iterating through list

            // Iterate through the linked list index # times
            while (counter != index) {
                current = head.next;
                counter++;
            }

            return current.code;
        }
    }

    // Set the provided element at the given index. Return the Node's previous data value
    public T set(int index, T element) {
        if (length == 0) {  // List is empty
            return null;
        }
        else {
            int counter = 0;
            Node<T> current = head; // For iterating through list

            // Iterate through the linked list index # times
            while (counter != index) {
                current = head.next;
                counter++;
            }

            T val = current.data;       // Get the old value
            current.data = element;     // Updata Node value

            return val; 
        }
    }

    // Return the length of the array
    public int getLength() {
        return length;
    }

    // Update the list length
    public void setLength(int n) {
        length = n;
    }

    // Return the first Node of the list
    public Node<T> getHead() {
        return head;
    }

    // Create a new head of the list
    public void setHead(T data, int code) {
        // Create a new node for an empty list
        if (length == 0) {
            Node<T> newHead = new Node<T>(data, code);
            head = newHead;
        }
        else {  // Update currend head
            head.data = data;
            head.code = code;
        }
    }

    // Create a new head of the list given just the data
    public void setHead(T data) {
       // Create a new node for an empty list
        if (length == 0) {
            Node<T> newHead = new Node<T>(data);
            head = newHead;
        }
        else {  // Update currend head
            head.data = data;
        }
    }

    // Set head to the given node
    public void setHead(Node<T> newHead) {
        head = newHead;
    }

    public Iterator<T> iterator() {
        return new GLLIterator<T>(this);
    }

    public Iterator<T> descendingIterator() {
        return new ReverseGLLIterator<T>(this);
    }
}
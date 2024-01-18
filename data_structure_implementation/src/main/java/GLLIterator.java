import java.util.Iterator;

// Iterate through our linked list
public class GLLIterator<E> implements Iterator<E> {  
    public GenericList.Node<E> node;    // Our current node in iteration

    // Pass the head of the linked list
    GLLIterator(GenericList<E> list) {
        node = list.getHead();
    }

    // Check if the our node points to a node 
    public boolean hasNext() {      
        return node != null;  
    }

    // Return the current element's value and move to the next element 
    public E next() {   
        E val = node.data;
        node = node.next;
        
        return val;
    }
}
import java.util.Iterator;

// Iterate through our linked list in reverse
public class ReverseGLLIterator<E> implements Iterator<E> {  
    public GenericList<E> list;         // Store the linked list from GenericList class
    public GenericList.Node<E> node;    // Our current node in iteration

    // Pass the head of the linked list
    ReverseGLLIterator(GenericList<E> list) {
        this.list = list;
    }

    // Check if the there is a value before our curent. 
    public boolean hasNext() {
        return node != list.getHead() && node != null;  
    }

    // Return the current element's value and move to the next element 
    public E next() {
        E val = node.data;
        GenericList.Node<E> current = list.getHead();

        // Iterate until we find the value before our node
        while (current.next != node) {
            current = node.next;
        }

        node = current; // Set node to the value before it since we're decrementing

        return val;
    }
}

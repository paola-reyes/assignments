import java.util.Iterator;
import java.util.ArrayList;

// Iterate through our hash map
public class HMIterator<E> implements Iterator<E> {
    public ArrayList<GenericQueue<E>> list;
    public GenericList.Node<E> node;    // Our current node in iteration
    public int index;

    // Pass the head of the linked list
    HMIterator(MyHashMap<E> map) {
        this.list = map.list;

        // Look for first node
        for (int i = 0; i < list.size(); i++) {
            if (list.get(i).getLength() > 0) {
                node = list.get(i).getHead();   // Set node to first node
                break;
            }
        }
    }

    // Check if the our node points to a node 
    public boolean hasNext() {
        return node != null;
    }

    // Return the current element's value and move to the next element 
    public E next() {      
        E val = node.data;

        // Reached the end of the queue
        if (node.next == null) {
            if (index + 1 != list.size()) {
                node = list.get(++index).getHead();   // Get the next queue head
            }
            else {
                node = null;    // Reached the end of map
            }
        }
        else {
            node = node.next;   // Get next queue item
        }

        return val;
    }
}

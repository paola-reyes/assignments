/*
 Paola Reyes
 CS 342 Fall'23
 10-2-23
 Prof. Hallenbeck
  
    Project 1: Generic List

    This class is a custom implemenation of a hash map class.
    It is an ArrayList of GenericQueue<T>. The queues use functions
    from GenericList and GenericQueue. It takes in a string key
    and stores our value in an index and queue node. It also 
    implements Iterable<T> and uses HMIterator to iterate through
    the hash map. 
*/
import java.util.ArrayList;
import java.util.Iterator;

public class MyHashMap<T> implements Iterable<T> {
    public ArrayList<GenericQueue<T>> list;

    MyHashMap(String key, T value) {
        list = new ArrayList<GenericQueue<T>>(10);
        put(key, value);
    }

    // Add a value to the list
    public void put(String key, T value) {
        int code = key.hashCode()&9;

        // Append value to queue if the key already exists
        if (contains(key)) {
            for (int i = 0; i < list.size(); i++) {  // Iterate through list
                for (int j = 0; j < list.get(i).getLength(); j++) {  // Iterate through queue
                    if (list.get(i).getCode(j) == code) {    
                        list.get(i).add(value, code);
                    }
                }
            }
        }
        else {  // Add a new queue to list
            GenericQueue<T> queue = new GenericQueue<T>(value, code);
            list.add(queue);
        }
    }

    // Check if any queue in list contains the key's hash code
    public boolean contains(String key) {
        int code = key.hashCode()&9;

        for (int i = 0; i < list.size(); i++) {  // Iterate through list
            for (int j = 0; j < list.get(i).getLength(); j++) {  // Iterate through queue
                if (list.get(i).getCode(j) == code) {
                    return true;
                }
            }
        }

        return false;   // Not found
    }

    // Return the value associated with the given key
    public T get(String key) {
        int code = key.hashCode()&9;

        for (int i = 0; i < list.size(); i++) { // Iterate through list
            for (int j = 0; j < list.get(i).getLength(); j++) { // Iterate through queue
                if (list.get(i).getCode(j) == code) {
                    return list.get(i).get(j);  // Return data
                }
            }
        }

        return null;   // Not found so return null
    }

    // Return the number of Nodes list's queues
    public int size() {
        int count = 0;
        
        for (int i = 0; i < list.size(); i++) {  // Iterate through list
            count += list.get(i).getLength();
        }

        return count;
    }

    // Check if there are any Nodes in list's queues
    public boolean isEmpty() {
        for (int i = 0; i < list.size(); i++) {  // Iterate through list
            if (list.get(i).getLength() > 0) {
                return false;   // Node found
            }
        }

        return true;
    }

    // Update the value at the given key
    public T replace(String key, T value) {
        for (int i = 0; i < list.size(); i++) {  // Iterate through list
            for (int j = 0; j < list.get(i).getLength(); j++) {  // Iterate through queue
                if (list.get(i).getCode(j) == key.hashCode()) {  // Stop when we find the key
                    T val = list.get(i).get(j);
                    list.get(i).set(j, value);

                    return val;
                }
            }
        }

        return null;    // Key not found
    }

    // Print all the queues in list
    public void print() {
        for (int i = 0; i < list.size(); i++) {
            list.get(i).print();
        }
    }

    // Return an iterator to an element
    public Iterator<T> iterator() {
        return new HMIterator<T>(this);
    }
} 
import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;
import java.util.Iterator;

public class GQTest {
    // Check constructor initalized queue well
    @Test
    void constructorOneParam() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        assertEquals(5, q.getHead().data, "constructor sets wrong value");
    }

    // Check constructor initalized queue well
    @Test 
    void constructorTwoParam() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5, 70);
        assertEquals(5, q.getHead().data, "constructor sets wrong value");
        assertEquals(70, q.getHead().code, "constructor sets wrong code");
    }

    // Check add() sends values to the queue
    @Test
    void addOneParamTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.add(3);
        ArrayList<Integer> actual = q.dumpList();

        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(5);
        expected.add(4);
        expected.add(3);

        assertEquals(3, q.getLength(), "add() wrong size");
        assertEquals(true, actual.equals(expected), "add() wrong elements");
    }

    // Check add() sends values to the queue
    @Test
    void addTwoParamTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5, 70);
        q.add(4, 69);
        ArrayList<Integer> actual = q.dumpList();

        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(5);
        expected.add(4);

        assertEquals(2, q.getLength(), "add() wrong size");
        assertEquals(true, actual.equals(expected), "add() wrong elements");
        assertEquals(70, q.getCode(0), "add() wrong code");
        assertEquals(69, q.getCode(1), "add() wrong code");
    }

    // Check delete() removes the head value
    @Test
    void deleteTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.add(3);
        q.delete();

        assertEquals(2, q.getLength(), "delete() wrong size");
        assertEquals(4, q.getHead().data, "delete() wrong first element");
    }

    // Check enqueue() sents values to queue
    @Test
    void enqueueTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.enqueue(4);

        ArrayList<Integer> actual = q.dumpList();
        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(5);
        expected.add(4);

        assertEquals(2, q.getLength(), "enqueue wrong size");
        assertEquals(true, expected.equals(actual), "enqueue wrong elements");
    }

    // Check dequeue() removes the head value
    @Test
    void dequeueTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.enqueue(4);
        q.enqueue(3);
        q.dequeue();

        assertEquals(2, q.getLength(), "delete() wrong size");
        assertEquals(4, q.getHead().data, "delete() wrong first element");
    }

    // Check the for-each iterator works
    @Test
    void forEachTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.add(3);

        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(5);
        expected.add(4);
        expected.add(3);
        ArrayList<Integer> actual = new ArrayList<Integer>();

        for (Integer i : q) {
            actual.add(i);
        }

        assertEquals(true, expected.equals(actual), "for each wrong results");
    }

    // Check dumpList() sends the right values
    @Test
    void dumpListTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);

        ArrayList<Integer> actual = q.dumpList();
        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(5);
        expected.add(4);

        assertEquals(true, actual.equals(expected), "dump list wrong elements");
    }

    // Check get() accesses the index's data
    @Test
    void getTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);

        assertEquals(5, q.get(0), "get() wrong element");
        assertEquals(4, q.get(1), "get() wrong element");
    }

    // Check set() updates the index's value
    @Test
    void setTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.set(1, 13);

        assertEquals(13, q.get(1), "set() wrong element");
    }

    // Check getLength returns the correct value
    @Test
    void getLengthTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.add(3);

        assertEquals(3, q.getLength(), "getLength wrong size");
    }

    // Check setLength() updates the length
    @Test
    void setLengthTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.setLength(20);

        assertEquals(20, q.getLength(), "getLength wrong size");
    }

    // Check setHead() changes the head value
    @Test
    void setHeadTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.setHead(20);

        assertEquals(20, q.getHead().data, "setHead() wrong value");
    }

    // Check getHead() accesses the head value
    @Test 
    void getHeadTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        GenericList.Node<Integer> n = q.getHead();

        assertEquals(5, n.data, "getHead() wrong value");
    }

    // Check reverseIterator works
    @Test
    void reverseIteratorTest() {
        GenericQueue<Integer> q = new GenericQueue<Integer>(5);
        q.add(4);
        q.add(3);

        ArrayList<Integer> actual = new ArrayList<>();
        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(3);
        expected.add(4);
        expected.add(5);

        Iterator<Integer> iter = q.descendingIterator();

        while (iter.hasNext()) {
            actual.add(iter.next());
        }
    }
}
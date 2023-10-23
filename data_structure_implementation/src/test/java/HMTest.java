import static org.junit.jupiter.api.Assertions.*;
import org.junit.jupiter.api.Test;
import java.util.ArrayList;


public class HMTest {
    // Check constructor initializes hashmap with correct value
    @Test
    void constructorTest1() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);

        assertEquals(10, m.get("peluchina"), "constructor wrong value");
        assertEquals(1, m.size(), "constructor wrong size");
    }

    // Check constructor initializes hashmap with correct value
    @Test
    void constructorTest2() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("thiago", 8);

        assertEquals(8, m.get("thiago"), "constructor wrong value");
        assertEquals(1, m.size(), "constructor wrong size");
    }

    // Check put() adds the correct value to the hashmap
    @Test
    void putTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);
        m.put("thiago", 8);
        m.put("betty", 4);

        assertEquals(3, m.size(), "put() wrong size");
        assertEquals(10, m.get("peluchina"), "put() wrong value");
        assertEquals(8, m.get("thiago"), "put() wrong value");
        assertEquals(4, m.get("betty"), "put() wrong value");
    }

    // Check contain() returns the correct boolean
    void containsTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);
        m.put("thiago", 8);
        m.put("betty", 4);

        assertEquals(true, m.contains("betty"), "contains() should be true");
        assertEquals(false, m.contains("coco"), "contains() should be false");
    }

    // Check size() returns the correct value
    @Test
    void sizeTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);
        m.put("thiago", 8);
        m.put("betty", 4);

        assertEquals(3, m.size(), "size() wrong value");
    }

    // Check isEmpty() returns correct boolean
    @Test
    void isEmptyTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);

        assertEquals(false, m.isEmpty(), "isEmpty() should be false");
    }

    // Check replace() updates the value at key
    @Test
    void replaceTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);
        m.put("thiago", 8);
        m.put("betty", 4);
        m.replace("thiago", 7);

        assertEquals(7, m.get("thiago"), "replace() wrong value");
    }

    // Check the for-each loop works
    @Test
    void forEachTest() {
        MyHashMap<Integer> m = new MyHashMap<Integer>("peluchina", 10);
        m.put("thiago", 8);
        m.put("betty", 4);

        ArrayList<Integer> expected = new ArrayList<Integer>();
        expected.add(10);
        expected.add(8);
        expected.add(4);

        ArrayList<Integer> actual = new ArrayList<Integer>();
        for (Integer i : m) {
            actual.add(i);
        }

        assertEquals(true, actual.equals(expected), "for-each has wrong values");
    }
}

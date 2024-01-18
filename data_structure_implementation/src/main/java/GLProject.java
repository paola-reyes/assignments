public class GLProject {
	public static void main(String[] args) {
		MyHashMap<Integer> map = new MyHashMap<Integer>("thiago", 8);
		map.put("betty", 4);
		map.put("pelooch", 10);
		
		for (Integer i : map) {
			System.out.println(i);
		}
	}
}
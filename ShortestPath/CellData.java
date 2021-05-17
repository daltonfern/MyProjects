  
/**
 * @class Class CELLDATA implements all the getter and setter methods for a new
 *        CellData object
 */
public class CellData<T> {
	private T id;
	private int value;

	public CellData(T theId, int theValue) {
		id = theId;
		value = theValue;
	}

	public int getValue() {
		return value;
	}

	public T getId() {
		return id;
	}

	public void setValue(int newValue) {
		value = newValue;
	}

	public void setId(T newId) {
		id = newId;
	}
}

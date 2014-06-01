/**
 * 
 */
package circuit;


/**
 * @author bhess
 * 
 */
public class CircuitComponent {

	public CircuitElement[] inGates;

	public CircuitElement[] outGates;

	public CircuitElement[] allElements;

	public String toString() {
		return "All elements: " + allElements.length + "\nInput-Gates: "
				+ inGates.length + "\nOutput-Gates: " + outGates.length;
	}

}

/**
 * 
 */
package factories;

import gates.unary.Dummy;
import circuit.CircuitComponent;
import circuit.CircuitElement;

/**
 * @author bhess
 *
 */
public class DummyFactory implements ComponentFactory {

	/* (non-Javadoc)
	 * @see factories.ComponentFactory#createComponent(int, int)
	 */
	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		CircuitComponent c = new CircuitComponent();
		c.allElements = new CircuitElement[size];
		for (int i = 0; i < c.allElements.length; ++i) {
			c.allElements[i] = new Dummy();
		}
		c.inGates = c.allElements;
		c.outGates = c.allElements;
		return c;
	}

	/* (non-Javadoc)
	 * @see factories.ComponentFactory#getInputLengths()
	 */
	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

}

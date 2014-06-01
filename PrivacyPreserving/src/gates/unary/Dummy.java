/**
 * 
 */
package gates.unary;

import circuit.CircuitElement;

/**
 * @author bhess
 *
 */
public class Dummy extends CircuitElement {

	/**
	 * @param inWireCnt
	 */
	public Dummy() {
		super(1);
	}

	/* (non-Javadoc)
	 * @see circuit.CircuitElement#evaluate(boolean[])
	 */
	@Override
	public boolean evaluate(boolean[] in) {
		return in[0];
	}

	/* (non-Javadoc)
	 * @see circuit.CircuitElement#getArity()
	 */
	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return 1;
	}

}

/**
 * 
 */
package gates.unary;

import circuit.CircuitElement;

/**
 * @author bhess
 *
 */
public class ResultElement extends CircuitElement {

	/**
	 * @param inWireCnt
	 */
	public ResultElement(boolean[] resultArray, int positionInArray) {
		super(1);
		this.resultArray = resultArray;
		this.positionInArray = positionInArray;
	}
	
	private boolean[] resultArray;
	private int positionInArray;

	/* (non-Javadoc)
	 * @see circuit.CircuitElement#evaluate(boolean[])
	 */
	@Override
	public boolean evaluate(boolean[] in) {
		resultArray[positionInArray] = in[0];
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

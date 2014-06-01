package gates.trinary;

import circuit.CircuitElement;

public class FullAdderCout extends CircuitElement {

	/**
	 * @param inWireCnt
	 * @param outElementsCnt
	 */
	public FullAdderCout(int outElementsCnt) {
		super(3, outElementsCnt);
		// TODO Auto-generated constructor stub
	}

	/**
	 * Inputs: in[0]: x
	 *         in[1]: y
	 *         in[2]: c_in
	 *         
	 * Output: (y and c_in) or (x and c_in) or (x and y)
	 * 
	 * Can be used for:
	 *  - the c_out of a Full Adder 
	 */
	@Override
	public boolean evaluate(boolean[] in) {
		return (in[1] & in[2]) | (in[0] & in[2]) | (in[0] & in[1]);
	}

	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return 3;
	}

}

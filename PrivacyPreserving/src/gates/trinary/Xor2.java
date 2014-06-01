package gates.trinary;

import circuit.CircuitElement;

public class Xor2 extends CircuitElement {

	/**
	 * @param inWireCnt
	 * @param outElementsCnt
	 */
	public Xor2(int outElementsCnt) {
		super(3, outElementsCnt);
		// TODO Auto-generated constructor stub
	}

	/**
	 * Inputs: in[0]: x
	 *         in[1]: y
	 *         in[2]: c_in
	 *         
	 * Output: (x xor y) xor c_in
	 */
	@Override
	public boolean evaluate(boolean[] in) {
		return (in[0] != in[1]) != in[2];
	}

	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return 3;
	}

}

package gates.binary;

import circuit.CircuitElement;

public class Xor extends CircuitElement {

	/**
	 * @param gate
	 * @param inWireCnt
	 * @param outElementsCnt
	 */
	public Xor(int outElementsCnt) {
		super(2, outElementsCnt);
	}
	
	public Xor() {
		super(2);
	}

	@Override
	public boolean evaluate(boolean[] in) {
		return in[0] != in[1]; 
	}

	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return 2;
	}

}

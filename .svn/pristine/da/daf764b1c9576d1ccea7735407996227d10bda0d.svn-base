package gates.nary;

import circuit.CircuitElement;

public class Equality extends CircuitElement {

	public Equality(int equalTo, int inWireCnt, int outElementsCnt) {
		super(inWireCnt, outElementsCnt);
		int bitLength = (int) Math.ceil(Math.log(equalTo) / Math.log(2));
		compare = new boolean[bitLength];
		for (int i = 0; i < bitLength; i++) {
			equalTo >>= i;
			compare[i] = (equalTo & 0x1) == 0x1;
		}
	}
	
	private boolean[] compare;
	
	@Override
	public boolean evaluate(boolean[] in) {
		boolean res = true;
		for (int i = 0; i < compare.length && res; ++i) {
			res &= compare[i];
		}
		return res;
	}

	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return compare.length;
	}

}

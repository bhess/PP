package gates.nary;

import circuit.CircuitElement;

public class OrN extends CircuitElement {
	
	public OrN(int inWireCnt) {
		super(inWireCnt);
		this.arity = inWireCnt;
	}

	public OrN(int inWireCnt, int outElementsCnt) {
		super(inWireCnt, outElementsCnt);
		this.arity = inWireCnt;
	}
	
	private int arity;

	@Override
	protected boolean evaluate(boolean[] in) {
		boolean res = false;
		for (int i = 0; i < in.length && !res; ++i) {
			res |= in[i];
		}
		return res;
	}

	@Override
	protected int getArity() {
		return arity;
	}

}

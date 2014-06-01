package gates.nary;

import circuit.CircuitElement;

public class EqualityTwo extends CircuitElement {

	public EqualityTwo(int arity, int outElementsCnt) {
		super(arity, outElementsCnt);
		this.arity = arity;
	}
	
	private int arity;
	
	@Override
	public boolean evaluate(boolean[] in) {
		int half = in.length / 2;
		boolean res = true;
		for (int i = 0; i < half && res; ++i) {
			res &= (in[i] == in[i+half]);
		}
		return res;
	}

	@Override
	public int getArity() {
		return arity;
	}

}

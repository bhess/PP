package gates.trinary;

import circuit.CircuitElement;

public class AndTri extends CircuitElement {
	
	public AndTri(int outElementsCnt) {
		super(3, outElementsCnt);
	}
	
	@Override
	public boolean evaluate(boolean[] in) {
		return in[0] && in[1] && in[2];
	}

	@Override
	public int getArity() {
		// TODO Auto-generated method stub
		return 3;
	}
}

package gates.unary;

import circuit.CircuitElement;

public class Terminator extends CircuitElement {

	public Terminator() {
		super(1);
	}

	@Override
	protected boolean evaluate(boolean[] in) {
		// TODO Auto-generated method stub
		return in[0];
	}

	@Override
	protected int getArity() {
		// TODO Auto-generated method stub
		return 1;
	}
	
	public boolean allSignalsSet() {
		return false;
	}

}

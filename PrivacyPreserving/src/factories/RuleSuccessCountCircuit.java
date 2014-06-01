package factories;

import circuit.CircuitComponent;

public class RuleSuccessCountCircuit implements ComponentFactory {

	public CircuitComponent createComponent(int startWire, int bits, int events) {
		CircuitComponent rcarray = new RuleCheckArrayCircuit().createComponent(startWire, bits, events);
		CircuitComponent oba = new OneBitAdderFactory().createComponent(startWire, rcarray.outGates.length);
		for (int i = 0; i < rcarray.outGates.length; ++i) {
			rcarray.outGates[i].setOutElementsCnt(1);
			rcarray.outGates[i].addOutElement(oba.inGates[i]);
			rcarray.outGates[i].registerAtOutElements();
		}
		rcarray.outGates = oba.outGates;
		
		return rcarray;
	}
	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

}

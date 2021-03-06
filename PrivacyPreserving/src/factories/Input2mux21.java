package factories;

import gates.binary.And;
import gates.binary.Or;
import gates.unary.Dummy;
import gates.unary.Not;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class Input2mux21 implements ComponentFactory {

	private static int INWIRES = 5, OUTWIRES = 2, MIDDLEWIRES = 1;
	
	/**
	 * Input: s|a11|a12|b11|b12
	 * Output: s=1 -> a11|a12, s=1 -> b11|b12
	 */
	@Override
	public CircuitComponent createComponent(int startWire, int size) {

		CircuitComponent cc = new CircuitComponent();
		cc.inGates = new CircuitElement[INWIRES];
		cc.outGates = new CircuitElement[OUTWIRES];
		cc.inGates[0] = new Dummy();
		cc.inGates[1] = new And(1);
		cc.inGates[2] = new And(1);
		cc.inGates[3] = new And(1);
		cc.inGates[4] = new And(1);
		
		cc.allElements = new CircuitElement[MIDDLEWIRES];
		cc.allElements[0] = new Not(2);
		
		cc.outGates = new CircuitElement[OUTWIRES];
		cc.outGates[0] = new Or();
		cc.outGates[1] = new Or();
		
		cc.inGates[0].setOutElementsCnt(3);
		cc.inGates[0].addOutElement(cc.inGates[1]);
		cc.inGates[0].addOutElement(cc.inGates[2]);
		cc.inGates[0].addOutElement(cc.allElements[0]);
		cc.inGates[0].registerAtOutElements();
		
		cc.inGates[1].addOutElement(cc.outGates[0]);
		cc.inGates[1].registerAtOutElements();
		
		cc.inGates[2].addOutElement(cc.outGates[1]);
		cc.inGates[2].registerAtOutElements();
		
		cc.inGates[3].addOutElement(cc.outGates[0]);
		cc.inGates[3].registerAtOutElements();
		
		cc.inGates[4].addOutElement(cc.outGates[1]);
		cc.inGates[4].registerAtOutElements();
		
		cc.allElements[0].addOutElement(cc.inGates[3]);
		cc.allElements[0].addOutElement(cc.inGates[4]);
		
		return cc;
	}

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

}

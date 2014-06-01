package factories;

import gates.unary.Dummy;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class RuleCheckArrayCircuit implements ComponentFactory {

	/**
	 * Creates an array of rulecheck circuits (event times)
	 * @param startWire
	 * @param bits
	 * @param events
	 * @return
	 */
	public CircuitComponent createComponent(int startWire, int bits, int events) {
		CircuitComponent res = new CircuitComponent();
		int eventSize = bits + 1, totalBits = eventSize * events;
		
		CircuitComponent[] ruleCheckComponents = new CircuitComponent[events - 1];
		res.outGates = new CircuitElement[events - 1];
		for (int i = 0; i < events - 1; ++i) {
			ruleCheckComponents[i] = new RuleCheckCircuit().createComponent(0, bits);
			res.outGates[i] = ruleCheckComponents[i].outGates[0];
		}
		
		res.inGates = new CircuitElement[totalBits];
		
		for (int i = 0; i < eventSize; ++i) {
			res.inGates[i] = new Dummy();
			res.inGates[i].setOutElementsCnt(1);
			res.inGates[i].addOutElement(ruleCheckComponents[0].inGates[i]);
			res.inGates[i].registerAtOutElements();
		}
		for (int i = 1; i < events - 1; ++i) {
			int pos = i*eventSize;
			for (int j = 0; j < eventSize; ++j) {
				res.inGates[pos + j] = new Dummy();
				res.inGates[pos + j].setOutElementsCnt(2);
				res.inGates[pos + j].addOutElement(ruleCheckComponents[i-1].inGates[eventSize+j]);
				res.inGates[pos + j].addOutElement(ruleCheckComponents[i].inGates[j]);
				res.inGates[pos + j].registerAtOutElements();
			}
		}
		int pos = (events - 1) * eventSize;
		for (int i = 0; i < eventSize; ++i) {
			res.inGates[pos + i] = new Dummy();
			res.inGates[pos + i].setOutElementsCnt(1);
			res.inGates[pos + i].addOutElement(ruleCheckComponents[events - 2].inGates[eventSize+i]);
			res.inGates[pos + i].registerAtOutElements();
		}
		
		return res;
	}

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		// TODO Auto-generated method stub
		return null;
	}

}

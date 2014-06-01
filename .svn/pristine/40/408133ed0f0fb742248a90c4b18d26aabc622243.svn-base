package factories;

import circuit.CircuitComponent;
import circuit.CircuitElement;

public class Sorting implements ComponentFactory {

	/**
	 * Input format:  {{Timestamp}_t|{S,L}_e}_rep
	 * Output format: {{S,L}_e}_rep (sorted by timestamp)
	 */
	public CircuitComponent createComponent(int startWire, int t, int e, int rep) {
		CircuitComponent c = new CircuitComponent();
		c.inGates = new CircuitElement[rep * (e + t)];
		
		CircuitComponent pairComp = new PairwiseComparison().createComponent(startWire, t, rep);
		for (int i = 0; i < rep; ++i) {
			for (int j = 0; j < t; ++j) {
				c.inGates[i*(t+e) + j] =  pairComp.inGates[i*t + j]; 
			}
		}
		
		int rank = (int)Math.ceil(Math.log(rep) / Math.log(2));
		
		CircuitComponent perm = new Permutation().createComponent(0, e, rep);
		for (int i = 0; i < rep; ++i) {
			for (int j = 0; j < rank; ++j) {
				pairComp.outGates[i*rank + j].setOutElementsCnt(1);
				pairComp.outGates[i*rank + j].addOutElement(perm.inGates[i*(rank+e) + rank - j - 1]);
				pairComp.outGates[i*rank + j].registerAtOutElements();
			}
			for (int j = 0; j < e; ++j) {
				c.inGates[i*(t+e) + j + t] = perm.inGates[i*(rank+e) + j + rank];
			}
		}
		c.outGates = perm.outGates;
		return c;
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

package factories;

import gates.nary.OrN;
import gates.unary.Terminator;

import circuit.CircuitComponent;
import circuit.CircuitElement;

public class Permutation implements ComponentFactory {

	/**
	 * Input format:  {r_logn,{S,E}_b}_n
	 * Output format: {{S,E}_b}_n
	 * @param startWire
	 * @param b
	 * @param n
	 * @return
	 */
	public CircuitComponent createComponent(int startWire, int b, int n) {
		int logn = (int)Math.ceil(Math.log(n) / Math.log(2));
		CircuitComponent res = new CircuitComponent();
		
		res.outGates = new CircuitElement[n * b];
		res.inGates = new CircuitElement[n * (b + logn)];
		int inPos = 0;
		
		for (int i = 0; i < n * b; ++i) {
			res.outGates[i] = new OrN(n);
		}
		
		for (int i = 0; i < n; ++i) {
			CircuitComponent c = new BBit1nDEMUX().createComponent(startWire, b, logn);
			for (int j = 0; j < b + logn; ++j) {
				res.inGates[inPos++] = c.inGates[j];
			}
			for (int j = 0; j < res.outGates.length; ++j) {
				c.outGates[j].setOutElementsCnt(1);
				c.outGates[j].addOutElement(res.outGates[j]);
				c.outGates[j].registerAtOutElements();
			}
			for (int j = res.outGates.length; j < c.outGates.length; ++j) {
				c.outGates[j].setOutElementsCnt(1);
				c.outGates[j].addOutElement(new Terminator());
				c.outGates[j].registerAtOutElements();
			}
		}
		
		return res;
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

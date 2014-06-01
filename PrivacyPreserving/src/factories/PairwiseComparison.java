package factories;

import gates.unary.Dummy;
import gates.unary.Not;
import gates.unary.Terminator;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class PairwiseComparison implements ComponentFactory {

	/**
	 * Input format:  {timestamp_b}_n
	 * Output format: {rank_logn}_n
	 * @param startWire
	 * @param b
	 * @param n
	 * @return
	 */
	public CircuitComponent createComponent(int startWire, int b, int n) {
		CircuitComponent cc = new CircuitComponent();
		
		int logn = (int)Math.ceil(Math.log(n) / Math.log(2));
		
		cc.inGates = new CircuitElement[b * n];
		for (int i = 0; i < b * n; ++i) {
			cc.inGates[i] = new Dummy();
			cc.inGates[i].setOutElementsCnt(n - 1);
		}
		
		
		
		CircuitElement[][] comps = new CircuitElement[n][n-1];
		
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				CircuitComponent comp = new NBitComp().createComponent(0, b);
				comp.outGates[0].setOutElementsCnt(1);
				comp.outGates[0].addOutElement(new Terminator());
				comp.outGates[0].registerAtOutElements();
				
				comps[i][j - 1] = comp.outGates[1];
				comps[j][i] = comp.outGates[1];
				comp.outGates[1].setOutElementsCnt(2);
				int pos = 0;
				for (int k = i * b; k < (i + 1) * b; ++k) {
					cc.inGates[k].addOutElement(comp.inGates[pos++]);
				}
				for (int k = j * b; k < (j + 1) * b; ++k) {
					cc.inGates[k].addOutElement(comp.inGates[pos++]);
				}
			}
		}
		
		cc.outGates = new CircuitElement[n * logn];
		int outGatePos = 0;
		for (int i = 0; i < n; ++i) {
			CircuitComponent rank = new OneBitAdderFactory().createComponent(0, n - 1);
			for (int j = 0; j < n - 1; ++j) {
				if (i > j) {
					CircuitElement not = new Not(1);
					comps[i][j].addOutElement(not);
					not.addOutElement(rank.inGates[j]);
					not.registerAtOutElements();
				} else {
					comps[i][j].addOutElement(rank.inGates[j]);
				}
			}
			for (int j = 0; j < logn; ++j) {
				cc.outGates[outGatePos++] = rank.outGates[j];
			}
		}
		
		for (int i = 0; i < b * n; ++i) {
			cc.inGates[i].registerAtOutElements();
		}
		
		return cc;
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

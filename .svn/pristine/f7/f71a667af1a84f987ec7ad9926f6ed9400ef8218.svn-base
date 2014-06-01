package factories;

import gates.binary.And;
import gates.unary.Dummy;
import gates.unary.Not;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class BBit1nDEMUX implements ComponentFactory {

	/**
	 * Input format:  rank_n|{S,E}_b
	 * Output format: {{S,E}_b}_2^n
	 * @param startWire
	 * @param b
	 * @param n
	 * @return
	 */
	public CircuitComponent createComponent(int startWire, int b, int n) {
		this.globalOut = new CircuitElement[b * (int)Math.pow(2, n)];
		this.globalIn = new CircuitElement[n + b];
		this.globalN = n;
		for (int i = 0; i < n; ++i) {
			this.globalIn[i] = new Dummy();
			this.globalIn[i].setOutElementsCnt((int)Math.pow(2, i) * (b+1));
		}
		CircuitComponent cc = buildRec(b, n);
		for (int i = 0; i < n; ++i) {
			this.globalIn[i].registerAtOutElements();
		}
		cc.outGates = globalOut;
		cc.inGates = globalIn;
		return cc;
	}
		
	private CircuitElement[] globalOut, globalIn;
	private int globalOutPos = 0, globalN;

	private CircuitComponent buildRec(int b, int n) {
		if (n == 1) {
			CircuitComponent cc = get12demux(b, n);
			for (int i = 0; i < cc.outGates.length; ++i) {
				globalOut[globalOutPos++] = cc.outGates[i];
			}
			if (globalN == 1) {
				globalIn = cc.inGates;
			}
			return cc;
		} else {
			CircuitComponent upper = get12demux(b, n);
			CircuitComponent lowerLeft = buildRec(b, n - 1);
			CircuitComponent lowerRight = buildRec(b, n - 1);
			for (int i = 0; i < b; ++i) {
				upper.outGates[i].setOutElementsCnt(1);
				upper.outGates[i].addOutElement(lowerLeft.inGates[i + 1]);
				upper.outGates[i].registerAtOutElements();
				
				upper.outGates[i + b].setOutElementsCnt(1);
				upper.outGates[i + b].addOutElement(lowerRight.inGates[i + 1]);
				upper.outGates[i + b].registerAtOutElements();
			}
			if (n == globalN) {
				for (int i = 0; i < b; ++i) {
					globalIn[i + n] = upper.inGates[i + 1];
				}
			}
			return upper;
			
		}

	}

	private CircuitComponent get12demux(int b, int level) {
		CircuitComponent cc = new CircuitComponent();

		cc.inGates = new CircuitElement[b + 1];
		cc.outGates = new CircuitElement[2 * b];
		cc.allElements = new CircuitElement[1];

		for (int i = 0; i < cc.outGates.length; ++i) {
			cc.outGates[i] = new And();
		}

		cc.allElements[0] = new Not(b);
		for (int i = 0; i < b; ++i) {
			cc.allElements[0].addOutElement(cc.outGates[i]);
		}
		cc.allElements[0].registerAtOutElements();

		cc.inGates[0] = globalIn[globalN - level];
		//cc.inGates[0].setOutElementsCnt(b + 1);
		cc.inGates[0].addOutElement(cc.allElements[0]);
		for (int i = b; i < 2 * b; ++i) {
			cc.inGates[0].addOutElement(cc.outGates[i]);
		}
		//cc.inGates[0].registerAtOutElements();

		for (int i = 1; i < cc.inGates.length; ++i) {
			cc.inGates[i] = new Dummy();
			cc.inGates[i].setOutElementsCnt(2);
			cc.inGates[i].addOutElement(cc.outGates[i - 1]);
			cc.inGates[i].addOutElement(cc.outGates[b + i - 1]);
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

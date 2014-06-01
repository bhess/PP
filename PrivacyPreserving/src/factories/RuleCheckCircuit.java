package factories;

import gates.binary.Or;
import gates.nary.EqualityTwo;
import gates.nary.OrN;
import gates.trinary.AndTri;
import gates.unary.Dummy;
import gates.unary.Not;
import gates.unary.Terminator;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class RuleCheckCircuit implements ComponentFactory {

	/**
	 * Input: S_i(1)|L_i(size)|S_i+1(1)|L_i+1(size)
	 */
	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		CircuitComponent res = new CircuitComponent();
		CircuitComponent comp = new NBitComp().createComponent(startWire, size);
		comp.outGates[1].setOutElementsCnt(1);
		comp.outGates[1].addOutElement(new Terminator());
		comp.outGates[1].registerAtOutElements();
		comp.outGates[0].setOutElementsCnt(2);
		
		res.allElements = new CircuitElement[7 + (2 * size) + 2];
		res.inGates = new CircuitElement[(2 * size) + 2];
		res.outGates = new CircuitElement[1];
		res.allElements[0] = new Not(1);
		res.allElements[1] = comp.outGates[0];
		//res.allElements[1] = new EqualityTwo(2 * size, 2);
		res.allElements[2] = new Not(1);
		res.allElements[3] = new AndTri(1);
		res.allElements[4] = new AndTri(1);
		res.allElements[5] = new Not(1);
		res.allElements[6] = new Or();
		
		res.outGates[0] = res.allElements[6];
		
		res.allElements[0].addOutElement(res.allElements[4]);
		res.allElements[1].addOutElement(res.allElements[3]);
		res.allElements[1].addOutElement(res.allElements[5]);
		res.allElements[2].addOutElement(res.allElements[3]);
		res.allElements[3].addOutElement(res.allElements[6]);
		res.allElements[4].addOutElement(res.allElements[6]);
		res.allElements[5].addOutElement(res.allElements[4]);
		
		for (int i = 0; i < 6; ++i) {
			res.allElements[i].registerAtOutElements();
		}
		
		
		// adding input dummies
		int i = 7;
		res.allElements[i] = new Dummy();
		res.allElements[i].setOutElementsCnt(2);
		res.allElements[i].addOutElement(res.allElements[0]);
		res.allElements[i].addOutElement(res.allElements[3]);
		res.allElements[i].registerAtOutElements();
		++i;
		for (; i < 8 + size; ++i) {
			/*
			res.allElements[i] = new Dummy();
			res.allElements[i].setOutElementsCnt(1);
			res.allElements[i].addOutElement(res.allElements[1]);
			res.allElements[i].registerAtOutElements();
			*/
			res.allElements[i] = comp.inGates[i - 8];
		}
		res.allElements[i] = new Dummy();
		res.allElements[i].setOutElementsCnt(2);
		res.allElements[i].addOutElement(res.allElements[2]);
		res.allElements[i].addOutElement(res.allElements[4]);
		res.allElements[i].registerAtOutElements();
		++i;
		for (int z = 0; i < res.allElements.length; ++i, ++z) {
			/*
			res.allElements[i] = new Dummy();
			res.allElements[i].setOutElementsCnt(1);
			res.allElements[i].addOutElement(res.allElements[1]);
			res.allElements[i].registerAtOutElements();
			*/
			res.allElements[i] = comp.inGates[z + size];
		}
		
		for (i = 7; i < res.allElements.length; ++i) {
			res.inGates[i-7] = res.allElements[i];
		}
		return res;
	}

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

}

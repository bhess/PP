package factories;

import gates.binary.And;
import gates.binary.Xor;
import gates.unary.Dummy;
import circuit.CircuitComponent;
import circuit.CircuitElement;

public class OneBitAdderFactory implements ComponentFactory {

	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		
		component = new CircuitComponent();
		
		if (size == 1) {
			component.inGates = new CircuitElement[1];
			component.inGates[0] = new Dummy();
			component.outGates = component.inGates;
			return component;
		}

		elPerStep = new int[size - 1];
		startIndex = new int[size - 1];
		int inBits = 1;
		int outBits;
		// calculate the number of gates per step
		for (int i = 1; i < size; ++i, inBits = outBits) {
			// int blocks = inBits;
			outBits = (int) Math.ceil(Math.log(i + 2) / Math.log(2));
			elPerStep[i - 1] = (inBits == outBits ? 2 * inBits - 1 : 2 * inBits);
			totalEl += elPerStep[i - 1];
		}

		component.allElements = new CircuitElement[totalEl + size];
		component.outGates = new CircuitElement[(int) Math.ceil(Math
				.log(size + 1)
				/ Math.log(2))];
		elements = component.allElements;
		int count = 0;

		// create the gates
		for (int c = 0; c < elPerStep.length; count += elPerStep[c], ++c) {
			startIndex[c] = count;
		}

		for (int c = 0; c < elPerStep.length - 1; ++c) {
			int el = elPerStep[c];
			boolean odd = (el % 2 == 1);
			int blocks = (odd ? el - 1 : el - 2);
			for (int i = 0; i < blocks; i += 2) {
				elements[startIndex[c] + i] = new Xor(2);
				elements[startIndex[c] + i + 1] = (i + 3 < el ? new And(2)
						: new And(1));
			}

			elements[startIndex[c] + blocks] = (!(elPerStep[c + 1] % 2 == 1 && elPerStep[c] % 2 == 1) ? new Xor(
					2)
					: new Xor(1));

			//elements[startIndex[c] + blocks] = new Xor(2);
			if (!odd) {
				elements[startIndex[c] + blocks + 1] = new And(1);
			}

		}
		// special for the last step
		int c = elPerStep.length - 1;
		int el = elPerStep[c];
		boolean odd = (el % 2 == 1);
		int blocks = (odd ? el - 1 : el - 2);
		for (int i = 0; i < blocks; i += 2) {
			elements[startIndex[c] + i] = new Xor();
			elements[startIndex[c] + i + 1] = (i + 3 < el ? new And(2)
					: new And(1));// new And();
		}
		elements[startIndex[c] + blocks] = new Xor();
		if (!odd) {
			elements[startIndex[c] + blocks + 1] = new And();
		}
		//

		wire();

		// input-gates...
		CircuitElement[] tmpelements = new CircuitElement[2 * (size - 1)];
		for (int i = 0; i < startIndex.length; ++i) {
			tmpelements[2 * i] = elements[startIndex[i]];
			tmpelements[2 * i + 1] = elements[startIndex[i] + 1];
		}

		component.inGates = new CircuitElement[size];
		component.inGates[0] = new Dummy();
		component.inGates[1] = new Dummy();
		component.inGates[0].setOutElementsCnt(2);
		component.inGates[0].addOutElement(tmpelements[0]);
		component.inGates[0].addOutElement(tmpelements[1]);
		component.inGates[0].registerAtOutElements();
		component.allElements[totalEl] = component.inGates[0];
		component.inGates[1].setOutElementsCnt(2);
		component.inGates[1].addOutElement(tmpelements[0]);
		component.inGates[1].addOutElement(tmpelements[1]);
		component.inGates[1].registerAtOutElements();
		component.allElements[totalEl + 1] = component.inGates[1];
		
		for (int i = 2; i < size; ++i) {
			component.inGates[i] = new Dummy();
			component.inGates[i].setOutElementsCnt(2);
			component.inGates[i].addOutElement(tmpelements[2*(i-1)]);
			component.inGates[i].addOutElement(tmpelements[2*(i-1)+1]);
			component.inGates[i].registerAtOutElements();
			component.allElements[totalEl + i] = component.inGates[i];
		}

		// checkConsistency();
		return component;
	}

	private void wire() {
		for (int c = 0; c < elPerStep.length - 1; ++c) {
			int el = elPerStep[c];
			boolean odd = (el % 2 == 1);
			int blocks = (odd ? el - 1 : el - 2);
			for (int i = 0; i < blocks; i += 2) {
				CircuitElement toWire = elements[startIndex[c] + i];
				toWire.addOutElement(elements[startIndex[c + 1] + i]);
				toWire.addOutElement(elements[startIndex[c + 1] + i + 1]);
				toWire.registerAtOutElements();

				toWire = elements[startIndex[c] + i + 1];
				toWire.addOutElement(elements[startIndex[c] + i + 2]);
				if (i + 3 < el) {
					toWire.addOutElement(elements[startIndex[c] + i + 3]);
				}
				toWire.registerAtOutElements();
			}
			CircuitElement toWire = elements[startIndex[c] + blocks];
			toWire.addOutElement(elements[startIndex[c + 1] + blocks]);
			if (!(elPerStep[c + 1] % 2 == 1 && elPerStep[c] % 2 == 1)) {
				toWire.addOutElement(elements[startIndex[c + 1] + blocks + 1]);
			}
			toWire.registerAtOutElements();
			if (!odd) {
				toWire = elements[startIndex[c] + blocks + 1];
				toWire.addOutElement(elements[startIndex[c + 1] + blocks + 2]);
				toWire.registerAtOutElements();
			}

		}

		int outGa = 0;

		int c = elPerStep.length - 1;
		int el = elPerStep[c];
		boolean odd = (el % 2 == 1);
		int blocks = (odd ? el - 1 : el - 2);
		for (int i = 0; i < blocks; i += 2) {
			CircuitElement toWire = elements[startIndex[c] + i];
			component.outGates[outGa++] = toWire;

			toWire = elements[startIndex[c] + i + 1];
			toWire.addOutElement(elements[startIndex[c] + i + 2]);
			if (i + 3 < el) {
				toWire.addOutElement(elements[startIndex[c] + i + 3]);
			}
			toWire.registerAtOutElements();
		}
		CircuitElement toWire = elements[startIndex[c] + blocks];
		component.outGates[outGa++] = toWire;
		if (!odd) {
			toWire = elements[startIndex[c] + blocks + 1];
			component.outGates[outGa] = toWire;
		}

	}

	private CircuitComponent component;

	private CircuitElement[] elements;
	private int[] elPerStep, startIndex;
	private int totalEl = 0;

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

	public void checkConsistency() {

		for (int i = 0; i < elements.length; ++i) {

			if (elements[i] instanceof And) {
				System.out.println((i + 1) + " AND");
			} else if (elements[i] instanceof Xor) {
				System.out.println((i + 1) + " XOR");
			}
			if (elements[i].outElements != null) {
				System.out.println("How many outs: "
						+ elements[i].outElements.length);
				for (CircuitElement c : elements[i].outElements) {
					for (int j = 0; j < elements.length; ++j) {
						if (c == elements[j])
							System.out.println("Out: " + (j + 1));
					}
				}
			}

			if (true)
				continue;
			if (elements[i].outElements == null) {
				System.out.println(i + 1 + " null");
				continue;
			}
			for (int j = 0; j < elements[i].outElements.length; ++j) {
				if (elements[i].outElements[j] == null) {
					System.out.println("Element " + i + 1 + ": suggested "
							+ elements[i].outElements.length + ", actual: " + j
							+ 1);
					break;
				}
			}
		}
	}

}

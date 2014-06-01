/**
 * 
 */
package circuit;

import gates.unary.ResultElement;

/**
 * @author bhess
 *
 */
public class Evaluation {

	public Evaluation(CircuitComponent component) {
		this.component = component;
		this.results = new boolean[component.outGates.length];
		for (int i = 0; i < component.outGates.length; ++i) {
			component.outGates[i].setOutElementsCnt(1);
			component.outGates[i].addOutElement(new ResultElement(results, i));
		}
	}
	
	private CircuitComponent component;
	public boolean[] results;
	
	public boolean[] evaluate(boolean[] inputBits) {
		CircuitElement[] inE = component.inGates;
		for (int i = 0; i < inputBits.length; ++i) {
			inE[i].addSignal(inputBits[i]);
			evaluate(inE[i]);
		}
		return results;
	}
	
	private void evaluate(CircuitElement c) {
		if (c.allSignalsSet()) {
			boolean signal = c.evaluate();
			if (c instanceof ResultElement) return;
			for (CircuitElement el : c.outElements) {
				el.addSignal(signal);
				evaluate(el);
			}
		}
	}
}

package factories;

import circuit.CircuitComponent;

public class SortAndRuleCheck implements ComponentFactory {

	/**
	 * Input format:  {{Timestamp}_t|{S,L}_e}_rep
	 * Output format: {RuleSuccess}_log(rep)
	 */
	public CircuitComponent createComponent(int startWire, int t, int e, int rep) {
		CircuitComponent sort = new Sorting().createComponent(0, t, e, rep);
		CircuitComponent ruleCheck = new RuleSuccessCountCircuit().createComponent(0, e - 1, rep);
		
		System.out.println(sort.outGates.length == ruleCheck.inGates.length);
		
		for (int i = 0; i < sort.outGates.length; ++i) {
			sort.outGates[i].setOutElementsCnt(1);
			sort.outGates[i].addOutElement(ruleCheck.inGates[i]);
			sort.outGates[i].registerAtOutElements();
		}
		
		CircuitComponent res = new CircuitComponent();
		res.inGates = sort.inGates;
		res.outGates = ruleCheck.outGates;
		return res;
	}
	
	@Override
	public CircuitComponent createComponent(int startWire, int size) {
		
		return null;
	}

	@Override
	public int[][] getInputLengths() {
		// TODO Auto-generated method stub
		return null;
	}

}

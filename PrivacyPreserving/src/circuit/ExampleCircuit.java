package circuit;

import factories.BBit1nDEMUX;
import factories.Input2mux21;
import factories.NBitComp;
import factories.OneBitAdderFactory;
import factories.PairwiseComparison;
import factories.Permutation;
import factories.RuleCheckArrayCircuit;
import factories.RuleSuccessCountCircuit;
import factories.SortAndRuleCheck;
import factories.Sorting;

/**
 * @author bhess
 * 
 */
public class ExampleCircuit {

	public static void main(String[] args) {
		//adder();
		//rc();
		
	
		/*
		boolean sample[] = {	false, false, true, false, false, false, false, true,
								true, true, false, true, false, false, true, false,
								false, true, true, true, false, false, true, true,
								false, false, false, false, true, true, true, true
								
		};
		*/
		int rep = 9;
		boolean sample[] = {	false, false, false, false,   true, false, false, true, false,
								false, false, false, true,    false, false, false, true, false,
								false, false, true, false,    true, false, true, true, false,
								false, false, true, true,     false, false, true, true, false,
								false, true, false, false,   true, false, false, true, false,
								false, true, false, true,    false, false, false, true, false,
								false, true, true, false,    true, false, true, true, false,
								false, true, true, true,     false, false, true, true, false,
								true, false, false, false,   true, false, false, true, false,
		};
		CircuitComponent c = new Sorting().createComponent(0, 4, 5, rep);
		Evaluation eval = new Evaluation(c);
		boolean evaled[] = eval.evaluate(sample);
		printSample(evaled);
		rc(evaled, rep);

		CircuitComponent c2 = new SortAndRuleCheck().createComponent(0, 4, 5, rep);
		Evaluation eval2 = new Evaluation(c2);
		boolean[] evaled2 = eval2.evaluate(sample);
		printSample(evaled2);
		
		
		System.exit(0);
	}
	
	static void rc(boolean[] sample, int rep) {
		/*
		boolean sample[] = {	true, false, false, true, 
								false, false, false, true, 
								true, false, true, true, 
								false, false, true, true};
		*/
		printSample(sample);
		/*
		CircuitComponent cc = new RuleCheckArrayCircuit().createComponent(0, 3,
				4);
		Evaluation eval = new Evaluation(cc);
		boolean evaled[] = eval.evaluate(sample);
		printSample(evaled);
		*/
		CircuitComponent cc2 = new RuleSuccessCountCircuit().createComponent(0,
				4, rep);
		Evaluation eval = new Evaluation(cc2);
		boolean[] evaled = eval.evaluate(sample);
		printSample(evaled);
		System.out.println(getValue(evaled));
	}

	static void adder() {
		// for (int c = 1048576; c < 1148576; ++c) {
		int c = 1048575;
		boolean[] sample = arr(c);
		printSample(sample);
		CircuitComponent cc = new OneBitAdderFactory().createComponent(0,
				sample.length);

		// Connector.OBAdder(du, cc);

		Evaluation eval = new Evaluation(cc);
		boolean[] evaled = eval.evaluate(sample);

		int value = getValue(evaled);
		System.out.println(value + " " + (value == cnt(sample)));
		// }

		/*
		 * boolean[] results = new boolean[cc.outGates.length]; for (int i = 0;
		 * i < cc.outGates.length; ++i) { cc.outGates[i].setOutElementsCnt(1);
		 * cc.outGates[i].addOutElement(new ResultElement(results, i)); }
		 * System.out.println(cc);
		 */
	}

	static int getValue(boolean[] evaled) {
		int value = 0;
		for (int i = 0; i < evaled.length; ++i) {
			if (evaled[i]) {
				value |= 0x1 << i;
			}
		}
		return value;
	}

	static boolean[] arr(int num) {
		boolean[] res = new boolean[(int) Math.ceil(Math.log(num + 1)
				/ Math.log(2))];
		for (int i = 0; i < res.length; ++i) {
			res[i] = (num >> i & 0x1) == 0x1;
		}
		return res;
	}

	static int cnt(boolean[] arr) {
		int cnt = 0;
		for (boolean b : arr)
			cnt = (b ? cnt + 1 : cnt);
		return cnt;
	}

	static void printSample(boolean[] sample) {
		System.out.print("[");
		for (boolean b : sample) {
			System.out.print((b ? "1" : "0") + ",");
		}
		System.out.println("]");
	}

}

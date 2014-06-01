/**
 * 
 */
package connectors;

import circuit.CircuitComponent;

/**
 * @author bhess
 * 
 * Connects two Circuit components
 */
public class Connector {

	public static void OBAdder(CircuitComponent dummy, CircuitComponent oba) {
		dummy.outGates[0].setOutElementsCnt(2);
		dummy.outGates[0].addOutElement(oba.inGates[0]);
		dummy.outGates[0].addOutElement(oba.inGates[1]);
		dummy.outGates[1].setOutElementsCnt(2);
		dummy.outGates[1].addOutElement(oba.inGates[0]);
		dummy.outGates[1].addOutElement(oba.inGates[1]);
		
		for (int i = 2; i < dummy.outGates.length; ++i) {
			dummy.outGates[i].setOutElementsCnt(2);
			dummy.outGates[i].addOutElement(oba.inGates[2*(i-1)]);
			dummy.outGates[i].addOutElement(oba.inGates[2*(i-1)+1]);
		}
		
		dummy.outGates = oba.outGates;
	}
	
}

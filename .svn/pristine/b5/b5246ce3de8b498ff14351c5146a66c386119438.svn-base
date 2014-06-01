package circuit;

abstract public class CircuitElement {

	/**
	 * initialize with the associated gate, the number of input wires
	 * and the number of output elements
	 * @param gate 
	 * @param inWireCnt
	 * @param outElementsCnt
	 */
	public CircuitElement(int inWireCnt, int outElementsCnt) {
		this(inWireCnt);
		setOutElementsCnt(outElementsCnt);
	}
	
	public CircuitElement(int inWireCnt) {
		this.inWires = new int[inWireCnt];
		this.inElements = new CircuitElement[inWireCnt];
		this.inSignals = new boolean[inWireCnt];
	}
	
	public void setOutElementsCnt(int outElementsCnt) {
		this.outElements = new CircuitElement[outElementsCnt];
	}
	
	/**
	 * reset all input-signals if the circuit is evaluated
	 */
	public void resetSignals() {
		signalsSet = 0;
	}

	/**
	 * Adds an input wire and the associated element.
	 * @param wire
	 * @param c
	 */
	public void addInWire(int wire, CircuitElement c) {
		inWires[inWirePos] = wire;
		inElements[inWirePos++] = c;
	}
	
	public void registerAtOutElements() {
		for (CircuitElement c : outElements) {
			c.addInWire(outWire, this);
		}
	}
	
	/**
	 * Specify the output-wire
	 * @param wire
	 */
	public void addOutWire(int wire) {
		outWire = wire;
	}
	
	/**
	 * Adds an element attached to the out-wire
	 * @param e
	 */
	public void addOutElement(CircuitElement e) {
		outElements[outWirePos++] = e;
	}
	
	/**
	 * Adds a signal to the wire in the array with the given signal
	 * @param index
	 * @param signal
	 */
	public void addSignal(boolean signal) {
		inSignals[signalsSet++] = signal;
		//signalsSet++;
	}
	
	/**
	 * Are all signals set?
	 * @return
	 */
	public boolean allSignalsSet() {
		return signalsSet == inSignals.length;
	}
	
	/**
	 * Evaluates the associated gate with the given inputs
	 * @return
	 */
	public boolean evaluate() {
		return evaluate(inSignals);
	}
	
	private boolean[] inSignals;
	private int signalsSet = 0;

	public int[] inWires;
	public int outWire;
	public CircuitElement[] inElements, outElements;
	private int inWirePos = 0, outWirePos = 0;

	
	abstract protected boolean evaluate(boolean[] in);
	abstract protected int getArity();
	
}

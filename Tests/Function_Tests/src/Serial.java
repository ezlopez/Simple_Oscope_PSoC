import java.io.InputStreamReader; // decodes a stream of bytes into a character set
import java.io.OutputStreamWriter;

import gnu.io.CommPortIdentifier;
import gnu.io.NoSuchPortException;
import gnu.io.SerialPort;
import gnu.io.SerialPortEvent; //deals with possible events in serial port (eg: data received)
import gnu.io.SerialPortEventListener;
import gnu.io.PortInUseException; //all the exceptions.Never mind them for now
import java.io.IOException;
import gnu.io.UnsupportedCommOperationException;
import java.util.TooManyListenersException;

public class Serial implements SerialPortEventListener {

	private SerialPort sp;
	private CommPortIdentifier portId;
	private InputStreamReader input;
	private static OutputStreamWriter output;
	
	public Serial() {
		sp = null;
		portId = null;
		input = null;
		output = null;
	}

	public void initialize(String portName, int baud, int timeout) {
		try {
			// Get the identifier and try to own it.
			portId = CommPortIdentifier.getPortIdentifier(portName);

			if (!portId.isCurrentlyOwned()) {
				sp = (SerialPort) portId.open(this.getClass().getName(), timeout);
				sp.setSerialPortParams(baud, SerialPort.DATABITS_8, SerialPort.STOPBITS_1, SerialPort.PARITY_NONE);
			} else {
				System.out.println("Port is alread owned.");
				System.exit(1);
			}

		} catch (NoSuchPortException e) {
			System.out.println("Typed the COM port incorrectly");
			System.exit(1);
		} catch (PortInUseException e) {
			System.out.println("Trying to access a port not owned by you");
			System.exit(1);
		} catch (UnsupportedCommOperationException e) {
			e.printStackTrace();
			System.exit(1);
		}

		// Open up the I/O streams
		try {
			input = new InputStreamReader(sp.getInputStream());
			output = new OutputStreamWriter(sp.getOutputStream());
			sp.addEventListener(this);
			sp.notifyOnDataAvailable(true);

		} catch (IOException | TooManyListenersException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

	}

	public void serialEvent(SerialPortEvent evt) {

		// if (evt.getEventType() == SerialPortEvent.DATA_AVAILABLE) { //if data
		// available on serial port
		try {
			while (input.ready())
				System.out.print((char) input.read());
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}

	public void close() {
		if (sp != null) {
			sp.close(); // close serial port
		}
		input = null; // clear
		output = null;
	}

	public void serialWrite(String str) {
		try {
			output.write(str);
			output.flush();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}

}
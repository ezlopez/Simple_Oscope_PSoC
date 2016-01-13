import java.io.IOException;

public class PSOC_Tester {
	/*
	 * The user supplies the test and log file names, in that order.
	 */
	public static void main(String[] args) throws IOException {
		Serial psoc = new Serial();
		TestReader tr = null;
		String response = null;
		byte humanResponse[] = new byte[10];
		
		try {
			tr = new TestReader(args[0], args[1]);
			tr.initialize();
		} catch (IOException e) {
			System.out.println("Give the correct filenames, dummy.");
			System.exit(1);
		} catch (InvalidTestFileException e1) {
			System.out.println("Test file not configured correctly.");
			System.exit(1);
		}

		System.out.println("Opened test and log files.");
		psoc.initialize(tr.portName, tr.baud, tr.timeout);
		System.out.println("Opened " + tr.portName);
		System.out.println("Tests starting");
		
		while (tr.hasNextTest()) {
			// Send the PSoC its command
			psoc.serialWrite(tr.nextTest());
			
			// Wait for PSoC response with max timeout
			
			
			// Wait for human response, if necessary
			if (tr.needsHuman()) {
				try {
					System.out.println("The command is " + tr);
					System.out.print("Does the test pass? ");
					System.in.read(humanResponse);
				} catch (IOException e) {
					e.printStackTrace();
					System.exit(1);
				}
				tr.logResult(response, humanResponse.toString().replaceAll("\\s","").equalsIgnoreCase("Y"));
			}
			else
				tr.logResult(response);
		}
		
		try {
			tr.close();
			psoc.close();
		} catch (IOException e) {
			// Doesn't really matter, we're done anyway
			e.printStackTrace();
		}
		
		System.out.println("Finsished Testing");
	}

}

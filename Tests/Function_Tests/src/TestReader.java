import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.Date;

/*
	 * Test file format
	 * Lines starting with a '%' are considered comment lines
	 * All fields must be separated with spaces 
	 * 
	 * Header: <Port name>  <Baud> <Timeout>
	 * Tests:  <PSOC command> <Expected response> <Human check Y/N>
	 * 
	 * The port name is the name the PC gives the port (i.e. COM5).
	 * The timeout is how long the tester waits for an answer, in ms.
	 * The human check is only used if a test is objective.
	 * 
	 * Example file:
	 * % This is a very simple test
	 * COM5 9600 1000
	 * #PC_REQ_CONNECT# PSOC_READY N
	 * % Done testing
	 * 
	 */
public class TestReader {
	// Com port-related variables
	public int baud, timeout;
	public String portName;
	
	// Test-related variables
	private BufferedReader test;
	private PrintWriter log;
	private int testNum;
	private String currTestLine, nextTestLine;
	private String command, expectedResponse;
	private boolean humanTest;
	
	public TestReader(String testFile, String logFile) throws IOException {
		// Open up the file
		test = new BufferedReader(new FileReader(testFile));
		log = new PrintWriter(logFile, "UTF-8");
		testNum = 0;
		command = null;
		expectedResponse = null;
		humanTest = false;
		currTestLine = null;
		nextTestLine = null;
	}
	
	public void initialize() throws InvalidTestFileException, IOException {
		String[] header;
		
		// Input the test header
		// The quick and dirty method
		if (this.hasNextTest()) {
			header = nextTestLine.split(" ");
			nextTestLine = null;
			portName = header[0];
			baud = Integer.parseInt(header[1]);
			timeout = Integer.parseInt(header[2]); 
		}
		else
			throw new InvalidTestFileException();
		
		// Output log header data
		log.write("Test started " + (new Date()).toString());
		log.flush();
	}
	
	public boolean hasNextTest() {
		String line;
		if (nextTestLine != null)
			return true;
		
		try {
			while (test.ready()) {
				line = test.readLine();
				
				if (line.charAt(0) != '%') {
					nextTestLine = line;
					return true;
				}
			}
		} catch (IOException e) {
			return false;
		}
		return false;
	}
	
	public String nextTest() throws IOException {
		String[] splitTest;
		
		// If caller hasn't already verified it has a next test
		if (nextTestLine == null) {
			if (!this.hasNextTest())
				throw new IOException();
		}
		currTestLine = nextTestLine;
		nextTestLine = null;
		
		// Now that we have the test line, let's parse
		splitTest = currTestLine.split(" ");
		command = splitTest[0];
		expectedResponse = splitTest[1];
		humanTest = splitTest[2].equalsIgnoreCase("y");

		++testNum;
		return command;
	}
	
	public boolean needsHuman() {
		return this.humanTest;
	}
	
	public String getCommand() {
		return this.command;
	}
	
	// PSoC-only result testing
	public void logResult(String psocResult) {
		this.logResult(psocResult, true);
	}

	// PSoC and human result testing
	public void logResult(String psocResult, boolean htResult) {
		
	}
	
	public void close() throws IOException {
		test.close();
		log.close();
	}
}

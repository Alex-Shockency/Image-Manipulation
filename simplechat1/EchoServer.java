// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

import java.io.IOException;

import ocsf.server.AbstractServer;
import ocsf.server.ConnectionToClient;

/**
 * This class overrides some of the methods in the abstract superclass in order
 * to give more functionality to the server.
 *
 * @author Dr Timothy C. Lethbridge
 * @author Dr Robert Lagani&egrave;re
 * @author Fran&ccedil;ois B&eacute;langer
 * @author Paul Holden
 * @version July 2000
 */
public class EchoServer extends AbstractServer {
	// Class variables *************************************************

	/**
	 * The default port to listen on.
	 */
	final public static int DEFAULT_PORT = 5555;

	// Constructors ****************************************************

	/**
	 * Constructs an instance of the echo server.
	 *
	 * @param port
	 *            The port number to connect on.
	 */
	public EchoServer(int port) {
		super(port);
	}

	// Instance methods ************************************************

	/**
	 * This method handles any messages received from the client.
	 *
	 * @param msg
	 *            The message received from the client.
	 * @param client
	 *            The connection from which the message originated.
	 */
	public void handleMessageFromClient(Object msg, ConnectionToClient client) {
		String tempMsg = msg.toString();
		// keeps track of messages sent by user.
		int msgCount = (int) client.getInfo("Message Count");
		// Check if loginId is correctly sent
		loginId(msgCount, tempMsg, client);
		// print message back to server.
		System.out.println("Message received: " + msg.toString() + " from "
				+ client.getInfo("Login Id") + " " + client);
		if (msgCount == 0) {
			System.out.println(client.getInfo("Login Id") + " has logged on.");
			this.sendToAllClients(client.getInfo("Login Id")
					+ " has logged on.");
		}
		if (msgCount != 0) {
			if (tempMsg.trim().equals("#logoff")) {
				try {
					client.close();
				} catch (IOException e) {
					e.printStackTrace();
				}
			} else
				this.sendToAllClients(client.getInfo("Login Id") + "> "
						+ tempMsg);
		}
		client.setInfo("Message Count", msgCount + 1);

	}

	/**
	 * This method overrides the one in the superclass. Called when the server
	 * starts listening for connections.
	 */
	protected void serverStarted() {
		System.out.println("Server listening for connections on port "
				+ getPort());
	}

	/**
	 * This method overrides the one in the superclass. Called when the server
	 * stops listening for connections.
	 */
	protected void serverStopped() {
		System.out.println("Server has stopped listening for connections.");
	}

	@Override
	protected void clientConnected(ConnectionToClient client) {
		client.setInfo("Message Count", 0);
		System.out
				.println("A new client is attempting to connect to the server.");
	}

	@Override
	synchronized protected void clientDisconnected(ConnectionToClient client) {
		System.out.println(client.getInfo("Login Id") + " has disconnected.");
	}

	// Class methods ***************************************************

	/**
	 * This method receives the login message and checks if it is valid and is
	 * the first message sent. Called when the client attempts to login.
	 * 
	 * @param msgCount
	 *            -Keeps track of the number of messages sent by user used to
	 *            check if login command is issued later.
	 * @param message
	 *            -message received by server from client.
	 * @param client
	 *            - used to set client info
	 */
	private void loginId(int msgCount, String message, ConnectionToClient client) {
		if (message.startsWith("#login")) {
			if (msgCount == 0) {
				client.setInfo("Login Id",
						message.substring(7, message.length()));
			}

		}
		else if (msgCount == 0 && !message.startsWith("#login")) {
			try {
				client.sendToClient("ERROR - No login ID specified.  Connection aborted.");
			} catch (IOException e1) {
				e1.printStackTrace();
			}
			try {
				client.close();
			} catch (IOException e) {
				e.printStackTrace();
			}
		}
	}

	/**
	 * This method is responsible for the creation of the server instance (there
	 * is no UI in this phase).
	 *
	 * @param args
	 *            [0] The port number to listen on. Defaults to 5555 if no
	 *            argument is entered.
	 */
	public static void main(String[] args) {
		int port = 0; // Port to listen on
		try {
			port = Integer.parseInt(args[0]); // Get port from command line
		} catch (Throwable t) {
			port = DEFAULT_PORT; // Set port to 5555
		}
		EchoServer sv = new EchoServer(port);
		try {
			sv.listen(); // Start listening for connections
		} catch (Exception ex) {
			System.out.println("ERROR - Could not listen for clients!");
		}
	}

}
// End of EchoServer class

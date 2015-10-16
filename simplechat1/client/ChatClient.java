// This file contains material supporting section 3.7 of the textbook:
// "Object Oriented Software Engineering" and is issued under the open-source
// license found at www.lloseng.com 

package client;

import java.io.IOException;

import ocsf.client.AbstractClient;

import common.ChatIF;

/**
 * This class overrides some of the methods defined in the abstract superclass
 * in order to give more functionality to the client.
 *
 * @author Dr Timothy C. Lethbridge
 * @author Dr Robert Lagani&egrave;
 * @author Fran&ccedil;ois B&eacute;langer
 * @version July 2000
 */
public class ChatClient extends AbstractClient {
	// Instance variables **********************************************

	/**
	 * The interface type variable. It allows the implementation of the display
	 * method in the client.
	 */
	ChatIF clientUI;
	String id;

	// Constructors ****************************************************

	/**
	 * Constructs an instance of the chat client.
	 *
	 * @param host
	 *            The server to connect to.
	 * @param port
	 *            The port number to connect on.
	 * @param clientUI
	 *            The interface type variable.
	 */

	public ChatClient(String login, String host, int port, ChatIF clientUI)
			throws IOException {
		super(host, port); // Call the superclass constructor
		this.clientUI = clientUI;
		id = login;
		try {
			openConnection();
			sendToServer("#login " + login);
		} catch (IOException e) {
			System.out.println("Cannot open connection.  Awaiting command.");
		}
	}

	// Instance methods ************************************************

	/**
	 * This method handles all data that comes in from the server.
	 *
	 * @param msg
	 *            The message from the server.
	 */
	public void handleMessageFromServer(Object msg) {
		String message = msg.toString();
		clientUI.display(message);
	}

	/**
	 * This method handles all data coming from the UI
	 *
	 * @param message
	 *            The message from the UI.
	 */
	public void handleMessageFromClientUI(String message) {
		try {
			if (message.length() != 0) {
				if (message.charAt(0) == '#') {
					handleCommand(message);
				} else {
					sendToServer(message);
				}
			}
		} catch (IOException e) {
			clientUI.display("Could not send message to server.  Terminating client.");
			quit();
		}
	}

	/**
	 * This method terminates the client.
	 */
	public void quit() {
		try {
			closeConnection();
		} catch (IOException e) {
		}
		System.exit(0);
	}

	@Override
	protected void connectionClosed() {
		System.out.println("Client's connection has been closed.");
	}

	@Override
	protected void connectionException(Exception exception) {
		System.out.println("Abnormal termination of connection.");
	}

	/**
	 * performs action based on command returns -1 for invalid command
	 * 
	 * @param command
	 * @return
	 */
	private void handleCommand(String command) throws IOException {
		// parse string
		// check #
		// check command
		if (command.charAt(0) == '#') {
			// parse command
			int endOfCommand = command.length();
			String argument = "";
			if (command.contains(" ")) {
				endOfCommand = command.indexOf(' ');
				argument = command.substring(command.indexOf(' ') + 1);
			}
			String commandType = command.substring(1, endOfCommand);
			switch (commandType) {
			case "quit":
				System.exit(1);
				break;
			case "logoff":
				sendToServer("#logoff");
				closeConnection();
				break;
			case "sethost":
				if (isConnected()) {
					clientUI.display("ERROR - client is already connected to a server");
					break;
				}
				setHost(argument);
				clientUI.display("Host set to: " + argument);
				break;
			case "setport":
				if (isConnected()) {
					clientUI.display("ERROR - client is already connected to a server");
				}
				try {
					setPort(Integer.parseInt(argument));
					clientUI.display("Port set to: " + argument);
				} catch (Exception e) {
					System.out.println("ERROR: invalid format");
				}
				break;
			case "login":
				if (isConnected()) {
					clientUI.display("ERROR - client is already connected to a server");
				} else {
					openConnection();
					sendToServer("#login " + id);
				}
				break;
			case "gethost":
				clientUI.display("HOST NAME: " + getHost());
				break;
			case "getport":
				clientUI.display("PORT: " + Integer.toString(getPort()));
				break;
			default:
				clientUI.display("invalid command");
			}
		}
	}
}// End of ChatClient class

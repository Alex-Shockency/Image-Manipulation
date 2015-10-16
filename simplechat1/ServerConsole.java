import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import client.ChatClient;

import common.ChatIF;

public class ServerConsole implements ChatIF {
	final public static int DEFAULT_PORT = 5555;
	EchoServer server;

	@Override
	public void display(String message) {
		System.out.println("> " + message);
	}

	public ServerConsole(String host, int port) {
		try {
			// client= new ChatClient("server", host, port, this);
			server = new EchoServer(port);
			server.listen();
		} catch (Exception e) {
			// TODO Auto-generated catch block
			System.out.println("ERROR - Could not listen for clients!");
		}
	}

	/**
	 * This method waits for input from the console. Once it is received, it
	 * sends it to the client's message handler.
	 */
	public void accept() {
		try {
			BufferedReader fromConsole = new BufferedReader(
					new InputStreamReader(System.in));
			String message;
			int port = 0;
			while (true) {
				message = fromConsole.readLine();
				handleServerCommand(message, port);
			}// end while(true)
		} catch (Exception ex) {
			System.out.println("Unexpected error while reading from console!");
		}
	}// end accept()

	private void handleServerCommand(String message, int port) {
		if (message.contains("#setport")) {
			String tempPort = message.trim().substring(8);
			try {
				port = Integer.parseInt(tempPort);
				message = message.substring(0, 8);
			} catch (Exception e) {
				System.out.println("ERROR - invalid port #");
			}
		}
		switch (message) {
		case "#quit":
			try {
				server.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			System.exit(1);
			break;
		case "#stop":
			server.sendToAllClients("WARNING - Server has stopped listening for connections.");
			server.stopListening();
			break;
		case "#close":
			server.sendToAllClients("WARNING - Server has stopped listening for connections.");
			server.sendToAllClients("SERVER SHUTTING DOWN! DISCONNECTING!");
			server.stopListening();
			try {
				server.close();
			} catch (IOException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			break;
		case "#setport":
			if (!server.isListening()) {
				if (port != 0) {
					server.setPort(port);
					System.out.println("Port set to: " + port);
				}
			} else {
				System.out
						.println("ERROR - Server must be closed before changing port");
			}
			break;
		case "#start":
			if (!server.isListening()) {
				try {
					server.listen();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			} else {
				System.out.println("ERROR - Server already listening");
			}
			break;
		case "#getport":
			System.out.println("Current port: " + server.getPort());
			break;
		}
		if (message.length() != 0) {
			if (message.trim().charAt(0) != '#') {
				server.sendToAllClients("SERVER MSG> " + message);
				System.out.println("SERVER MSG> " + message);
			}
		}
	}// end handleServerCommand(String message,int port)

	public static void main(String[] args) {
		String host = "";
		int port = 0; // The port number
		if (args.length == 2) {
			try {
				host = args[0];
				port = Integer.parseInt(args[1]); // Get port from command line
			} catch (Throwable t) {
				host = args[1];
				port = DEFAULT_PORT; // Set port to 5555
			}
		}
		if (args.length == 1) {
			try {
				port = Integer.parseInt(args[0]); // Get port from command line
			} catch (Throwable t) {
				host = args[0];
				port = DEFAULT_PORT; // Set port to 5555
			}
		} else {
			host = "localhost";
			port = DEFAULT_PORT; // Set port to 5555
		}
		ServerConsole serverchat = new ServerConsole(host, port);
		serverchat.accept(); // Wait for console data
	}
}// end class

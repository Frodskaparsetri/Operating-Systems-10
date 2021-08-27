import java.net.*;
import java.io.*;

public class EchoServer {
    public static void main(String[] args) {
        try {
            boolean isRunning = true;
            ServerSocket socket = new ServerSocket(5575);
            /* now listen for connections */
            while (isRunning) {
                Socket client = socket.accept();

                // Read from the input from client
                InputStream in = client.getInputStream();
                BufferedReader bin = new BufferedReader(new InputStreamReader(in));

                String line = bin.readLine();

                // Echo back the input from the client to the client
                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                pout.println(line);

                /* close the socket and resume */
                client.close();

                isRunning = false; // NOTE: just terminating it straight away for testing purposes
            }
            socket.close();
        } catch (IOException ioe) {
            System.err.println(ioe);

        }
    }

}

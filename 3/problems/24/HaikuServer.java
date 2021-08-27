import java.net.*;
import java.io.*;

public class HaikuServer {
    public static void main(String[] args) {
        try {
            String haiku = "coronavirus\ngo away and don't come backcovid19 sucks";

            boolean isRunning = true;
            ServerSocket socket = new ServerSocket(5575);
            /* now listen for connections */
            while (isRunning) {
                Socket client = socket.accept();
                PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                /* write the "Quote of the Day" to the socket */
                pout.println("This is the word of the day!");
                /* close the socket and resume */
                /* listening for connections */
                client.close();

                isRunning = false; // NOTE: just terminating it straight away for testing purposes
            }
            socket.close();
        } catch (IOException ioe) {
            System.err.println(ioe);

        }
    }

}

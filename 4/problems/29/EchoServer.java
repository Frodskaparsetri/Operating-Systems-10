import java.net.*;
import java.util.concurrent.*;
import java.io.*;

/* ARGS: a number - determining how many clients at a time are supported */
public class EchoServer {
    public static void main(String[] args) {

        ServerSocket socket = null;
        boolean isRunning = true;

        try {
            int numberOfThreads = Integer.parseInt(args[0].trim());
            ExecutorService pool = Executors.newFixedThreadPool(numberOfThreads);

            socket = new ServerSocket(5575);
            System.out.println("Server Start. Awaiting Client connections...");

            /* now listen for connections */
            while (isRunning) {
                Socket client = socket.accept();

                System.out.println("Client Connected!");

                Runnable connection = () -> {
                    try {
                        // Read from the input from client
                        InputStream in = client.getInputStream();
                        BufferedReader bin = new BufferedReader(new InputStreamReader(in));

                        String line = bin.readLine();

                        // Echo back the input from the client to the client
                        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                        pout.println(line);

                        /* close the socket */
                        client.close();
                        System.out.println("Client thread completed!");
                    } catch (Exception error) {
                        System.err.println(error);
                    }
                };

                System.out.println("Serving Client in new thread!");
                pool.execute(connection);
                System.out.println("Client served with new thread!\n---");
            }
            socket.close();
        } catch (IOException ioe) {
            System.err.println(ioe);
        }
    }

}

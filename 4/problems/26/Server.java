import java.net.*;
import java.io.*;
import java.util.concurrent.*;

public class Server {
    public static void main(String[] args) {

        Boolean isRunning = true;
        ServerSocket socket = null;
        try {

            int numberOfThreads = Integer.parseInt(args[0].trim());
            ExecutorService pool = Executors.newFixedThreadPool(numberOfThreads);

            socket = new ServerSocket(6013);
            System.out.println("Server Start. Awaiting Client connections...");

            /* now listen for connections */
            while (isRunning) {

                Socket client = socket.accept();
                System.out.println("Received Connection!");

                Runnable connection = () -> {
                    try {
                        PrintWriter pout = new PrintWriter(client.getOutputStream(), true);
                        /*
                         * Waiting 10 seconds just to demonstrate that multiple clients can run
                         * concurrently
                         */
                        Thread.sleep(10000);
                        pout.println("This is the word of the day!");
                        client.close();
                    } catch (Exception error) {
                        System.err.println(error);
                    }

                };

                System.out.println("Issuing new task for client!");
                pool.execute(connection);
                System.out.println("Issue completed!\nAwating new connections!\n---");

            }
            socket.close();

        } catch (Exception error) {
            System.err.println(error);
        }
    }
}

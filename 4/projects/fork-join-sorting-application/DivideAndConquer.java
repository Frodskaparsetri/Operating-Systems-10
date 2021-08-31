import java.util.Random;
import java.util.concurrent.ForkJoinPool;
import java.util.concurrent.RecursiveAction;

// Args: quicksort | mergesort
public class DivideAndConquer {
    public static void main(String[] args) {

        if (args.length < 1) {
            System.out.println("Missing Args: write either \"quicksort\" or \"mergesort\"");
            return;
        }

        int[] randomNumbers = generateRandomArray(500, 1000);

        ForkJoinPool pool = new ForkJoinPool();

        RecursiveAction recursive;
        switch (args[0]) {
            case "quicksort":
                recursive = new QuickSort(0, randomNumbers.length, randomNumbers);
                break;

            case "mergesort":
            default:
                recursive = new MergeSort(randomNumbers.length, randomNumbers);
                break;
        }

        pool.submit(recursive);

        // Output:
        for (int n : randomNumbers) {
            System.out.print(n + " ");
        }
    }

    public static int[] generateRandomArray(int n, int max) {
        int[] list = new int[n];
        Random random = new Random();

        for (int i = 0; i < n; i++) {
            list[i] = random.nextInt(max);
        }
        return list;
    }
}

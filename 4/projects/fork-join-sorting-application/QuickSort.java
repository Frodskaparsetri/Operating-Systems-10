import java.util.concurrent.RecursiveAction;

public class QuickSort extends RecursiveAction {

    static final int THRESHOLD = 100;

    private int begin;
    private int end;
    private int[] array;

    QuickSort(int begin, int end, int[] array) {
        this.begin = begin;
        this.end = end;
        this.array = array;
    }

    @Override
    protected void compute() {
        if (end - begin < THRESHOLD) {
            SelectionSort.sort(array);
            return;
        }

        int middle = (begin + end) / 2;

        RecursiveAction leftTask = new QuickSort(begin, middle, array);
        RecursiveAction rightTask = new QuickSort(middle + 1, end, array);

        leftTask.fork();
        rightTask.fork();

        rightTask.join();
        leftTask.join();
    }

}
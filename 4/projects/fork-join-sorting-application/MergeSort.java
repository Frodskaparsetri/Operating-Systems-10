import java.util.concurrent.RecursiveAction;

public class MergeSort extends RecursiveAction {

    static final int THRESHOLD = 100;

    private int size;
    private int[] array;

    MergeSort(int size, int[] array) {
        this.size = size;
        this.array = array;
    }

    @Override
    protected void compute() {
        if (size < THRESHOLD) {
            SelectionSort.sort(array);
            return;
        }

        int middle = size / 2;

        RecursiveAction leftTask = new MergeSort(middle, array);
        RecursiveAction rightTask = new MergeSort(size - middle, array);

        leftTask.fork();
        rightTask.fork();

        rightTask.join();
        leftTask.join();
    }

}
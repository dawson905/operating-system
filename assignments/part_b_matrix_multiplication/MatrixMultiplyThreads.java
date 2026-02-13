import java.util.Scanner;

public class MatrixMultiplyThreads {

    static int[][] A;
    static int[][] B;
    static int[][] C;

    // One thread computes one row of C
    static class RowWorker implements Runnable {
        private final int row;

        RowWorker(int row) {
            this.row = row;
        }

        public void run() {
            int colsB = B[0].length;
            int sharedDim = B.length;

            for (int j = 0; j < colsB; j++) {
                int sum = 0;
                for (int k = 0; k < sharedDim; k++) {
                    sum += A[row][k] * B[k][j];
                }
                C[row][j] = sum;
            }
        }
    }

    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);

        int rA = sc.nextInt();
        int cA = sc.nextInt();
        A = new int[rA][cA];
        for (int i = 0; i < rA; i++) {
            for (int j = 0; j < cA; j++) {
                A[i][j] = sc.nextInt();
            }
        }

        int rB = sc.nextInt();
        int cB = sc.nextInt();
        B = new int[rB][cB];
        for (int i = 0; i < rB; i++) {
            for (int j = 0; j < cB; j++) {
                B[i][j] = sc.nextInt();
            }
        }

        // Dimension check
        if (cA != rB) {
            System.out.println("Error: Cannot multiply. A has " + cA + " columns but B has " + rB + " rows.");
            sc.close();
            return;
        }

        C = new int[rA][cB];

        // Create one thread per row
        Thread[] threads = new Thread[rA];
        for (int row = 0; row < rA; row++) {
            threads[row] = new Thread(new RowWorker(row));
            threads[row].start();
        }

        // Wait for all rows to finish
        for (int row = 0; row < rA; row++) {
            try {
                threads[row].join();
            } catch (InterruptedException e) {
                System.out.println("Interrupted while waiting for threads.");
                sc.close();
                return;
            }
        }

        System.out.println("Result Matrix C:");
        printMatrix(C);

        sc.close();
    }

    private static void printMatrix(int[][] M) {
        for (int i = 0; i < M.length; i++) {
            for (int j = 0; j < M[0].length; j++) {
                System.out.print(M[i][j]);
                if (j < M[0].length - 1) System.out.print(" ");
            }
            System.out.println();
        }
    }
}

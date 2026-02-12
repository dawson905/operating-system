public class Main {
    public static void main(String[] args) throws InterruptedException {

        BankAccount account = new BankAccount();

        Thread[] threads = new Thread[10];

        for (int i = 0; i < 5; i++) {
            threads[i] = new Thread(() -> account.updateBalance(100));
        }

        for (int i = 5; i < 10; i++) {
            threads[i] = new Thread(() -> account.updateBalance(-100));
        }

        for (Thread t : threads) {
            t.start();
        }

        for (Thread t : threads) {
            t.join();
        }

        System.out.println("Final Balance: " + account.getBalance());
    }
}

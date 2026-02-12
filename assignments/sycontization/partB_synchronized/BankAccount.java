public class BankAccount {
    private int balance = 1000;

    public synchronized void updateBalance(int amount) {
        int current = balance;
        try {
            Thread.sleep(10);
        } catch (InterruptedException e) {
        }
        balance = current + amount;
    }

    public int getBalance() {
        return balance;
    }
}

import java.util.concurrent.atomic.AtomicInteger;
import java.util.concurrent.locks.ReentrantLock;

public class CounterTest {

    interface Counter {
        void increment();
        int get();
    }

    static class LockCounter implements Counter {
        private int count = 0;
        private ReentrantLock lock = new ReentrantLock();

        public void increment() {
            lock.lock();
            try {
                count++;
            } finally {
                lock.unlock();
            }
        }

        public int get() {
            return count;
        }
    }

    static class AtomicCounter implements Counter {
        private AtomicInteger count = new AtomicInteger(0);

        public void increment() {
            count.incrementAndGet();
        }

        public int get() {
            return count.get();
        }
    }

    static long testCounter(Counter c) throws InterruptedException {
        int threads = 4;
        int loops = 100000;

        Thread[] t = new Thread[threads];

        long start = System.nanoTime();

        for (int i = 0; i < threads; i++) {
            t[i] = new Thread(() -> {
                for (int j = 0; j < loops; j++) {
                    c.increment();
                }
            });
        }

        for (Thread x : t) x.start();
        for (Thread x : t) x.join();

        return System.nanoTime() - start;
    }

    public static void main(String[] args) throws InterruptedException {

        Counter lock = new LockCounter();
        Counter atomic = new AtomicCounter();

        long lockTime = testCounter(lock);
        long atomicTime = testCounter(atomic);

        System.out.println("LockCounter total: " + lock.get());
        System.out.println("LockCounter time: " + lockTime);

        System.out.println("AtomicCounter total: " + atomic.get());
        System.out.println("AtomicCounter time: " + atomicTime);

        System.out.println("Expected: 400000");
    }
}
